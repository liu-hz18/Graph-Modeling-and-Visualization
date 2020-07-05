var width = 600;
var height = 600;
var svg = d3.select("svg");
svg.attr("x", 200)
    .attr("y", 200)
    .attr("width", 1000)
    .attr("height", 1000);

/*初始化force*/
var force = d3.layout.force()
    .nodes(nodes)
    .links(edges)
    .size([800, 800])     //作用力的中心区域       
    .linkDistance(80)   //连线的长度
    .charge([-25]);     //负数为排斥 正数为吸引

/*很关键 启动force*/
force.start();

/*添加连线*/
var svg_edges = svg.selectAll("line")
    .data(edges)
    .enter()
    .append("line")
    .attr("dx", function (d, i) {
        return i * 20;
    })
    .attr("dy", function (d, i) {
        return i * 30;
    })
    .attr("stroke-opacity", 0.6)
    .style("stroke", "#999")  //线条的颜色
    .style("stroke-width", d => Math.sqrt(d.weight/100));

/*颜色*/
var color = d3.scale.category20();

/*添加节点*/
var svg_nodes = svg.selectAll("circle")
    .data(nodes)
    .enter()
    .append("circle")
    .attr("cx", function (d, i) {
        return i * 20;
    })
    .attr("cy", function (d, i) {
        return i * 30;
    })
    .attr("r", 5)
    .style("fill", function (d, i) {
        return color(i);
    })
    .style("-webkit-tap-highlight-color", function(d, i){
        return color(i+1);
    })
    .call(force.drag);//控制拖动


//单击结点显示电影信息
var svg_node = svg.selectAll("circle")
    .on("click", function (d, i) {
        document.getElementById("movie-infohint").style.display = "none";
        document.getElementById("movie-info").style.visibility = "visible";
        document.getElementById("moviename").innerHTML = nodes[i].name;
        document.getElementById("moviedirector").innerHTML = nodes[i].director;
        document.getElementById("moviewriter").innerHTML = nodes[i].writer;
        document.getElementById("movieactors").innerHTML = nodes[i].actor;
        document.getElementById("movieregion").innerHTML = nodes[i].region;
        document.getElementById("movielanguage").innerHTML = nodes[i].language;
        document.getElementById("moviedate").innerHTML = nodes[i].date;
        document.getElementById("movietype").innerHTML = nodes[i].type;
    })


force.on("tick", function () { //对于每一个时间间隔  将之前通过force活着
    //更新连线坐标
    svg_edges.attr("x1", function (d) { return d.source.x; })
        .attr("y1", function (d) { return d.source.y; })
        .attr("x2", function (d) { return d.target.x; })
        .attr("y2", function (d) { return d.target.y; });

    //更新节点坐标
    svg_nodes.attr("cx", function (d) { return d.x; })
        .attr("cy", function (d) { return d.y; });

});


function trim(str){ //删除左右两端的空格
　　 return str.replace(/(^\s*)|(\s*$)/g, "");
}

//中心度算法展示 结点缩放
function displayCentrality(i) {
    restoreCentrality();
    clearCluster();
    restoreTree();
    if (i == 1) {                //介数中心度
        svg.selectAll("circle")
            .data(nodes)
            .transition()
            .duration(1500)
            .attr("r", function (circle) {
                return circle.betCent*100+2;
            });
    }
    else if (i == 2) {                //紧密中心度
        svg.selectAll("circle")
            .data(nodes)
            .transition()
            .duration(1500)
            .attr("r", function (circle) {
                return circle.closeCent*6000+2;
            });
    }
}

function restoreCentrality() {
    svg.selectAll("circle")
        .data(nodes)
        .transition()
        .duration(1000)
        .attr("r", 5);
}

function buildTree() {
    restoreTree();
    clearCluster();
    restoreCentrality();
    svg_edges
        .transition()
        .duration(1000)
        .style("stroke", function (line) {
            if (line.isTree == 1) {
                return "red";
            }
            else
                return "#999";
        })  //线条的颜色
        .style("stroke-width", function (line) {
            if (line.isTree == 1)
                return 2;
            else
                return 0.3;
        });//线条的宽度
}

function restoreTree() {         //清空
    svg_edges
        .transition()
        .duration(1000)
        .style("stroke", "#999")
        .style("stroke-width", 1);
}


function showRoute(i) {
    var cur = 0;
    var nex = path[i][0];
    var n = path[i].length;
    for (var k = 0; k < n; k++) {
        nodes[path[i][k]].visited = 1;
    }
    svg_nodes.transition()
        .duration(1500)
        .attr("r", function (circle) {
            if (circle.visited == 1) {
                return 15;
            }
            else
                return 5;
        });
    svg_edges.transition()
        .duration(1500)
        .style("stroke", function (line) {
            if (line.source.visited == 1 && line.target.visited == 1)
                return "#FF0000";
            else
                return "#999";
        })
        .style("stroke-width", function (line) {
            if (line.source.visited == 1 && line.target.visited == 1)
                return 5;
            else
                return 1;
        });
}

function getRoute() {  //最短路径展示
    clearRoute();
    restoreCentrality();
    restoreTree();
    clearCluster();
    var ps = trim(document.getElementById("startpoint").value);
    //alert(ps);
    var es = trim(document.getElementById("endpoint").value);
    var s = -1;
    var e = -1;
    var n = nodes.length;
    for (var i = 0; i < n; i++) {
        if (ps == nodes[i].name) {
            s = i;
            break;
        }
    }
    for (var i = 0; i < n; i++) {
        if (es == nodes[i].name) {
            e = i;
            break;
        }
    }
    if (s < e) {
        var temp = s;
        s = e;
        e = temp;
    }
    if (s >= 0 && e >= 0) {
        var ans = 0;
        if (s <= e){
            ans = s * n + e;
        } else {
            ans = e * n + s;
        }
        showRoute(ans);
        //console.log(path[ans]);
        var pathname = new Array;
        var len = path[ans].length;
        for(var i = 0; i < len; i++){
            pathname[i] = "《"+nodes[path[ans][i]].name+"》";
        }
        document.getElementById("path").innerHTML = pathname;
    }
    else
        alert("您搜索的电影不存在");
    console.log(s + " " + e);
}

function clearRoute() {
    svg_edges
        .transition()
        .duration(1000)
        .style("stroke", "#999")
        .style("stroke-width", 1);
    svg_nodes
        .transition()
        .duration(1000)
        .attr("r", function (circle) {
            circle.visited = 0;
            return 5;
        });
}


function displayCluster() {
    clearRoute();
    restoreCentrality();
    restoreTree();
    svg_nodes
        .transition()
        .duration(1500)
        .style("fill", function (circle) {
            return color(circle.community);
        });
}

function clearCluster() {
    var counter = 0;
    svg_nodes
        .transition()
        .duration(1000)
        .style("fill", function () {
            counter++;
            return color(counter % 10);
        });
}
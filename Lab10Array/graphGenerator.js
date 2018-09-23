var random = Math.random, floor = Math.floor;
var verticies = floor(random() * 5) + 5;
var edges = [];
var Edge = /** @class */ (function () {
    function Edge(v1, v2, e) {
        this.v1 = v1;
        this.v2 = v2;
        this.e = e;
    }
    return Edge;
}());
for (var v1 = 0; v1 < verticies; ++v1) {
    for (var v2 = 0; v2 < verticies; ++v2) {
        if (random() > 0.33) {
            continue;
        }
        var weight = floor(random() * 100);
        edges.push(new Edge(v1, v2, weight));
    }
}
console.log("go 1");
console.log("lg " + verticies + " " + edges.length);
for (var _i = 0, edges_1 = edges; _i < edges_1.length; _i++) {
    var edge = edges_1[_i];
    console.log(edge.v1 + " " + edge.v2 + " " + edge.e);
}

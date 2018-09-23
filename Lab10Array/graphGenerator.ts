const { random, floor } = Math;

const verticies = floor(random() * 5) + 5;
const edges: Edge[] = [];

class Edge {
  v1: number;
  v2: number;
  e: number;

  constructor(v1, v2, e) {
    this.v1 = v1;
    this.v2 = v2;
    this.e = e;
  }
}

for (let v1 = 0; v1 < verticies; ++v1) {
  for (let v2 = 0; v2 < verticies; ++v2) {
    if (random() > 0.33) {
      continue;
    }

    const weight = floor(random() * 100);
    edges.push(new Edge(v1, v2, weight));
  }
}

console.log(`go 1`);
console.log(`lg ${verticies} ${edges.length}`);

for (let edge of edges) {
  console.log(`${edge.v1} ${edge.v2} ${edge.e}`);
}

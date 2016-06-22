//author: Yingzhu (Jacqueline) Zhang

#include <queue>
#include <algorithm>
#include "graph.hpp"
#include "mst.hpp"
#include "union_find.hpp"


using std::cerr;
using std::endl;
using std::max;

Weighted_Graph::Weighted_Graph(string name) : name(name), E(0), V(0), adj(1) {}


MST Weighted_Graph::kruskal() const 
{
  MST mst;
  Edge ed;
  Edge ef;

  // The priority pq stores the edges with the minimum element determined by the edge weights.
  // I'm spotting you the declaration of the priority queue since the syntax is particularly forbidding. 
  // I couldn't resist passing a lambda expression (new in C++11) to serve as the comparator in the
  // priority queue.
  auto compare = [](Edge e, Edge f) {return (e.weight() > f.weight());};
  std::priority_queue<Edge, std::vector<Edge>, decltype(compare)> pq(compare);

  for (int x = 0; x < E; x++)
  {
    Edge ed = edges[x];
    pq.push(ed);

  }

  Union_Find uf = Union_Find(V);

  while (!pq.empty() &&  mst.size() < ((unsigned int) V-1))
  {
    Edge ef = pq.top();
    pq.pop();
    int v = ef.either();
    int w = ef.other(v);
    if (uf.connected(v,w)) {
      continue;
    }
    uf.onion(v,w);
    mst.add_edge(ef);

  }

  // Kruskal's algorithm goes here...
  // cerr << "It would help if you implemented Kruskal's algorithm!" << endl;
  
  return mst;
}


void Weighted_Graph::add_edge(Edge e)
{
  edges.push_back(e);
  E++;
  
  int v = e.either();
  int w = e.other(v);
  int maximum = max(v,w);
  
  if ((unsigned int) maximum + 1> adj.size()){ adj.resize(maximum + 1); }
  
  if (adj[v].empty()) { V++;}
  if (adj[w].empty()) { V++;}
  adj[v].push_back(w);
  adj[w].push_back(v);
  
}  

ostream &operator<<(ostream &os, const Weighted_Graph &G) 
{
  os << "graph: " << G.name << " {\n";
  os << " V: " << G.V << "\n";
  os << " E: " << G.E << "\n";
  os << " adjacency list = {" << "\n";
  for (auto v = 0; v < G.V; v++) {
    os << "  " << v << ": ";
    if (!G.adj[v].empty()) {
      for (auto &w : G.adj[v]) {
	os << w << " ";
      }
    }
    os << endl;
  }
  os << " }" << endl;
  os << "}" << endl;

  return os;
}

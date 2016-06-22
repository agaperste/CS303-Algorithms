#if !defined(__GRAPH_HPP)
#define __GRAPH_HPP

#include <list>
#include <string>

#include "edge.hpp"
#include "mst.hpp"

using std::list;
using std::string;
using std::vector;

// The Weighted_Graph class.

class Weighted_Graph {
  friend ostream &operator<<(ostream &os, const Weighted_Graph &G);

public:
  Weighted_Graph(string name = "G") WEAK;
  
  inline int num_edges() const {return E;}
  inline int num_vertices() const {return V;}
  void add_edge(Edge e) WEAK; // Add an edge by adding it to edges and updating the adjacency list,
                              // resizing either as needed.
  MST kruskal() const WEAK;

protected:

private:
  string name;           // The name of the graph.
  int E;                 // The number o' edges.
  int V;                 // The number o' vertices.
  vector<list<int>> adj; // The adjacency list.
  vector<Edge> edges;    // I just felt like using a linked list for the edges.  A vector would do, too.
};

ostream &operator<<(ostream &os, const Weighted_Graph &G) WEAK;

#endif
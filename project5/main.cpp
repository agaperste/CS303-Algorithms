#include "edge.hpp"
#include "graph.hpp"

using std::cin;
using std::cout;

int main (int argc, char **argv)
{
  Edge ee;
  Weighted_Graph G;

  while (cin >> ee) {
    G.add_edge(ee);
  }
  cout << G;

  MST M = G.kruskal();
  cout << M;

  return 0;
}
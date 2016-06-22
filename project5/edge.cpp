#include "edge.hpp"

int Edge::other(int vertex)
{
  if (vertex == v) {
    return w;
  }
  else if (vertex == w) {
    return v;
  }
  else { // Throw a wobbly if "vertex" is not an endpoint of this edge...
    throw std::runtime_error("Invalid edge!");
  }
}

istream &operator>>(istream &is, Edge &e) {
  is >> e.v >> e.w >> e.wt;
  return is;
}

ostream &operator<<(ostream& os, const Edge& e) {
  os << e.v << "--" << e.w << " (" << e.wt << ")";
  return os;
}
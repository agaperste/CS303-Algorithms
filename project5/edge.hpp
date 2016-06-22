#if !defined(__EDGE_HPP)
#define __EDGE_HPP

#include <iostream>
#include <stdexcept>

using std::istream;
using std::ostream;

class Edge {
  friend istream &operator>>(istream &is, Edge &e);
  friend ostream &operator<<(ostream &os, const Edge &e);

public:
  Edge () {};
  Edge (int v, int w, double weight) : v(v), w(w), wt(weight) {};

  inline double weight(void) {return wt;} // Return the weight of the edge.
  inline int either(void) {return v;}     // Return endpoint v of the edge.
  int other(int vertex) WEAK;             // Return the endpoint other than vertex.

protected:

private:
  int v, w;  // The vertices connected by the edge.
  double wt; // The weight of the edge.
};

istream &operator>>(istream &is, Edge &e) WEAK;
ostream &operator<<(ostream &os, const Edge &e) WEAK;

#endif
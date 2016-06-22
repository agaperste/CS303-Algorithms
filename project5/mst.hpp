#if !defined(__MST_HPP)
#define __MST_HPP

#include <vector>
#include <string>
#include "edge.hpp"

using std::string;

// The MST class is derived from a standard vector object.

class MST : public std::vector<Edge> { 
  friend ostream &operator<<(ostream &os, const MST &M);

public:
  MST(string name = "M") : name(name), wt(0) {};
  inline double weight() {return wt;};
  void add_edge(Edge e) WEAK; // Add an edge to the vector inherited from the base class vector<Edge> and update wt.

protected:

private:
  string name; // The name of this MST.
  double wt;   // The total weight of the MST.
};

ostream &operator<<(ostream &os, const MST &M) WEAK;

#endif
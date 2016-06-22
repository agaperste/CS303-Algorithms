#if !defined(__UNION_FIND_HPP)
#define __UNION_FIND_HPP

#include <vector>

class Union_Find {
public:
  Union_Find(int N) WEAK; // Create a union-find object for N items.

  int find (int p) WEAK;              // Component identifier for p.
  void onion (int p, int q) WEAK;     // Add a connection between p and q.
  bool connected (int p, int q) WEAK; // True if p and q are in the same component; false otherwise.

protected:

private:
  int num_components;  // No. of connected components.
  std::vector<int> id; 
  std::vector<int> sz;
};

#endif
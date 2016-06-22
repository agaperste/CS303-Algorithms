//author: Yingzhu (Jacqueline) Zhang

#include "union_find.hpp"

Union_Find::Union_Find (int N) : num_components(N), id(N), sz(N) {
  for (int i = 0; i < N; i++) {
    id[i] = i;
    sz[i] = 1;
  }
}

int Union_Find::find (int p) {
  while (p != id[p]) p = id[p];
  return p;
}

void Union_Find::onion (int p, int q) {
  int i = find(p);
  int j = find(q);
  if (i == j) return;
  
  if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
  else               { id[j] = i; sz[i] += sz[j]; }
  
  num_components--;
}

bool Union_Find::connected ( int p, int q) {
  return find(p) == find(q);
}

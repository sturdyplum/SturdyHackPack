/*
 Disjoing set amortized order one operations
*/

#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
  private: vector<int> p, r ,s;
  public:
    int numDisjoint;
    UnionFind(int N)
    {
      numDisjoint = N;
      r.assign(N, 0);
      s.assign(N,1);// this is only needed if you are going to be querying this
      p.assign(N, 0);
      for (int i = 0; i < N; i++) p[i] = i;
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }

    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    void unionSet(int i, int j)
    {
      if (!isSameSet(i, j)) // if from different set
      {
        numDisjoint--;
        int x = findSet(i), y = findSet(j);
        if (r[x] > r[y])
 {
   p[y] = x; // rank keeps the tree short
   s[x] += s[y];
 }
        else {
          p[x] = y;
          if (r[x] == r[y]) r[y]++;
 	   s[y] += s[x];
        }
      }
    }

    int sizeOfSet(int i) {return s[findSet(i)];}
};



// Two line version without rank
int find(vector<int> &C, int x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vector<int> &C, int x, int y) { C[find(C, x)] = find(C, y); }

#include <bits/stdc++.h>

using namespace std;

struct UnionFind
{
    vector<int> p, r ,s;
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



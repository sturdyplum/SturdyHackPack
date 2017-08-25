/*
    2-sat algorithm
    Complexity O(|V| + |E|)

Here maxv should be set to two times the maximum nodes since we need to represent every node in two ways (on or off). In order to extract a valid 2-sat solution we need to use the reverse topological ordering.
*/

vector<int> edge[maxv];

void set(int i, int val) {
  int must = (2 * i) | val;
  edge[must ^ 1].push_back(must);
}

void add_or(int i, int v1, int j, int v2) {
  edge[(2 * i) | (v1 ^ 1)].push_back((2 * j) | v2);
  edge[(2 * j) | (v2 ^ 1)].push_back((2 * i) | v1);
}

void add_equal(int i, int j) {
  add_or(i, 1, j, 0);
  add_or(i, 0, j, 1);
}

void add_distinct(int i, int j) {
  add_or(i, 0, j, 0);
  add_or(i, 1, j, 1);
}

// Tarjan's algorithm for strongly connected components.
int dfstime, dfsin[maxv], lowlink[maxv], ncomp, comp[maxv], stack[maxv], ss;

void scc(int v) {
  int w;
  dfsin[v] = dfstime;
  lowlink[v] = dfstime++;
  s[ss++] = v;
  for (int i = 0; i < edge[v].size(); ++i) {
    int w = edge[v][i];
    if (dfsin[w] < 0) { scc(w); lowlink[v] = min(lowlink[v], lowlink[w]); }
    else if (comp[w] < 0) lowlink[v] = min(lowlink[v], dfsin[w]);
  }
  
  if (dfsin[v] == lowlink[v]) {
    do {
      w = s[--ss];
      comp[w] = ncomp;
    } while (w != v);
    ++ncomp;
  }
}


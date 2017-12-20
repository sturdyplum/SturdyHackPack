public static class twoSat {
	ArrayList<Integer> edge[];

	int dfstime, dfsin[], lowlink[], ncomp, comp[], stack[], ss, N;
	twoSat(int N) {
		this.N = N;
		edge = new ArrayList[N*2];
		for(int i = 0; i < 2 * N; i++) {
			edge[i] = new ArrayList<>();
		}
		dfsin = new int[N*2];
		Arrays.fill(dfsin, -1);
		lowlink = new int[N*2];
		comp = new int[N*2];
		Arrays.fill(comp, -1);
		stack = new int[N*2];
	}

	void set(int i, int val) {
	  int must = (2 * i) | val;
	  edge[must ^ 1].add(must);
	}

	void add_or(int i, int v1, int j, int v2) {
	  edge[(2 * i) | (v1 ^ 1)].add((2 * j) | v2);
	  edge[(2 * j) | (v2 ^ 1)].add((2 * i) | v1);
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

	void scc(int v) {
	  int w;
	  dfsin[v] = dfstime;
	  lowlink[v] = dfstime++;
	  stack[ss++] = v;
	  for (int i = 0; i < edge[v].size(); ++i) {
	    w = edge[v].get(i);
	    if (dfsin[w] < 0) { scc(w); lowlink[v] = Math.min(lowlink[v], lowlink[w]); }
	    else if (comp[w] < 0) lowlink[v] = Math.min(lowlink[v], dfsin[w]);
	  }

	  if (dfsin[v] == lowlink[v]) {
	    do {
	      w = stack[--ss];
	      comp[w] = ncomp;
	    } while (w != v);
	    ++ncomp;
	  }
	}

	boolean validate() {
		for(int i = 0; i < 2*N; i++) {
			if(dfsin[i] == -1) scc(i);
		}
		for(int i = 0; i < N; i++) {
			if(comp[i*2] == comp[i*2+1]) return false;
		}
		return true;
	}
}

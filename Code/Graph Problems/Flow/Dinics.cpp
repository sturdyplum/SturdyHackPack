/*
 * Dinics Algorithm
 * Complexity O(V E^2)
 *
 * Unit Capcity  networks O(min(v^2/3 , e^1/2) * E)
 * Bipartite or network in which every network has
 * only one incoming node with capacity one or only
 * one outgoing node with capcity one. O(sqrt(V) * E)
 */

#include <bits/stdc++.h>

using namespace std;

const int maxnodes = 110;

int nodes = maxnodes, src, dest;
int dist[maxnodes];
bool blocked[maxnodes];
queue<int> q;


struct Edge {
  int to, rev;
  int f, cap;
  bool dir;
};

vector<Edge> g[maxnodes];

void addEdge(int s, int t, int cap){
  Edge a = {t, (int)g[t].size(), 0, cap};
  Edge b = {s, (int)g[s].size(), 0, 0};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[dest] = 0;
  q.push(dest);
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge e = g[u][j];
      int v = e.to;
      if (dist[v] < 0 && g[e.to][e.rev].f < g[e.to][e.rev].cap) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
  return dist[src] >= 0;
}

int dinic_dfs(int u, int MIN) {
  if (u == dest)
    return MIN;
  int flow = 0;
  for (int i = 0; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if(blocked[v]) continue;
    if (dist[v] < dist[u]) {
        int df = dinic_dfs(v, min(MIN, e.cap-e.f));
        flow += df;
        MIN -= df;
        e.f += df;
        g[v][e.rev].f -= df;
    }
    if(MIN == 0)
    {
        break;
    }
  }
  if(MIN > 0) blocked[u] = true;
  return flow;
}

int maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  int result = 0;
  while (dinic_bfs()) {
    fill(blocked, blocked + nodes, false);
    result += dinic_dfs(src,INT_MAX);
  }
  return result;
}


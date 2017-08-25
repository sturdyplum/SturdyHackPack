/*
    Dijkstra’s O(E + V log(V))
*/

vi dist(V, INF); dist[s] = 0; // INF = 1B to avoid overflow
priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
while (!pq.empty()) { // main loop
	ii front = pq.top(); pq.pop(); // greedy: get shortest unvisited vertex
	int d = front.first, u = front.second;
	if (d > dist[u]) continue; // this is a very important check
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j]; // all outgoing edges from u
		if (dist[u] + v.second < dist[v.first]) {
			dist[v.first] = dist[u] + v.second; // relax operation
			pq.push(ii(dist[v.first], v.first));
		} 
	}
} // this variant can cause duplicate items in the priority queue shouldn't be an issue really


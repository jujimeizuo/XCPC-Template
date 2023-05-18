template <typename T>
std::vector<std::vector<T>> bellman_ford(const graph<T>& g, int st) {
	std::vector<T> dist(g.n, std::numeric_limits<T>::max());
	dist[st] = 0;

	// Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
	for (int i = 1; i < g.n; i++) {
		for (auto& e : g.edges) {
			int from = e.from, to = e.to, cost = e.cost;
			if (dist[from] != std::numeric_limits<T>::max() && dist[from] + cost < dist[to]) {
				dist[to] = dist[from] + e.from;
			}
		}
	}

	for (auto& e : g.edges) {
		int from = e.from, to = e.to, cost = e.cost;
		if (dist[from] != std::numeric_limits<T>::max() && dist[from] + cost < dist[to]) {
			// Graph contains negative weight cycle
			return {};
		}
	}

	return dist;
}
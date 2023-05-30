#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <ostream>
#include <algorithm>

namespace dv {

struct edge {
	int u, v, cost;
	edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
};

static const std::vector<edge> initial_edges = {edge(0, 1, 1), edge(1, 2, 1), edge(2, 3, 2), edge(0, 3, 7), edge(0, 2, 3)};
static const int inf = 1e9 + 10;

class state {
public:
	state(size_t maxn = 4) : maxn(maxn) {
		dst = std::vector<std::vector<int>>(maxn, std::vector<int>(maxn, inf));
		neighbours.resize(maxn);
		need_update.resize(maxn);

		for (const auto& edge : initial_edges) {
			update(edge);
		}
	}

	void update(const edge& e) {
		neighbours[e.u][e.v] = neighbours[e.v][e.u] = e.cost;
		recalc(e.v);
		recalc(e.u);

		while (!updating_queue.empty()) {
			auto v = updating_queue.front();
			recalc(v);
			updating_queue.pop();
		}
	}

	void print_distances(std::ostream& out) {
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				if (dst[i][j] == inf) {
					out << "inf "; 
				} else {
					out << dst[i][j] << ' ';
				}
			}
			out << std::endl;
		}
	}

private:
	void recalc(int v) {
		auto old_dst = dst[v];

		std::vector<int> new_dst(maxn, inf);
		new_dst[v] = 0;

		for (auto [u, cost] : neighbours[v]) {
			for (int w = 0; w < maxn; w++) {
				new_dst[w] = std::min(new_dst[w], cost + dst[u][w]);
			}
		}

		need_update[v] = false;

		if (old_dst != new_dst) {
			dst[v] = new_dst;
			for (auto [u, _] : neighbours[v]) {
				if (!need_update[u]) {
					need_update[u] = true;
					updating_queue.push(u);
				}
			}

		}
	}

	std::vector<std::vector<int>> dst;
	std::vector<std::unordered_map<int, int>> neighbours;
	std::vector<bool> need_update;
	std::queue<int> updating_queue;
	size_t maxn;
};

}
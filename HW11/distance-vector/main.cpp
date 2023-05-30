#include "dv.hpp"
#include <iostream>
#include <vector>

int main() {
	dv::state current;
	current.print_distances(std::cout);

	while (true) {
		int u, v, cost;
		std::cin >> u >> v >> cost;
		if (!u && !v) {
			break;
		}

		current.update(dv::edge(u, v, cost));

		std::cout << std::endl;
		current.print_distances(std::cout);
	}
}
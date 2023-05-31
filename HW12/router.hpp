#pragma once

#include <string>
#include <mutex>
#include <unordered_map>
#include <queue>
#include <string_view>
#include <ostream>

namespace rip {

class router;

struct path_info {
	int len;
	router* next_router;

	bool operator==(const path_info& other) const {
		return len == other.len && next_router == other.next_router;
	}
};

class router {
public:
	router(const std::string& ip_address, std::mutex& net_sync, int& rem) : ip_address(ip_address),  net_sync(net_sync), remaining_events(rem) {}

	router(const router& other) : ip_address(other.ip_address), neighbours(other.neighbours), table(other.table),
		neighbour_table(other.neighbour_table), net_sync(other.net_sync), remaining_events(other.remaining_events) {
		
		queue_sync.lock();
		updating_queue = other.updating_queue;
		queue_sync.unlock();
	}

	void add_neighbour(router* neighbour) {
		neighbours.emplace_back(neighbour);
		neighbour_table[neighbour] = {};
	}

	void update_neighbour(router* updated_neighbour, const std::unordered_map<router*, path_info>& nb_table) {
		std::lock_guard<std::mutex> lock(queue_sync);
		updating_queue.push({updated_neighbour, nb_table});
	}

	std::string_view get_ip() const {
		return ip_address;		
	}

	void run(std::ostream& out) {
		recalc();

		auto iteration_number = 0;

		net_sync.lock();

		out << get_header_partial(iteration_number++) << std::endl;
		print_table(out);
		
		net_sync.unlock();

		while (true) {
			if (!remaining_events) {
				break;
			}

			if (!updating_queue.empty()) {
				queue_sync.lock();
				auto [neighbour, nb_table] = updating_queue.front();
				updating_queue.pop();
				queue_sync.unlock();

				neighbour_table[neighbour] = nb_table;
				recalc();

				net_sync.lock();
				out << get_header_partial(iteration_number++) << std::endl;
				print_table(out);
				remaining_events--;
				net_sync.unlock();

				if (!remaining_events) {
					break;
				}
			} 
		}

		net_sync.lock();

		out << get_header_final() << std::endl;
		print_table(out);

		net_sync.unlock();
	}

private:
	const std::string ip_address;
	std::mutex& net_sync;
	std::mutex queue_sync;
	std::vector<router*> neighbours;
	std::queue<std::pair<router*, std::unordered_map<router*, path_info>>> updating_queue;
	std::unordered_map<router*, path_info> table;
	std::unordered_map<router*, std::unordered_map<router*, path_info>> neighbour_table;
	int& remaining_events;

	void recalc() {
		std::unordered_map<router*, path_info> new_table;
		new_table[this] = {0, this};

		for (const auto& neighbour : neighbours) {
			for (const auto &[router, info] : neighbour_table[neighbour]) {
				if (!new_table.count(router) || 1 + info.len < new_table[router].len) {
					new_table[router] = {1 + info.len, neighbour};
				}
			}
		}

		if (new_table != table) {
			net_sync.lock();
			remaining_events += neighbours.size();
			net_sync.unlock();

			table = new_table;
			for (const auto& neighbour : neighbours) {
				neighbour->update_neighbour(this, table);
			}		
		}
	}

	void print_table(std::ostream& out) {
		out << "[Source IP]     [Destination IP]        [Next hop]        [Distance]" << std::endl;
		for (const auto& [router, info] : table) {
			out << ip_address << " " << router->get_ip() << "         " << info.next_router->get_ip() << "   " << info.len << std::endl;
		}
		out << std::endl;
	}

	std::string get_header_partial(int iteration_number) const {
		return "Simulation step " + std::to_string(iteration_number) + " of router " + ip_address; 
	}

	std::string get_header_final() const {
		return "Final state of router " + ip_address;
	}
};	

}
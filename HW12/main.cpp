#include "router.hpp"
#include "json.hpp"
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <thread>
#include <stdexcept>
#include <fstream>

using json = nlohmann::json;

namespace {

std::string add_spaces(const std::string& ip) {
	return ip + std::string(15 - ip.size(), ' ');
}

}

int main(int argc, char* argv[]) {
	try {
		if (argc < 2) {
			throw std::invalid_argument("Please, specify config file");
		}

		std::ifstream f(argv[1]);
		json data = json::parse(f);

		std::vector<std::string> ips;
		for (const auto& ip : data["ips"]) {
			ips.emplace_back(ip.get<std::string>());
		}

		std::vector<std::pair<std::string, std::string>> edges;
		for (const auto& edge : data["edges"]) {
			edges.emplace_back(edge[0].get<std::string>(), edge[1].get<std::string>());
		}

		int events_remaining = 0;
		std::mutex net_sync;
		std::vector<std::unique_ptr<rip::router>> routers;
		std::unordered_map<std::string, rip::router*> ptr;
		
		for (const auto& ip : ips) {
			auto ip_arg = add_spaces(ip);

			routers.emplace_back(std::make_unique<rip::router>(rip::router(ip_arg, net_sync, events_remaining)));
			ptr[ip] = routers.back().get();
		}

		for (auto [ip1, ip2] : edges) {
			ptr[ip1]->add_neighbour(ptr[ip2]);
			ptr[ip2]->add_neighbour(ptr[ip1]);
		}

		std::vector<std::thread> workers;
		for (auto& router : routers) {
			workers.emplace_back([&router]() {
				router.get()->run(std::cout);
			});
		}

		for (auto& worker : workers) {
			worker.join();
		}	
	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}
	
}
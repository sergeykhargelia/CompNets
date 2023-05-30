#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dv.hpp"
#include <sstream>

TEST_CASE("initialization") {
	std::ostringstream out;
	dv::state current;
	
	current.print_distances(out);
	
	CHECK(out.str() == "0 1 2 4 \n1 0 1 3 \n2 1 0 2 \n4 3 2 0 \n");
}

TEST_CASE("update 1") {
	std::ostringstream out;
	dv::state current;
	
	current.update(dv::edge(0, 3, 1));
	current.print_distances(out);
	
	CHECK(out.str() == "0 1 2 1 \n1 0 1 2 \n2 1 0 2 \n1 2 2 0 \n");
}

TEST_CASE("update 2") {
	std::ostringstream out;
	dv::state current;

	current.update(dv::edge(0, 3, 1));
	current.update(dv::edge(1, 2, 10));
	current.print_distances(out);

	CHECK(out.str() == "0 1 3 1 \n1 0 4 2 \n3 4 0 2 \n1 2 2 0 \n");
}

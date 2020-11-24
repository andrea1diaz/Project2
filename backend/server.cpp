#include <iostream>
#include <served/served.hpp>
#include "json.hpp"

#include "data_processor.h"


int main (int aargc, const char *argv[]) {
	data_processor process_data("stopwords.txt");

	process_data.add("data.txt");
	process_data.add("data1.txt");
	process_data.add("data2.txt");


	served::multiplexer mux;
    mux.handle("/api/collection/list")
        .get([&](served::response &res, const served::request &req) {
            std::string name = req.query["name"];
            res.set_header("content-type", "application/json");
			res << process_data.get_collections().str();
        });
	
    served::net::server server("0.0.0.0", "5000", mux);
	std::cout << "Running on port 5000\n";
    server.run(10);

    return (1);
}

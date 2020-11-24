#include <iostream>
#include <served/served.hpp>

#include "data_processor.h"


int main (int aargc, const char *argv[]) {
	data_processor process_data("stopwords.txt");

	process_data.add("data.txt");
	process_data.add("data1.txt");
	process_data.add("data2.txt");


	served::multiplexer mux;
	
	mux.handle("/api")
		.get([&](served::response &res, const served::request &req) {
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
			res.set_header("Access-Control-Allow-Headers", "append,delete,entries,foreach,get,has,keys,set,values,Authorization, X-Requested-With, content-type");
			res.set_body("hello second world");

		});

    mux.handle("/api/collection/list")
        .get([&](served::response &res, const served::request &req) {
			res.set_header("Access-Control-Allow-Headers", "append,delete,entries,foreach,get,has,keys,set,values,Authorization, X-Requested-With, content-type");
            res.set_header("content-type", "application/json");
			res.set_header("Access-Control-Allow-Credentials", "true");
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
			res.set_body("hello second world");
			res << process_data.get_collections().str();
        });
		
	
    served::net::server server("0.0.0.0", "5000", mux);
	std::cout << "Running on port 5000\n";
    server.run(10);

    return (1);
}

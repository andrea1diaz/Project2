#include <iostream>
#include <served/served.hpp>

#include "data_processor.cpp"
#include "porter_stemming.cpp"


int main (int aargc, const char *argv[]) {
	data_processor process_data("stopwords.txt");

	process_data.add("data.txt");
	process_data.add("data1.txt");
	process_data.add("data2.txt");


	served::multiplexer mux;
    mux.handle("/api/get-list")
        .get([&](served::response &res, const served::request &req) {
            std::string name = req.query["name"];
            res.set_header("content-type", "application/json");
            res << "{ \"content\": \"Hello, " << ((name.length() > 0) ? name : "world") << "!\" }\n";
        });

    std::cout << "Try this example with:" << std::endl;
    std::cout << "  curl \"http://localhost:8123/api/v1/greeting?name=world\"" << std::endl;

    served::net::server server("0.0.0.0", "8081", mux);
    server.run(10);

    return (1);
}

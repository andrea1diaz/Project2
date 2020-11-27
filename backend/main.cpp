
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "data_processor.cpp"
#include "porter_stemming.cpp"

int main () {
	//std::cout << "processing data...\n";
	data_processor process_data;
	
	//process_data.write_index();
	//std::cout << "finished processing data\n";
	
	std::string to_find;
	//std::cout << "ready for search\n";

		std::cin >> to_find;
		process_data.find(to_find);

	return 0;
}

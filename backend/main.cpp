
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "data_processor.cpp"
#include "porter_stemming.cpp"

int main () {
	data_processor process_data("stopwords.txt");

	process_data.add("data.txt");
	process_data.add("data1.txt");
	process_data.add("data2.txt");


	return 0;

	/*inverted_index recovery;
	
	recovery.add("data.txt", process_data.most_used_words());
	recovery.save_to("data_index.txt");

	recovery.add("data1.txt", process_data1.most_used_words());
	recovery.save_to("data_index.txt");

	recovery.add("data2.txt", process_data1.most_used_words());
	recovery.save_to("data_index.txt");

	std::vector<std::string> result2 = AND(recovery.L("Frodo"), recovery.L("Frodo"), recovery.L("Mirror"));

	
	for (auto i : result2) {
		std::cout << i << '\n';
	}
	return 0;*/
}

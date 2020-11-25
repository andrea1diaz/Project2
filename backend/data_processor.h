#pragma once

#include "porter_stemming.h"
#include "structs.h"

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <sstream>


class data_processor {
public:
	data_processor();
	data_processor(char *);

	void add_stopwords();
	bool stoplist(std::string, int, Block*);
	void calc_tf_idf();
	void calc_doc_score();
	
	std::string stemming(std::string word);
	
private:
	porter_stemming ps;
	int number_of_blocks;
	std::unordered_map<std::string, bool> stopwords;
	std::unordered_map<std::string, bool> signs;
	std::unordered_map<std::string, std::unordered_map<int, int>> index;

};

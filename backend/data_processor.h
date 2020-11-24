#pragma once

#include "porter_stemming.h"

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <sstream>

struct Word {
	std::unordered_map<int, int> collection_id;
	std::vector<int> counts_in_collection; // how many times it appears in a doc
	std::vector<double> tf_idf;

	void calc_tf_idf (int number_of_collections) {
		double idf = log10 (number_of_collections / collection_id.size());
	
		for (int i = 0; i < counts_in_collection.size(); ++i) {
			double tf = 1 + log10(counts_in_collection[i]);

			tf_idf.push_back(tf * idf);
		}
	}
};

struct Collection {
	std::string name;
	int total_words;
	int vocabulary_count;
	double score;

	Collection () {
		total_words = vocabulary_count = score = 0;
	}
};

class data_processor {
public:
	data_processor();
	data_processor(char *);

	void add(std::string);
	bool stoplist(std::string, int);
	void calc_tf_idf();
	void calc_doc_score();
	std::stringstream get_collections();

	std::vector<std::string> most_used_words();
	std::string stemming(std::string word);
	
	std::unordered_map<std::string, Word*> cleaned_data;
	std::unordered_map<int, Collection*> collection;
	
	int number_of_collections;
private:
	porter_stemming ps;
	std::unordered_map<std::string, bool> stopwords;
	std::unordered_map<std::string, bool> signs;
};

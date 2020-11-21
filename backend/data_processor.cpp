#include "data_processor.h"

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <numeric>

data_processor::data_processor(char *stopwords_file) {
	number_of_collections = 0;
	std::fstream file (stopwords_file);
	std::string word;

	while (file >> word) {
		stopwords.insert({word, 0});
	}

	signs.insert({{"¡", 0}, {"!", 0}, {"¿", 0}, {"?", 0 }, {".", 0}, {",", 0}, {";", 0},
				  {"@", 0}, {"%", 0}, {"^", 0}, {"[", 0}, {"]", 0}, {"{", 0}, {"}", 0},
				  {"`", 0}, {"'", 0}, {"‘", 0}, {"’", 0}, {":", 0}, {"(", 0}, {")", 0},
				  {"’s", 0}, {"‘", 0}});
	
	file.close();
}


void data_processor::add (std::string to_clean) {
	number_of_collections ++;

	Collection col;

	col.name = to_clean;
	collection.insert ({number_of_collections, col});

	bool worked = stoplist(to_clean, number_of_collections);
}

bool data_processor::stoplist(std::string to_clean, int collection_id) {
	std::fstream file (to_clean);
	std::string word;

	int vocabulary_count = 0;
	int total_words = 0;


	while (file >> word) {
		std::transform(word.begin(), word.end(), word.begin(),
    [](unsigned char c){ return std::tolower(c); });

		if (signs.find(std::string(1, word.back())) != signs.end())
			word.pop_back();

		if (signs.find(std::string(1, word.front())) != signs.end())
			word.erase(0, 1);

		if (stopwords.find(word) == stopwords.end()) {
			word = stemming(word);

			if (cleaned_data.find(word) != cleaned_data.end()) {
				auto w = cleaned_data.find(word)->second;

				if (w.collection_id.find(collection_id) == w.collection_id.end()) {
					w.collection_id.insert({collection_id, w.collection_id.size() - 1});
					w.counts_in_collection.push_back(1);
				}

				int i = w.counts_in_collection.size() - 1;
				cleaned_data.find(word)->second.counts_in_collection[i] += 1;
			}

			else {
				Word to_add;
				
				to_add.collection_id.insert ({collection_id, 0});
				to_add.counts_in_collection.push_back (1);

				cleaned_data.insert({word, to_add});
				vocabulary_count ++;
			}
		}

		total_words ++;
	}

	auto it = collection.find (collection_id)->second;

	it.total_words = total_words;
	it.vocabulary_count = vocabulary_count;

	file.close();

	return 1;
}


std::string data_processor::stemming (std::string word) {
	std::transform(word.begin(), word.end(), word.begin(),
		[](unsigned char c){ return std::tolower(c); });

	char *cstr = new char[word.length() + 1];
	strcpy(cstr, word.c_str());

	return ps.stemming(cstr, 0, word.length() - 1);
}


void data_processor::calc_tf_idf () {
	for (auto i : cleaned_data) {
		Word w = i.second;

		w.calc_tf_idf (number_of_collections);
	}
}


void data_processor::calc_doc_score () {
	for (auto w : cleaned_data) {
		for (int i = 0; i < w.second.tf_idf.size(); ++i) {
			auto c = collection.find(w.second.collection_id[i])->second;
			c.score += w.second.tf_idf[i];
		}
	}	
}


double cosine_similarity (std::vector<int> a, std::vector<int> b) {
	return std::inner_product (a.begin(), a.end(), b.begin(), 0);
}


bool sortbysec(const std::pair<std::string, int> &a, 
              const std::pair<std::string, int> &b) { 
    return (a.second > b.second); 
}


/*
std::vector<std::string> data_processor::most_used_words () {
	std::vector<std::pair<std::string, int>> tmp(cleaned_data.begin(), cleaned_data.end());

	std::sort(tmp.begin(), tmp.end(), sortbysec);

	std::vector<std::string> result;
	int size = 500;

	if (cleaned_data.size() < size) size = cleaned_data.size();

	for (int i = 0; i < size; ++i) {
		result.push_back(tmp[i].first);
	}

	return result;
} 
*/

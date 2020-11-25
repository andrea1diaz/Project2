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
#include <sstream>
#include <filesystem>

#include <boost/property_tree/json_parser.hpp>

namespace fs = std::filesystem;

data_processor::data_processor () {
	add_stopwords ();

	std::string path_ = "docs/";
	std::vector<std::string> doc_list;

	for (const auto & entry : fs::directory_iterator(path_))
		doc_list.push_back(entry.path());

	int number_of_docs = doc_list.size();
	int docs_per_block = number_of_docs / log(number_of_docs);

	for (int i = 0; i < number_of_docs; i += docs_per_block) {
		int size;

		if (i + docs_per_block < number_of_docs) size = docs_per_block;
		else size = number_of_docs - i - 1;

		Block *block = new Block(i);
	
		for (int j = 0; j < size; ++j) {
			block->docs.insert ({doc_list[i + j], 0});
			stoplist (doc_list[i + j], i + j, block);
		}

		block->write_block (number_of_docs);
	}

}

void data_processor::add_stopwords () {
	std::string stopwords_file = "stopwords.txt";
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

bool data_processor::stoplist(std::string to_clean, int doc_id, Block *block) {
	std::fstream file;
	file.open(to_clean);
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

			if (index.find(word) == index.end()) {
				std::unordered_map<int, int> b;
				b.insert ({block->block_id, 0});

				index.insert ({word, b});
			}

			else {
				if (index[word].find(block->block_id) == index[word].end()) {
					index[word].insert({block->block_id, 0});
				}
			}

			if (block->words.find(word) != block->words.end()) {
				if (block->docs.find(to_clean) == block->docs.end()) {
					block->in_docs.find(word)->second.push_back(doc_id);
					block->word_counts.find(word)->second.push_back(1);
				}

				else  {
					block->word_counts[word][block->in_docs[word].size() - 1] += 1;
				}
	
			}

			else {
				std::vector d {doc_id};
				std::vector c {1};
				
				block->words.insert ({word, block->words.size()});
				block->word_counts.insert ({word, c});
				block->in_docs.insert ({word, d});
				block->docs.find (to_clean)->second += 1;
			
			}
		}
	}

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

void data_processor::write_index () {
	std::fstream file;
	std::string filename = "index/";

	filename += "index.json";

	file.open (filename, std::ios::out);

	file << "{\n";
	
	int j = 1;
	for (auto i : index) {
		file << "\"" << i.first << "\": [";
		
		int z = 1;
		for (auto j : i.second) {
			file <<  j.first;
			if (z < i.second.size()) file << ", ";
			z++;
		}
		
		if (j < index.size()) file << "],\n";
		else file << "]\n";

		j++;
	}
		
	file << "}";

	file.close();
}


double cosine_similarity (std::vector<int> a, std::vector<int> b) {
	return std::inner_product (a.begin(), a.end(), b.begin(), 0.0L) / sqrt(std::inner_product(a.begin(), a.end(), a.begin(), 0.0L)) * sqrt(std::inner_product(b.begin(), b.end(), b.begin(), 0.0L));
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

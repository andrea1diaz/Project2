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

	std::string path_ = "/Users/andreadiaz/Library/Mobile Documents/com~apple~CloudDocs/utec/data-bases-2/Project2/backend/docs";
	std::vector<std::string> doc_list;

	for (const auto & entry : fs::directory_iterator(path_))
		doc_list.push_back(entry.path());

	number_of_docs = doc_list.size();
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

		block->write_block ();
		blocks.push_back (block);
	}

}

void data_processor::add_stopwords () {
	std::string stopwords_file = "stopwords.txt";
	number_of_docs = 0;
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

/*
void data_processor::add (std::string to_clean) {
	number_of_docs ++;

	Document *doc = new Document;

	doc->name = to_clean;
	documents.insert ({number_of_docs, doc});

	bool worked = stoplist(to_clean, number_of_docs);
}*/

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

			if (cleaned_data.find(word) != cleaned_data.end()) { 
				auto w = cleaned_data.find(word)->second;

				if (block->words.find(word) == block->words.end()) {

					std::vector d {doc_id};
					std::vector c {1};

					block->words.insert ({word, block->words.size()});
					block->in_docs.insert ({word, d});
					block->word_counts.insert ({word, c});
					block->docs[to_clean] += 1;

				}

				else {
					if (block->docs.find(to_clean) == block->docs.end()) {
						block->in_docs.find(word)->second.push_back(doc_id);
						block->word_counts.find(word)->second.push_back(1);
					}

					else  {
						block->word_counts[word][block->in_docs[word].size() - 1] += 1;
					}
				}

				if (w->doc_id.find(doc_id) == w->doc_id.end()) {

					w->doc_id.insert({doc_id, w->doc_id.size() - 1});
					w->counts_in_doc.push_back(1);
				}

				int i = w->counts_in_doc.size() - 1;
				cleaned_data.find(word)->second->counts_in_doc[i] += 1;
			}

			else {
				Word *to_add = new Word;
				std::vector d {doc_id};
				std::vector c {1};
				
				to_add->doc_id.insert ({doc_id, 0});
				to_add->counts_in_doc.push_back (1);

				cleaned_data.insert ({word, to_add});

				block->words.insert ({word, block->words.size()});
				block->word_counts.insert ({word, c});
				block->in_docs.insert ({word, d});
				block->docs.find (to_clean)->second += 1;

				vocabulary_count ++;

			}
		}

		total_words ++;
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




void data_processor::calc_tf_idf () {
	for (auto i : cleaned_data) {
		Word *w = i.second;

		w->calc_tf_idf (number_of_docs);
	}
}

/*
void data_processor::calc_doc_score () {
	for (auto w : cleaned_data) {
		for (int i = 0; i < w.second->tf_idf.size(); ++i) {
			auto d = documents.find(w.second->doc_id[i])->second;
			d->score += w.second->tf_idf[i];
		}
	}	
}*/


double cosine_similarity (std::vector<int> a, std::vector<int> b) {
	return std::inner_product (a.begin(), a.end(), b.begin(), 0.0L) / sqrt(std::inner_product(a.begin(), a.end(), a.begin(), 0.0L)) * sqrt(std::inner_product(b.begin(), b.end(), b.begin(), 0.0L));
}


bool sortbysec(const std::pair<std::string, int> &a, 
              const std::pair<std::string, int> &b) { 
    return (a.second > b.second); 
}

std::stringstream data_processor::get_documents () {
	boost::property_tree::ptree root;
	std::stringstream ss;

	for (auto i : documents) {
		boost::property_tree::ptree aux;
		std::string id = std::to_string(i.first);
		auto d = i.second;

		aux.put("name", d->name);
		aux.put("total_words", d->total_words);
		aux.put("vocabulary_count", d->vocabulary_count);
		
		root.push_back(std::make_pair(id, aux));
	}
	
	
	// Export JSON response
	boost::property_tree::json_parser::write_json(ss, root, true /* human */);

	return ss;
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

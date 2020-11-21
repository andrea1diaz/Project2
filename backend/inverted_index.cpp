#include "inverted_index.h"
#include "node.h"
#include "data_processor.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

inverted_index::inverted_index () {}

void inverted_index::add(std::string filename, std::string word) {
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	
	filelist.push_back(filename);

	node new_node(filename);

	Dictionary[word].push_back(new_node);
}

void inverted_index::add(std::string filename, std::vector<std::string> word_vector) {
	for (auto i : word_vector) {
		add(filename, i);
	}
}


void inverted_index::find(std::string word) {
	if (Dictionary.find(word) != Dictionary.end()) {
		int len = (int)Dictionary[word].size();

		for (int i = 0; i < len; ++i) {
			std::cout << Dictionary[word][i].filename << '\n';
		}
	}

	else std::cout << "word not found\n";
}



bool sortby(const std::pair<std::string, std::vector<node>> &a, 
              const std::pair<std::string, std::vector<node>> &b) { 
    return (a.first < b.first); 
}


void inverted_index::save_to(std::string filename) {
	std::vector<std::pair<std::string, std::vector<node>>> tmp(Dictionary.begin(), Dictionary.end());
	
	std::sort(tmp.begin(), tmp.end(), sortby);

	std::fstream file(filename, std::ios::out);
	
	for (int i = 0; i < tmp.size(); ++i) {
		file << tmp[i].first << ": ";
	
		int len = (int)tmp[i].second.size();

		for (int j = 0; j < len; ++j) {
			file << tmp[i].second[j].filename << " ";
		}

		file << '\n';
	}

	file.close();
}


std::vector<std::string> AND(std::vector<std::string> vec, std::vector<std::string> vec2) {
	std::vector<std::string> result;
	std::vector<std::string>::iterator it, ot;
	ot = vec.begin();

	std::set_intersection(vec.begin(), vec.end(), vec.begin(), vec2.end(), std::back_inserter(result));

	return result;
}

template <typename... Args>
std::vector<std::string> AND(std::vector<std::string> vec, std::vector<std::string> vec2, Args... args) {
	std::vector<std::string> result;
	std::vector<std::string>::iterator it, ot;

	ot = vec.begin();

	std::set_intersection(vec.begin(), vec.end(), vec.begin(), vec2.end(), std::back_inserter(result));

	return AND(result, args...);
}

std::vector<std::string> inverted_index::L(std::string word) {
	word = dp.stemming(word);

	std::vector<std::string> result;

	if (Dictionary.find(word) != Dictionary.end()) {
		int len = (int)Dictionary[word].size();

		for (int i = 0; i < len; ++i) {
			result.push_back(Dictionary[word][i].filename);
		}
	}

	return result;
}

template <typename T>
std::vector<std::string> OR(T vec1, T vec2) {
	std::vector<std::string> result;
	std::vector<std::string>::iterator it;

	std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(result));

	it = std::unique(result.begin(), result.end());

	return result;
}

template <typename T, typename... Args>
std::vector<std::string> OR(T vec1, T vec2, Args... args) {
	std::vector<std::string> result;
	std::vector<std::string>::iterator it;

	std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(result));

	it = std::unique(result.begin(), result.end());

	return OR(result, args...);
}


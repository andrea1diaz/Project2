#pragma once

#include "node.h"
#include "data_processor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class inverted_index {
public:
	inverted_index();

	void add(std::string filename, std::string word);
	void add(std::string filename, std::vector<std::string> word_vector);
    void find(std::string word);
	void save_to(std::string filename);
	
	std::vector<std::string> AND(std::vector<std::string> vec1, std::vector<std::string> vec2);

	template <typename... Args>
	std::vector<std::string> AND(std::vector<std::string> vec1, std::vector<std::string> vec2, Args... args);

	std::vector<std::string> L(std::string word);

	template <typename T>
	std::vector<std::string> OR(T vec1, T vec2);

	template <typename T, typename... Args>
	std::vector<std::string> OR(T vec1, T vec2, Args... args);


private:
	std::unordered_map<std::string, std::vector<node>> Dictionary;
	std::vector<std::string> filelist;
	data_processor dp;
};



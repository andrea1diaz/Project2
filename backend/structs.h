#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <math.h>

struct Block {
	std::unordered_map<std::string, int> words;
	std::unordered_map<std::string, std::vector<int>> in_docs;
	std::unordered_map<std::string, std::vector<int>> word_counts;
	std::unordered_map<std::string, int> docs;
	int block_id;

	Block (int id) { block_id = id; }

	void write_block (int number_of_docs) {
		std::fstream file;
		std::string filename = "/Users/andreadiaz/Library/Mobile Documents/com~apple~CloudDocs/utec/data-bases-2/Project2/backend/input/";

		filename += std::to_string(block_id);
		filename += ".json";

		file.open (filename, std::ios::out);

		file << "{\n";
		file << "\t\"docs\": {\n";
		for (auto i : docs) {
			file << "\t\t\"" << i.second << "\" : {\n";
			file << "\t\t\t\"name\": " << i.first << "\n\t\t\t},\n";
		}
		file << "\t\t},\n";
		file << "\t\"words\" : {\n";
		for (auto i : word_counts) {
			file << "\t\t\"" << i.first << "\" : {\n";
			double idf = log10(number_of_docs / in_docs[i.first].size());
			file << "\t\t\t\"idf\": " << idf << ",\n";
			file << "\t\t\t\"tf\": {\n";
			for (int j = 0; j < i.second.size(); ++j) {
				file << "\t\t\t\t\"" << in_docs[i.first][j] << "\": " << 1 + log10(i.second[j]) << ",\n";
			}
			file << "\t\t\t},\n";
			file << "\t\t\t\"tf_idf\": {\n";
			for (int j = 0; j < i.second.size(); ++j) {
				file << "\t\t\t\t\"" << in_docs[i.first][j] << "\": " << (double) (1 + log10(i.second[j])) * idf << ",\n";
			}
			file << "\t\t\t}\n";
			file << "\t\t},\n";

		}

		file <<	"\t}\n}";

		file.close();
	}
};

struct Word {
	std::unordered_map<int, int> doc_id;
	std::vector<int> counts_in_doc; // how many times it appears in a doc
	std::vector<double> tf_idf;

	void calc_tf_idf (int number_of_docs) {
		double idf = log10 (number_of_docs / doc_id.size());
	
		for (int i = 0; i < counts_in_doc.size(); ++i) {
			double tf = 1 + log10(counts_in_doc[i]);

			tf_idf.push_back(tf * idf);
		}
	}
};

struct Document {
	std::string name;
	int total_words;
	int vocabulary_count;

	Document () {
		total_words = vocabulary_count = 0;
	}

	Document (std::string n) {
		total_words = vocabulary_count = 0;

		name = n;
	}
};

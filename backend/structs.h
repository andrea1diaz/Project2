#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

struct Block {
	std::unordered_map<std::string, int> words;
	std::unordered_map<std::string, std::vector<int>> in_docs;
	std::unordered_map<std::string, std::vector<int>> word_counts;
	std::unordered_map<std::string, int> docs;
	int block_id;

	Block (int id) { block_id = id; }

	void write_block () {
		std::fstream file;
		std::string filename = "/Users/andreadiaz/Library/Mobile Documents/com~apple~CloudDocs/utec/data-bases-2/Project2/backend/input/";

		filename += std::to_string(block_id);
		filename += ".json";

		file.open (filename, std::ios::out);

		file << "{\n";
		file << "\t\"docs\": {\n";
		for (auto i : docs) {
			file << "\t\t\"" << i.first << "\" : {\n";
			file << "\t\t\t\"vocab_count\": " << i.second << "\n\t\t},\n";
		}
		file << "\t\t},\n";
		file << "\t\"words\" : {\n";
		for (auto i : word_counts) {
			file << "\t\t\"" << i.first << "\" : {\n";
			for (int j = 0; j < i.second.size(); ++j) {
				file << "\t\t\t\"" << j << "\": " << i.second[j] << ",\n";
			}
			file << "\t\t},\n";
		}

		file << "\t\t\"in_docs\": {\n";

		for (auto i : in_docs) {
			file << "\t\t\t\"" << i.first << "\": [\n";
			for (int j = 0; j < i.second.size(); ++j) {
				file << i.second[j] << ", ";
			}
			file << "\t\t\t],\n";
		}
		
		file << "}";

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

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
		std::string filename = "index/";

		filename += std::to_string(block_id);
		filename += ".json";

		file.open (filename, std::ios::out);

		file << "{";
		file << "\"docs\":{";
		int j = 1;
		for (auto i : docs) {
			file << "\"" << i.second << "\":\"" << i.first << "\"";
			
			if (j < docs.size()) file << ",";
			j++;

			//file << "\t\t\t\"name\": " << i.first << "\n\t\t\t},\n";
		}
		file << "},";
		file << "\"words\":{";

		int q = 1;
		for (auto i : word_counts) {
			file << "\"" << i.first << "\":{";
			double idf = log10(number_of_docs / in_docs[i.first].size());
			file << "\"idf\":" << idf << ",";
			file << "\"tf\":{";
			std::multiset<std::pair<double, int>> tf;
			std::multiset<std::pair<double, int>>::iterator it;
			
			int z = 1;
			for (int j = 0; j < i.second.size(); ++j) {
				file << "\"" << in_docs[i.first][j] << "\":" << 1 + log10(i.second[j]);
				if (z < i.second.size()) file << ",";
				z++;
				
				std::pair<double, int> p ((double)(1 + log10(i.second[j])),	in_docs[i.first][j]);
				tf.emplace(p);
			}
			file << "},";
			file << "\"tfidf\":{";

			int x = 1;
			for (std::multiset<std::pair<double, int>>::iterator it = tf.begin(); it != tf.end(); ++it) {
				file << "\"" << it->second << "\":" << it->first * idf;
				if (x < tf.size()) file << ",";
				x++;
			}
			file << "}";

			if (q < words.size()) file << "},";
			q++;

		}

		file <<	"}}}";

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

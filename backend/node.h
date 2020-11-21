#include <iostream>
#include <string>

struct node {
	int size;
	std::string filename;
	bool word;
	node* next[20];
	int idf;

	node() {
		size = 20;
	}

	node(std::string filename) {
		size = 20;

		this->filename = filename;
	}
};

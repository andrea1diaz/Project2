#pragma once

#include <iostream>
#include <string>

class porter_stemming {
public:
	porter_stemming ();

	bool consonant (int i);
	int consonant_sequence ();
	bool thers_vowel();
	bool thers_double_consonant (int i);
	bool consonant_vowel_consonant (int i);
	bool ends_with(char *word);
	void readjust(char *word);
	void replace(char *word);
	void remove_plurals();
	void vowelize();
	void sufix();
	void sufix2();
	void sufix3();
	void sufix4();
	std::string stemming(char *p, int i, int j);

	char *buffer;
	int offset_i;
	int	offset_j;
	int end;
};

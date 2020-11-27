#pragma warning( push )
#pragma warning( disable : 4101)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"

#include "porter_stemming.h"

#include <string.h>

porter_stemming::porter_stemming() {
	buffer = new char[10000000];
	end = offset_i = offset_j = 0;
}

// checks if the letter is a consonant 
bool porter_stemming::consonant(int i) {
	switch (buffer[i]) {
		case 'a':
			return 0;

		case 'e':
			return 0;

		case 'i':
			return 0;

		case 'o':
			return 0;

		case 'u':
			return 0;

		case 'y': // sometimes the 'y' works as a vowel
			return (i == offset_i) ? 0 : !consonant(i - 1);

		default:
			return 1;
	}	
}


// number of consonant sequences between offset_i and offset_j
int porter_stemming::consonant_sequence () {
	int counter = 0;
	int i = offset_i;
	
	while (consonant(i)) { // find the first vowel
		if (i > offset_j) return counter;

		i++;
	}

	i++;

	while (1) { // finds the sequence
		while (!consonant(i)) { // skip the vowels
			if (i > offset_j) return counter;

			i++;
		}

		i++;
		counter++;

		while (consonant(i)) { // find the next vowel
			if (i > offset_j) return counter;

			i++;
		}

		i++;
	}
}

// shows if there is a vowel between offset_i and offset_j
bool porter_stemming::thers_vowel () {
	for (int i = offset_i; i <= offset_j; ++i) {
		if (!consonant(i)) return 1;
	}

	return 0;
}


bool porter_stemming::thers_double_consonant(int i) {
	if (i < offset_i + 1) return 0;

	if (buffer[i] != buffer[i - 1]) return 0;

	return consonant(i);
}



// will ignore the x, w and y
bool porter_stemming::consonant_vowel_consonant(int i) {
	if (i < offset_i + 2) return 0;

	if (!consonant(i)) return 0;

	if (consonant(i - 1)) return 0;

	if (!consonant(i - 2)) return 0;

	switch (buffer[i]) {
		case 'w':
			return 0;
		
		case 'x':
			return 0;

		case 'y':
			return 0;

		default:
			return 1;
	}
}


bool porter_stemming::ends_with(char *word) {
	int word_length = word[0];

	if (word[word_length] != buffer[end]) return 0;
	
	if (word_length > end - offset_i + 1) return 0;

	if (memcmp(buffer + end - word_length + 1, word + 1, word_length) != 0) return 0;

	offset_j = end - word_length;

	return 1;
} 

void porter_stemming::readjust(char *word) {
	int word_length = word[0];

	memmove(buffer + offset_j + 1, word + 1, word_length);

	end = offset_j + word_length;
}

void porter_stemming::replace(char *word) {
	if (consonant_sequence() > 0) readjust(word);
}

void porter_stemming::remove_plurals() {
	if (ends_with("\02" "’s")) {
		readjust("\01" "s");
	}

	else if (buffer[end] == 's') {
		if (ends_with("\04" "sses")) end -= 2;		
		
		else if (ends_with("\03" "ies")) readjust("\01" "i");
		
		else if (buffer[end - 1] != 's') end--;

	}

	if (ends_with("\03" "eed")) {
		if (consonant_sequence() > 0) end--;
	}
		
	else if ((ends_with("\02" "ed") || ends_with("\03" "ing")) && thers_vowel()) {
		end = offset_j;

		if (ends_with("\02" "at")) readjust("\03" "ate");
		else if (ends_with("\02" "bl")) readjust("\03" "ble");
		else if (ends_with("\02" "iz")) readjust("\03" "ize");
		else if (thers_double_consonant(end)) {
			end--;

			if (buffer[end] == 'l' || buffer[end] == 's' || buffer[end] == 'z') end++;
		}

		else if (consonant_sequence() == 1 && consonant_vowel_consonant(end)) readjust("\01" "e");
	}
}

void porter_stemming::vowelize() {
	if (ends_with("\01" "y") && thers_vowel()) buffer[end] = 'i';
}


void porter_stemming::sufix() {
	switch (buffer[end - 1]) {
		case 'a':
			if (ends_with("\07" "ational")) {
				replace("\03" "ate");
				break;
			}

			if (ends_with("\06" "tional")) {
				replace("\04" "tion");
				break;
			}
			break;

		case 'c':
			if (ends_with("\04" "enci")) {
				replace("\04" "ence");
				break;
			}

			if (ends_with("\04" "anci")) {
				replace("\04" "ance");
				break;
			}
			break;

		case 'e':
			if (ends_with("\04" "izer")) {
				replace("\03" "ize");
				break;
			}
            break;
		
		case 'l':
			if (ends_with("\04" "abli")) {
				replace("\04" "able");
				break;
			}
			
			if (ends_with("\04" "alli")) {
				replace("\02" "al");
				break;
			}
            
			if (ends_with("\05" "entli")) {
				replace("\03" "ent");
				break;
			}
            
			if (ends_with("\03" "eli")) {
				replace("\01" "e");
				break;
			}
            
			if (ends_with("\05" "ousli")) {
				replace("\03" "ous");
				break;
			}
            break;
		
		case 'o':
			if (ends_with("\07" "ization")) {
				replace("\03" "ize");
				break;
			}

            if (ends_with("\05" "ation")) {
				replace("\03" "ate");
				break;
			}
            
			if (ends_with("\04" "ator")) {
				replace("\03" "ate");
				break;
			}
              break;
		
		case 's':
			if (ends_with("\05" "alism")) {
				replace("\02" "al");
				break;
			}
            
			if (ends_with("\07" "iveness")) {
				replace("\03" "ive");
				break;
			}
            
			if (ends_with("\07" "fulness")) {
				replace("\03" "ful");
				break;
			}
            
			if (ends_with("\07" "ousness")) {
				replace("\03" "ous");
				break;
			}
            break;

		case 't':
			if (ends_with("\05" "aliti")) {
				replace("\02" "al");
				break;
			}
            
			if (ends_with("\05" "iviti")) {
				replace("\03" "ive");
				break;
			}
            
			if (ends_with("\06" "biliti")) {
				replace("\03" "ble");
				break;
			}
            break;

		default:
			break;
			
	}
}


void porter_stemming::sufix2() {
	switch (buffer[end]) {
		case 'e':
			if (ends_with("\05" "icate")) {
				replace("\02" "ic");
				break;
			}
            
			if (ends_with("\05" "ative")) {
				replace("\00" "");
				break;
			}
            
			if (ends_with("\05" "alize")) {
				replace("\02" "al");
				break;
			}
            break;

		case 'i':
			if (ends_with("\05" "iciti")) {
				replace("\02" "ic");
				break;
			}
            break;
		
		case 'l':
			if (ends_with("\04" "ical")) {
				replace("\02" "ic");
				break;
			}
            
			if (ends_with("\03" "ful")) {
				replace("\00" "");
				break;
			}
            break;
    
		case 's':
			if (ends_with("\04" "ness")) {
				replace("\00" "");
				break;
			}
            break;

		default:
			break;
	}
}

void porter_stemming::sufix3() {
	switch (buffer[end - 1]) {
		case 'a':
			if (ends_with("\02" "al")) break; return;
		
		case 'c':
			if (ends_with("\04" "ance")) break;
            
			if (ends_with("\04" "ence")) break;
			
			return;
		
		case 'e':
			if (ends_with("\02" "er")) break;
			return;
		
		case 'i':
			if (ends_with("\02" "ic")) break;
			return;
		
		case 'l':
			if (ends_with("\04" "able")) break;
			
			if (ends_with("\04" "ible")) break;
			
			return;
		
		case 'n':
			if (ends_with("\03" "ant")) break;
            
			if (ends_with("\05" "ement")) break;
        
			if (ends_with("\04" "ment")) break;
	
			if (ends_with("\03" "ent")) break;
			
			return;
		
		case 'o':
			if (ends_with("\03" "ion") && offset_j >= offset_i && (buffer[offset_j] == 's' || buffer[offset_j] == 't')) break;
            if (ends_with("\02" "ou")) break;
			
			return;
		
		case 's':
			if (ends_with("\03" "ism")) break;
			return;
		
		case 't':
			if (ends_with("\03" "ate")) break;
			
			if (ends_with("\03" "iti")) break;
			
			return;
		
		case 'u':
			if (ends_with("\03" "ous")) break;
			return;
		
		case 'v':
			if (ends_with("\03" "ive")) break;
			return;
		
		case 'z':
			if (ends_with("\03" "ize")) break;
			return;
		
		default:
			return;
    }

    if (consonant_sequence() > 1) end = offset_j;
}


void porter_stemming::sufix4() {
	offset_j = end;
	
	if (buffer[end] == 'e') {
		int counter = consonant_sequence();
		
		if (counter > 1 || counter == 1 && !consonant_vowel_consonant(end - 1))
			end--;
   }

   if (buffer[end] == 'l' && thers_double_consonant(end) && consonant_sequence() > 1)
	   end--;
}

std::string porter_stemming::stemming(char * p, int i, int j) {

	std::string tmp;
	buffer = p;
	end = j;
	offset_i = i;

	if (end <= offset_i + 1) return "";
	
	remove_plurals();
	
	if (end > offset_i) {
       vowelize();
	   sufix();
	   sufix2();
	   sufix3();
	   sufix4();
   }

	tmp.assign(buffer, j);

	return tmp;
}

#pragma warning( pop ) 
#pragma clang diagnostic pop

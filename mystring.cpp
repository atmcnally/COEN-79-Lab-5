#include <cstring>
#include <iostream>
#include <cassert>
#include "mystring.h"

namespace coen79_lab5 {

	//call reserve whenever i change the length of my string

	string::string(const char str[]) {
		current_length = strlen(str);
		reserve(current_length + 1);

		for (int i = 0; i < sizeof(str); i++) {
			characters[i] = str[i];
		}

		allocated = current_length + 1;
	}
	//default argument is the empty string.
	//Precondition: str is an ordinary null-terminated string.
	//Postcondition: The string contains the sequence of chars from str.

	string::string(char c) {
		//is null character inserted by default?
		reserve(2);

		characters[0] = c;
		characters[1] = '\0';

		current_length = 1;
		allocated = 2;
	}
	//Postcondition: The string contains c and then the null character.

	string::string(const string& source) {
		current_length = source.length();
		reserve(current_length + 1);
		strncpy(characters, source.characters, current_length);
	}
	//Copy Constructor.
	//Postcondition: The string becomes a copy of the source string.

	string::~string() {
		delete[]characters;
	}

	void string::operator +=(const string& addend) {
		//can use addend.characters
		reserve(current_length + addend.length());
		for (int i = 0; i < addend.length(); i++) {
			characters[current_length + i] = addend[i];
		}

		current_length += addend.length();
	}
	//Postcondition: addend has been catenated to the end of the string.

	void string::operator +=(const char addend[]) {
		//can use addend.characters
		reserve(current_length + sizeof(addend));

		for (int i = 0; i < sizeof(addend); i++) {
			characters[current_length + i] = addend[i];
		}

		current_length += sizeof(addend);
	}
	//Precondition: addend is an ordinary null-terminated string.
	//Postcondition: addend has been catenated to the end of the string.

	void string::operator +=(char addend) {
		//can use addend.characters
		reserve(current_length + 1);
		characters[current_length] = addend;
		current_length++;
	}
	//Postcondition: The single character addend has been catenated to the end of the string.

	void string::reserve(size_t n) {
		//only ever need to allocate more memory -- so this is done

		if (current_length < n) {
			char* tmp = new char[n];

			if (characters != NULL) {
				strncpy(characters, tmp, n);
				delete[] characters;
				allocated = n;
			}

			characters = tmp;
		}
	}
	//Postcondition: All functions will now work efficiently (without allocating new memory) until n characters are in the string. 

	void string::insert(const string& source, unsigned int position) {
		assert(position <= length());
		reserve(current_length + source.length() + 1);
		int count = 0;
		for (int i = current_length - 1; i >= position; i--) {
			characters[i + 1] = characters[i];
			characters[i] = source[count];
			count++;
		}

		current_length += source.length();
	}
	//Postcondition: The source string is inserted into this string before the character at the given index.

	void string::dlt(unsigned int position, unsigned int num) {
		assert((position + num) <= length());
		for (int i = 0; i < num; i++) {
			characters[position + i] = characters[position + num + i];
		}

		for (int i = position + num; i < position + 2 * num; i++) {
			characters[i] = '/0';
		}

		//this does not mean that the allocated amount is still near current_length -- a lot of extra might end up getting allocated
		current_length -= num;
	}
	//Postcondition: num characters are deleted from the sequence, starting at index position.

	void string::replace(char c, unsigned int position) {
		assert(position < length());
		characters[position] = c;
	}
	//Postcondtion: the character at the given position in the string is replaced with c.

	void string::replace(const string& source, unsigned int position) {
		assert((position + source.length()) <= length());
		for (int i = 0; i < source.length(); i++) {
			characters[position + i] = source[i];
		}
	}
	//Postcondtion: the characters in this string starting at position are replaced with those in the source srting.

	char string::operator [ ](size_t position) const {
		assert(position < length());

		return characters[position];
	}
	//Postcondition: The value returned is the character at the specified position of the string. 
	//A string's positions start from 0 at the start of the sequence and go up to length( )-1 at the right end.

	int string::search(char c) const {
		for (int i = 0; i < current_length; i++) {
			if (characters[i] == c) {
				return i;
			}
		}

		return -1;
	}
	//Postcondition: The location of the first occurence of the character c within this string is returned. 
	//If the string does not contain c, -1 is is returned.

	int string::search(const string& substring) const {
		bool pop = true;
		for (int i = 0; i < current_length - substring.length(); i++) {
			if (characters[i] == substring[0]) {
				//if first character matches, check everything of substring length after character[i]
				for (int j = 0; j < substring.length(); j++) {
					if (characters[i + j] == substring.characters[j]) {
						continue;
					}
					else {
						pop = false;
						break;
					}
				}

				if (pop) {
					return i;
				}
			}
		}

		return -1;
	}
	//Postcondition: Returns the index of the start of the first instance of the given substring inside of this string. 
	//If the substring is not found, this function returns -1.

	unsigned int string::count(char c) const {
		int count = 0;
		for (int i = 0; i < current_length; i++) {
			if (characters[i] == c) {
				count++;
			}
		}

		return count;
	}
	//Postcondition: The count of the occurence of the character c within this string is returned.

	//everything below until non-member functions is a friend

	//TOTAL ORDER SEMANTICS for the string class:
	//The six comparison operators (==, !=, >=, <=, >, and <) are implemented for the string class, 
	//forming a total order semantics, using the usual lexicographic order on strings.

	bool operator ==(const string& s1, const string& s2) {
		/* if (s1.length() != s2.length()) {
			return false;
		} else {
			for (int i = 0; i < s1.length(); i++) {
				if (s1.characters[i] != s2.characters[i]) {
					return false;
				}
			}
		} */

		if (s1.length() == s2.length()) {
			if (strncmp(s1.characters, s2.characters, s1.length()) == 0) {
				return true;
			}
		}

		return false;
	}

	bool operator !=(const string& s1, const string& s2) {
		if (s1 == s2) {
			return false;
		}

		return true;
	}

	bool operator > (const string& s1, const string& s2) {

		if (s1 == s2) {
			return false;
		}
		else {
			if (s1.length() > s2.length()) {
				return true;
			}
			else if (s1.length() == s2.length()) {
				//need to compare and evaluate result of strncmp
				if (strncmp(s1.characters, s2.characters, s1.length()) > 0) {
					return true;
				}
			}
		}

		return false;
	}

	bool operator < (const string& s1, const string& s2) {

		if (s1 == s2) {
			return false;
		}
		else {
			if (s1.length() < s2.length()) {
				return true;
			}
			else if (s1.length() == s2.length()) {
				if (strncmp(s1.characters, s2.characters, s1.length()) < 0) {
					return true;
				}
			}
		}

		return false;
	}

	bool operator >=(const string& s1, const string& s2) {
		if (s1 == s2) {
			return true;
		}
		else {
			if (s1.length() > s2.length()) {
				return true;
			}
			else if (s1.length() == s2.length()) {
				//need to compare and evaluate result of strncmp
				if (strncmp(s1.characters, s2.characters, s1.length()) > 0) {
					return true;
				}
			}
		}

		return false;
	}
	bool operator <=(const string& s1, const string& s2) {
		if (s1 == s1) {
			return true;
		}
		else {
			if (s1.length() < s2.length()) {
				return true;
			}
			else if (s1.length() == s2.length()) {
				if (strncmp(s1.characters, s2.characters, s1.length()) < 0) {
					return true;
				}
			}
		}

		return false;
	}

	std::ostream& operator <<(std::ostream& outs, const string& source) {

		for (int i = 0; i < source.length(); i++) {
			outs << source.characters[i];
		}

		return outs;
	}
	//Postcondition: The sequence of characters in source has been written to outs. The return value is the ostream outs.

	// NON-MEMBER FUNCTIONS for the string class:
	string operator +(const string& s1, const string& s2) {
		string retStr(s1);

		retStr += s2;

		return retStr;
	}
	//Postcondition: The string returned is the catenation of s1 and s2.

	string operator +(const string& s1, const char addend[]) {
		string retStr(s1);
		retStr.reserve(s1.length() + sizeof(addend));

		retStr += addend;

		return retStr;
	}

	std::istream& operator >>(std::istream& ins, string& target) {


		return ins;
	}

}
//Postcondition: A string has been read from the istream ins, and the istream ins is then returned by the function. 
//The reading operation skips white space (i.e., blanks, newlines, tabs) at the start of ins. 
//Then the string is read up to the next white space or the end of the file. 
//The white space character that terminates the string has not been read.

//VALUE SEMANTICS for the string class:
//Assignments and the copy constructor may be used with string objects.

// DYNAMIC MEMORY usage by the string class:
//If there is insufficient dynamic memory then the following functions call new_handler: 
//The constructors, resize, operator +=, operator +, and the assignment operator -- THESE JUST CALL RESERVE
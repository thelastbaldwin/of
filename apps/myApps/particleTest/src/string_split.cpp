#include <iostream>
#include <string>

using namespace std;

int main(){
	string str("This is a very long string with far too many characters. If this were a twitter message, no one would read it because it had TL;DR written all over it.");

	if(str.length() > 70){
		//if the lengrth is over this threshold, find the last punctuation mark or space
		size_t mid_space = str.rfind(' ', 70);
		//string substr ( size_t pos = 0, size_t n = npos ) const;
		string first = str.substr(0, mid_space);
		string second = str.substr(mid_space+1);
		//string second = str.substr(mid_space);
		cout << first << endl;
		cout << second << endl;
		//cout << second << endl;

		cout << "The string 'second' is " << second.length() << " characters long" << endl;
		cout << "The string 'first' is " << first.length() << " characters long" << endl;
	}

	return 0;
}
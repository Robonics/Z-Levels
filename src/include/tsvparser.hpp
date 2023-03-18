#pragma once
#include <map>
#include <string>
#include <fstream>
#include <vector>

std::map<std::string, std::vector<std::string>> ParseTSV( std::string filename ) {

	std::ifstream file( filename );

	std::map<std::string, std::vector<std::string>> r;
	if(!file.is_open()) {
		return r;
	}

	for( std::string s; std::getline( file, s ); ) {
		int c = 0; // This is our current character position in the line. We will use this to define ranges where each value in the TSV is stored
		std::string _key; // This is a cache value for the first value in the line that will be used for the key
		std::vector<std::string> _value; // This is a cache for the values following the key
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == '\t' || i + 1 == s.length()) {
				if(c == 0) {
					_key = s.substr(c, i - c + ( (i + 1 == s.length()) ? 1 : 0 ));
				}else {
					_value.push_back( s.substr(c, i - c + ( (i + 1 == s.length()) ? 1 : 0 )) );
				}
				c = i + 1;
			}
		}
		r[_key] = _value;
	}

	return r;
}
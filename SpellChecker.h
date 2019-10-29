//Md Uddin
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
#include <unordered_set>

class SpellChecker {
private: 
	std::string file;
	std::string wordList;
public:
	std::unordered_set<std::string> wordDict;

	SpellChecker();
	explicit SpellChecker(const std::string& dirDict, std::string& dirFile);
	~SpellChecker();
	void toLowerCase(std::string& text);
	void checkFile(const std::string& dir);
	void checkDictFile(const std::string& dir);
	std::vector<std::string> getSuggestions(const std::string& word);
};
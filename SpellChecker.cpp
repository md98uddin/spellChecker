//Md Udddin
#include "SpellChecker.h"



//default constructor to interact with user
SpellChecker::SpellChecker()
{
	std::cout << "---------SPELLCHECKER STARTED----------" << std::endl;

	std::cout << "Please enter the dictionary file name" << std::endl;
	std::cin >> wordList;
	std::cout << "Please enter the text file name" << std::endl;
	std::cin >> file;

	SpellChecker(wordList, file);
}

//constructor to pass parameters on the go
SpellChecker::SpellChecker(const std::string& dirDict, std::string& dirFile):wordList(dirDict), file(dirFile)
{
	checkDictFile(wordList);
	checkFile(file);
}

//destructor
SpellChecker::~SpellChecker()
{
	//some memory cleanup
	wordDict.clear();
	std::cout << "Check suggestions.txt file for corrections"<< std::endl;
}

//converts our text into lowercase since we want to avoid C++
//case sensitivity
void SpellChecker::toLowerCase(std::string& text)
{
	for (auto& words : text) {
		words = tolower(words);
	}
}

//we can ensure that our text file words are being read
//one by one
void SpellChecker::checkFile(const std::string& dir)
{
	file = dir;
	//we open the file using fstream library
	std::ifstream inFile;
	std::ofstream outfile("suggestions.txt");
	inFile.open(file);

	//file error handling, reading each word and set them
	//to lower case
	if (inFile.is_open()) {
		std::string word;
		while (inFile >> word) {
			toLowerCase(word);

			//removing punctuation
			for (int i = 0; i < word.size(); ++i)
			{
				if (ispunct(word[i])) {
					word = word.erase(i, 1);
				}
			}

			    //conditional statement to locate matches 	
				if (wordDict.find(word) != wordDict.end()) {
					continue;
				}
				else {
					std::vector<std::string> suggestions = getSuggestions(word);
					if (suggestions.empty()) {
						outfile << word << "---->has no correction" << std::endl;
					}
					else {
						outfile << word << "---->";
						for (auto suggestion : suggestions) {
							outfile << suggestion << "," << std::endl;
						}
					}
				}
		}
	}
	else {
		std::cout << "Failed to open file.";
	}

	outfile.close();
}

//we can ensure that our dictionary file words are being read
//one by one and placed into our set container
void SpellChecker::checkDictFile(const std::string& dir)
{
	wordList = dir;
	std::ifstream inFile;
	inFile.open(wordList);

	//file error handling, reading each dictrionary word
	//then place them in set
	if (inFile.is_open()) {
		std::string word;
		while (inFile >> word) {
			toLowerCase(word);
			wordDict.emplace(word);
		}
	}
	else {
		std::cout << "Failed to open file.";
	}
}


//we create a vector of all suggestions for given words
std::vector<std::string> SpellChecker::getSuggestions(const std::string& word)
{
	std::vector<std::string> suggestions;

	//two neighboring letters swapped their positions
	for (int i = 0; i < word.size()-1; ++i)
	{
		auto newWord = word;
		std::swap(newWord[i], newWord[i + 1]);
		if (wordDict.find(newWord) != wordDict.end()) {
			suggestions.push_back(newWord);
		}

	}

	//a single extra letter appears in the word
	for (int i = 0; i < word.size() - 1; i++)
	{
		auto newWord = word;
		newWord=newWord.erase(i, 1);
		if (wordDict.find(newWord) != wordDict.end()) {
			suggestions.push_back(newWord);
		}
	}

	//a single letter is missing somewhere in the word and multiple suggestions
	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

	for (int i = 0; i < word.size(); ++i)
	{

		std::string s1 = word.substr(0, i);
		std::string s2 = word.substr(i);

		for (int j = 0; j < 26; j++)
		{
			std::string alpha(1, alphabet[j]);
			std::string word = s1 + alpha+s2;
			if (wordDict.find(word) != wordDict.end()) {
				suggestions.push_back(word);
			}
		}
    }



	return suggestions;
}
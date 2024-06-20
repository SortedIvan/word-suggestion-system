#include "trie.hpp"

class SuggestionSystem {
private:
	Node* root;
	Node* getPrefixRoot(std::string prefix, int pointer, Node* node);
	void insertHelper(std::string word, int& pointer, Node* root);
	std::vector<std::string> insertedWords;
public:
	SuggestionSystem();

	std::vector<std::string> getSuggestions(std::string prefix, bool sortedOutput, bool addPrefix);
	void insertWordIntoTree(std::string word);
	void insertMultipleWordsIntoTree(std::vector<std::string>& words);
	void getSuggestionsHelper(std::vector<std::string>& suggestions, std::string currentSubstring, Node* root);
};
#include "suggestion_system.hpp"
#include <algorithm>

SuggestionSystem::SuggestionSystem() {
	root = new Node();
}

Node* SuggestionSystem::getPrefixRoot(std::string prefix, int pointer, Node* node) {
	if (pointer >= prefix.size()) {
		return node;
	}

	char currentChar = prefix[pointer];

	if (node->children.find(currentChar) != node->children.end()) {
		pointer++;
		return getPrefixRoot(prefix, pointer, node->children[currentChar]);
	}

	return nullptr;
}

void SuggestionSystem::insertHelper(std::string word, int& pointer, Node* node) {
	if (pointer >= word.size()) {
		node->isWord = true;
		return;
	}

	char currentCharacter = word[pointer];

	// Check if character is already in the tree
	if (node->children.find(currentCharacter) != node->children.end()) {
		pointer++;
		insertHelper(word, pointer, node->children[currentCharacter]);
	}
	else {
		Node* child = new Node();
		node->children.insert({ currentCharacter, child });
		pointer++;
		insertHelper(word, pointer, node->children[currentCharacter]);
	}
}

std::vector<std::string> SuggestionSystem::getSuggestions(std::string prefix, bool sortedOutput) {
	std::vector<std::string> suggestions;
	std::string currentSubstring = "";
	int pointer = 0;

	Node* correctRoot = getPrefixRoot(prefix, pointer, root);

	if (!correctRoot) {
		return std::vector<std::string>();
	}

	// start collecting characters from this point onwards
	getSuggestionsHelper(suggestions, prefix, correctRoot);

	if (sortedOutput) {
		std::sort(suggestions.begin(), suggestions.end());
	}
	
	return suggestions;
}

void SuggestionSystem::insertWordIntoTree(std::string word) {
	int pointer = 0;
	insertHelper(word, pointer, root);
}


void SuggestionSystem::getSuggestionsHelper(std::vector<std::string>& suggestions, std::string currentSubstring, Node* node) {
	if (!node || node->children.size() == 0) {
		// reached the end
		suggestions.push_back(currentSubstring);
		return;
	}

	if (node->isWord) {
		suggestions.push_back(currentSubstring);
	}

	for (auto pair = node->children.begin(); pair != node->children.end(); ++pair) {
		getSuggestionsHelper(suggestions, currentSubstring + pair->first, pair->second);
	}
}

void SuggestionSystem::insertMultipleWordsIntoTree(std::vector<std::string>& words) {
	for (int i = 0; i < words.size(); ++i) {
		insertWordIntoTree(words[i]);
	}
}
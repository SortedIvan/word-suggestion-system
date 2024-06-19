#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include <iostream>

class Node {
public:
	std::unordered_map<char, Node*> children; // a - z
	bool isWord = false;

	Node() {

	}
};


Node* getCorrectRoot(std::string prefix, int pointer, Node* root);
std::vector<std::string> getSuggestions(std::string prefix, Node* root);
void insertWordIntoTree(std::string word, Node* root);
void insertHelper(std::string word, int& pointer, Node* root);
void getSuggestionsHelper(std::set<std::string>& suggestions, std::string currentSubstring, Node* root);

int main() {
	Node* root = new Node();
	
	std::vector<std::string> functions = { "test", "delete", "start_game", "destroy", "dig", "d", "destroyer", "destiny", "debree"};

	for (int i = 0; i < functions.size(); ++i) {
		insertWordIntoTree(functions[i], root);
	}

	std::string prefix = "de";
	std::vector<std::string> suggestions = getSuggestions(prefix, root);

	for (int i = 0; i < suggestions.size(); i++) {
		std::cout << suggestions[i] << std::endl;
	}
}

Node* getCorrectRoot(std::string prefix, int pointer, Node* root) {
	if (pointer >= prefix.size()) {
		return root;
	}

	char currentChar = prefix[pointer];

	if (root->children.find(currentChar) != root->children.end()) {
		pointer++;
		return getCorrectRoot(prefix, pointer, root->children[currentChar]);
	}

	return nullptr;
}


// search
std::vector<std::string> getSuggestions(std::string prefix, Node* root) {
	std::set<std::string> suggestions;
	std::string currentSubstring = "";
	int pointer = 0;

	Node* correctRoot = getCorrectRoot(prefix, pointer, root);

	if (!correctRoot) {
		return std::vector<std::string>();
	}
		 
	// start collecting characters from this point onwards
	getSuggestionsHelper(suggestions, prefix, correctRoot);

	return std::vector<std::string>(suggestions.begin(), suggestions.end());
}

void getSuggestionsHelper(std::set<std::string>& suggestions, std::string currentSubstring, Node* root) {
	if (!root || root->children.size() == 0) {
		// reached the end
		suggestions.insert(currentSubstring);
		return;
	}

	if (root->isWord) {
		suggestions.insert(currentSubstring);
	}

	for (auto pair = root->children.begin(); pair != root->children.end(); ++pair) {
		getSuggestionsHelper(suggestions, currentSubstring + pair->first, pair->second);
	}

}





void insertWordIntoTree(std::string word, Node* root) {
	int pointer = 0;
	insertHelper(word, pointer, root);
}

  
//test
void insertHelper(std::string word, int& pointer, Node* root) {

	if (pointer >= word.size()) {
		root->isWord = true;
		return;
	}

	char currentCharacter = word[pointer];

	// Check if character is already in the tree
	if (root->children.find(currentCharacter) != root->children.end()) {
		pointer++;
		insertHelper(word, pointer, root->children[currentCharacter]);
	}
	else {
		Node* child = new Node();
		root->children.insert({ currentCharacter, child });
		pointer++;
		insertHelper(word, pointer, root->children[currentCharacter]);
	}
}


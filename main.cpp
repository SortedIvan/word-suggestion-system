#include <iostream>
#include "suggestion_system.hpp"

int main() {
	
	SuggestionSystem* suggestionSystem = new SuggestionSystem();
	std::vector<std::string> functions = { "test", "delete", "start_game", "destroy", "enter_zone", "deinitialize", "remove", "stop", "run"};

	suggestionSystem->insertMultipleWordsIntoTree(functions);

	std::string prefix = "d";
	std::vector<std::string> suggestions = suggestionSystem->getSuggestions(prefix, true);

	for (int i = 0; i < suggestions.size(); i++) {
		std::cout << suggestions[i] << std::endl;
	}

	delete suggestionSystem;
}


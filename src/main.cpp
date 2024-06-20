#include <iostream>
#include <stdlib.h>
#include "suggestion_system.hpp"

int main() {
	
	SuggestionSystem* suggestionSystem = new SuggestionSystem();
	std::vector<std::string> functions = { "test", "delete", "start_game", "destroy", "enter_zone", "deinitialize", "remove", "stop", "run"};

	suggestionSystem->insertMultipleWordsIntoTree(functions);

	std::string currentWord = "";

	delete suggestionSystem;
}


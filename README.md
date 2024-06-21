# word-suggestion-system
A simple word suggestion system. Built by using a modified Trie data structure, together with SFML for visualizations.

This system uses a simple prefix Trie implementation: https://en.wikipedia.org/wiki/Trie

![image](https://github.com/SortedIvan/word-suggestion-system/assets/62967263/c673e518-9a57-481b-8095-74308df240ac)

It creates a tree, where each node holds a map to children nodes given a character input. Words are inserted character by character and create a decision tree that allows for efficient O(log(N)) searching. Constructing a tree given an array of commands takes O(Nlog(N)). Given a prefix of a word, we find the root where the prefix ends. Then, the tree sub-rooted at that particular root represents all of the auto-completions for the prefix input.


Each node has:
 - unordered_map that points to children nodes given a character
 - bool isWord to indicate whether the path down to the current node represents a word

The reasoning behind unorderd_map over an array is the ability to map words with any characters. An array with size 26 can be used only if the words contain the alphabet, which is not always true when autocompleting functions.

To use the system:
- Download and set up SFML. This project does not ensure the correct set up of SFML.
- Create a new SuggestionSystem pointer
- Insert your vector of strings that represent any commands/words that you want to auto-complete
- Search with a given prefix. You must indicate whether you want the input sorted alphabetically or not. Furthermore, specify whether you want the prefix to be automatically added to the auto-completion results

To get automatic suggestions, use the getSuggestions(...) function.

Visualization of the system:
![gif_ready](https://github.com/SortedIvan/word-suggestion-system/assets/62967263/590cad6e-d79b-49cb-b128-5b3ab050f8f7)

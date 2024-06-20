#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include <iostream>

struct Node {
	std::unordered_map<char, Node*> children;
	bool isWord;
};
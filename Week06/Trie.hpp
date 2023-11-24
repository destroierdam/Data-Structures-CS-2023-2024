#pragma once
#include <iostream>

template<typename T>
class Trie {
public:
	Trie(): root(new Node(nullptr)) {}

	void insert(const char* key, const T& value) {
		this->_insert(key, value, this->root);
	}
private:
	static const std::size_t CHILDREN_SIZE = 26;
	struct Node {
		T* data;
		Node* children[CHILDREN_SIZE];
		// OR
		// std::map<char, Node*>
		// OR
		// std::array<Node*, 26> children;
		Node(T* data): data(data) {
			for(std::size_t i = 0; i < CHILDREN_SIZE; ++i) {
				this->children[i] = nullptr;
			}
		}
	};
private:
	void _insert(const char* key, const T& value, Node* node) {
		if(node == nullptr) {
			std::cout << "INVALID TREE: key=" << key << " and value=" << value << "\n";
			return;
		}
		if(key[0] == '\0') {
			std::cout << "Adding value: " << value << "\n";
			node->data = new T(value);
			return;
		}
		std::cout << "Working on edge with label: " << key[0] << "\n";
		Node*& childToGoTo = node->children[key[0] - 'a'];
		if (childToGoTo == nullptr) {
			childToGoTo = new Node(nullptr);
		}
		// if (node->children[key[0] - 'a'] == nullptr) {
		// 	node->children[key[0] - 'a'] = new Node(nullptr);
		// }
		this->_insert(key + 1, value, childToGoTo);
	}
private:
	Node* root;
};

#pragma once
#include <iostream>
#include <vector>

template<typename T>
class BST {

public:
	BST():root(nullptr) {}

	void insert(const T& newData) {
		this->insertHelper(this->root, newData);
	}

	void print() const {
		this->printHelper(this->root);
	}

	std::size_t height() const {
		return this->heightHelper(this->root);
	}

	void balance() {
		std::vector<Node*> sortedNodes;
		this->getSortedNodes(this->root, sortedNodes);
		this->root = nullptr;

		for(Node* node : sortedNodes) {
			std::cout << "Node: " << node->data << "\n";
		}
		std::cout << "------------\n";
		this->insertBalanced(this->root, sortedNodes, 0, sortedNodes.size() - 1);
	}
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		
		Node(const T& data): data(data), left(nullptr), right(nullptr) {}

		Node(const T& data, Node* left, Node* right): data(data), left(left), right(right) {}
	};
private:
	void insertHelper(Node*& node, const T& newData) {
		if (node == nullptr) {
			node = new Node(newData);
			return;
		}
		if (newData < node->data) {
			this->insertHelper(node->left, newData);
		} else {
			this->insertHelper(node->right, newData);
		}
	}
	
	void insertHelperIterative(const T& newData) {
		Node** insertHere = &(this->root);

		while((*insertHere) != nullptr) {
			if(newData < (*insertHere)->data) {
				insertHere = &((*insertHere)->left);
			} else {
				insertHere = &((*insertHere)->right);
			}
		}
		(*insertHere) = new Node(newData);

		// SAME AS THIS:
		// while(true) {
		// 	if((*insertHere) == nullptr) {
		// 		(*insertHere) = new Node(newData);
		// 		return;
		// 	} else {
		// 		if(newData < (*insertHere)->data) {
		// 			insertHere = &((*insertHere)->left);
		// 		} else {
		// 			insertHere = &((*insertHere)->right);
		// 		}
		// 	}
		// }
	}
	
	void printHelper(Node * const node) const {
		if (node == nullptr) { return; }
		printHelper(node->left);
		std::cout << node->data << ", ";
		printHelper(node->right);
	}

	std::size_t heightHelper(Node* node) const {
		if (node == nullptr) { return 0; }
		return 1 + std::max(this->heightHelper(node->left), this->heightHelper(node->right));
	}

	void getSortedNodes(Node* node, std::vector<Node*>& sortedNodes) {
		if(node == nullptr) { return; }
		this->getSortedNodes(node->left, sortedNodes);
		node->left = nullptr;
		sortedNodes.push_back(node);
		this->getSortedNodes(node->right, sortedNodes);
		node->right = nullptr;
	}

	void insertBalanced(Node*& node, std::vector<Node*>& sortedNodes, std::size_t left, std::size_t right) {
		std::cout << "[balanced]: node:" << (node ? node->data : 0) << " left: " << left << " right: " << right << "\n";
		if (right > sortedNodes.size() || right < left) { return; }
		
		std::size_t mid = left + (right - left) / 2; // same as (left + right) / 2, but protects from overflow
		std::cout << "Inserting " << sortedNodes[mid]->data << "\n";
		node = sortedNodes[mid];
		if (mid > 0) {
			insertBalanced(node->left, sortedNodes, left, mid - 1);
		}
		insertBalanced(node->right, sortedNodes, mid + 1, right);
	}
private:
	Node* root;
};

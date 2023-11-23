#pragma once
#include <iostream>
#include <cstddef>
#include <functional>

template <typename T>
class BinTree {
public:
	BinTree(): root(nullptr) {
		std::clog << "Constructing tree " << (long) this << "\n";
		this->root = new Node{1, new Node{10, nullptr, nullptr}, new Node{44, new Node{69, nullptr, nullptr}, new Node{420, nullptr, nullptr}}};
	}
	BinTree(const BinTree& other) {
		std::clog << "Copying " << (long)&other << " into " << (long) this << "\n";
		this->copy(other);
	}
	BinTree(BinTree&& other):BinTree() {
		std::swap(this->root, other.root);
	}
	BinTree& operator=(const BinTree& other) {
		if (this != &other) {
			this->destroy();
			this->copy(other);
		}
		return *this;
	}
	~BinTree() {
		this->destroy();
	}

	std::size_t count() const {
		return countHelper(this->root);
	}

	std::size_t countEvens() const {
		return this->countEvensHelper(this->root);
	}

	std::size_t searchCount(std::function<bool(const T&)> pred) const {
		// return this->searchCountHelper(pred, this->root);
		return this->_searchCount(
			[pred](Node* node) -> bool { return pred(node->data); },
			this->root
		);
	}

	std::size_t height() const {
		return this->heightHelper(this->root);
	}
	std::size_t countLeaves() const {
		return this->_searchCount(
			[](Node* node) -> bool { return node->left == nullptr && node->right == nullptr; },
			this->root);
	}

private:
	struct Node {
		T data;
		Node * left;
		Node * right;
	};

private:
	void copy(const BinTree& other) {
		this->copyHelper(this->root, other.root);
	}
	void copyHelper(Node*& current, const Node* other) {
		if (other == nullptr) {
			return;
		}
		std::clog << "Copying node with data " << other->data << "\n";
		current = new Node{other->data, nullptr, nullptr};
		copyHelper(current->left, other->left);
		copyHelper(current->right, other->right);

		// current->left = copyHelper2(other->left)
		// current->right = copyHelper2(other->right)
	}
	void destroy() {
		std::clog << "Destroying tree " << (long) this << "\n";
		this->destroyHelper(this->root);
	}
	void destroyHelper(Node* current) {
		if (current == nullptr) {
			return;
		}
		// if (current->left != nullptr) { // Unneeded because of the if above
			destroyHelper(current->left);
		// }
		// if (current->right != nullptr) { // Unneeded because of the if above
			destroyHelper(current->right);
		// }
		// Now both subtrees have been deleted
		std::clog << "Deleting node with data " << current->data << "\n";
		delete current;
	}

	std::size_t countHelper(Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		return 1 + this->countHelper(node->left) + this->countHelper(node->right);
	}
	std::size_t countEvensHelper(Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		// std::cout << node->data << " - " << (node->data % 2 == 0 ? 1 : 0) << "\n";
		return (node->data % 2 == 0 ? 1 : 0) + this->countEvensHelper(node->left) + this->countEvensHelper(node->right);
		 // ? 1 : 0  can be ommitted
	}
	std::size_t _searchCount(std::function<bool(Node*)> pred, Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		return pred(node) + this->_searchCount(pred, node->left) + this->_searchCount(pred, node->right);
	}
	std::size_t searchCountHelper(std::function<bool(const T&)> pred, Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		return pred(node->data) + this->searchCountHelper(pred, node->left) + this->searchCountHelper(pred, node->right);
	}
	std::size_t heightHelper(Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		return 1 + std::max(this->heightHelper(node->left), this->heightHelper(node->right));
	}

private:
	Node * root;
};

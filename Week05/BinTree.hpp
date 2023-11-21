#pragma once
#include <iostream>

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

private:
	Node * root;
};

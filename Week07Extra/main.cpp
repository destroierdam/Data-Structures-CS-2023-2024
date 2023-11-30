#include "BST.hpp"

int main() {
	BST<int> bst;
	bst.insert(20);
	bst.insert(10);

	bst.insert(50);
	bst.insert(69);
	bst.insert(420);

	bst.print();
	std::cout << std::endl;
	if(bst.height() != 4) {
		std::cout <<"Height function does not work\n";
	}
	bst.balance();
	if(bst.height() != 3) {
		std::cout <<"Balance does not work\n";
	}

	bst.print();
}
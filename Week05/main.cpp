#include "BinTree.hpp"
#include <cassert>

int main() {
	BinTree<int> tree;
	assert(tree.count() == 5);
	if (tree.countEvens() != 3) {
		std::cout << tree.countEvens() << "\n";
	} else {
		std::cout << "Test for countEvens passes\n";
	}
	if (tree.searchCount([](int x) { return x % 2 == 0; }) != 3) {
		std::cout << tree.countEvens() << "\n";
	} else {
		std::cout << "Test for searchCount passes\n";
	}
	if (tree.height() != 3) {
		std::cout << tree.height() << "\n";
	} else {
		std::cout << "Test for height passes\n";
	}
	if (tree.countLeaves() != 3) {
		std::cout << tree.countLeaves() << "\n";
	} else {
		std::cout << "Test for countLeaves passes\n";
	}
	// BinTree<int> tree2(tree);
}

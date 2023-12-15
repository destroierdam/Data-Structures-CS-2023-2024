
#include <cstddef>
#include <vector>
#include <iostream>

const std::size_t ROWS = 4, COLS = 4;
const std::size_t N_IN_A_ROW = 4;

struct Node {
	int board[ROWS][COLS];
	std::vector<Node*> children;

	Node(int board[ROWS][COLS]) {
		for(std::size_t i = 0; i < ROWS; ++i) {
			for(std::size_t j = 0; j < COLS; ++j) {
				this->board[i][j] = board[i][j];
			}
		}
	}

	void printBoard() const {
		for(std::size_t i = 0; i < ROWS; ++i) {
			for(std::size_t j = 0; j < COLS; ++j) {
				std::cout << board[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};

bool isSolved(int board[ROWS][COLS]) {
	bool hasEmptySpace = false;

	for(std::size_t i = ROWS - 1; (0 <= i && i < ROWS); --i) {

		for(std::size_t j = 0; j <= COLS - N_IN_A_ROW; ++j) {
			int element = board[i][j];

	 		bool hasNInARow = true;

			for(std::size_t k = j; k < j + N_IN_A_ROW; ++k) {
				if (board[i][k] == 0) {
					hasEmptySpace = true;
				}
				if (element != board[i][k]) {
					hasNInARow = false;
				}
			}
			if (hasNInARow && element != 0) {
				std::cout << "Has N in a row\n";
				return true;
			}
		}
	}
	return hasEmptySpace == false;
}

void generateTree(Node* root, int currentPlayer) {
	root->printBoard();
	std::cout << "\n";

	if (isSolved(root->board)) {
		std::cout << "Board is solved\n";
		return;
	}
	for(std::size_t j = 0; j < COLS; ++j) {
		for(std::size_t i = ROWS - 1; (ROWS >= i && i >= 0); --i) {
			if (root->board[i][j] == 0) {
				// 
				Node* newNode = new Node(root->board);
				newNode->board[i][j] = currentPlayer;
				std::cout << "Child of board \n";
				root->printBoard();
				std::cout << "Is \n";
				newNode->printBoard(); 
				std::cout << "\n";
				
				root->children.push_back(newNode);
				

				break;
			}
		}
	}

	for(std::size_t i = 0; i < root->children.size(); ++i) {
		generateTree(root->children[i], (currentPlayer == 1 ? 2 : 1));
	}
}

int main() {
	int board[ROWS][COLS] = {{ 0, 0, 0, 0 },
							 { 1, 0, 0, 0 },
							 { 2, 2, 1, 2 },
							 { 1, 1, 2, 1 } };
	Node* root = new Node(board);
	generateTree(root, 2);
}

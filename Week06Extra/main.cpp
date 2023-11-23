#include <iostream>

template<typename T>
struct box {
    T data;
    box *next;
	box *prev;
};

template<typename T>
void complete(box<T>* l1, box<T>* l2, unsigned int k) {
    box<T>* l1It = l1, *l2It = l2, *ifMismatchedContinueFromHere = l1;

    unsigned int prefixLength = 0;
    
	while (l1It != nullptr) {
		std::cout << "Working on l1: " << l1It->data << " and l2: " << l2It->data << "\n";

        if (l1It->data == l2It->data) {
            prefixLength++;
			std::cout << "Match found, prefix length: " << prefixLength << "\n";
			if(prefixLength == 1) {
				ifMismatchedContinueFromHere = l1It;
			}
			std::cout << "incrementing it1 and it2 to ";
			l2It = l2It->next;
			l1It = l1It->next;
			std::cout << l1It->data << " and " << l2It->data << "\n";
        } else {
			std::cout << "Mismatch found; ";
			if (prefixLength >= k) {
				std::cout << "Copying to l1\n";
				// Add to l1
				while(l2It != nullptr) {
					box<T>* newBox = new box<T>{l2It->data, l1It, l1It->prev};
					if (l1It->prev) {
						l1It->prev->next = newBox;
					}
					if (l1It->next) {
						l1It->next->prev = newBox;
					}

					// l1It->next = newBox;
					l2It = l2It->next;
					// l1It = l1It->next;
				}
				l2It = l2;
				l1It = l1It->next;
			} else {
				prefixLength = 0;
				l1It = ifMismatchedContinueFromHere;
				l2It = l2;
			}
        }
        // l1It = l1It->next;
    }
}

template<typename T>
void print(box<T>* l) {
    while(l) {
        std::cout << l->data << " -> ";
		l = l->next;
    }
    std::cout << "nullptr\n";
}

int main() {
    box<int>* l1 = new box<int> {1, nullptr, nullptr};
	auto b2 = new box<int> {5};
	auto b3 = new box<int> {6};
	auto b4 = new box<int> {11};
	auto b5 = new box<int>{1};
	auto b6 = new box<int>{1};
	auto b7 = new box<int>{5};
	l1->next = b2;
	b2->prev = l1;
	b2->next = b3;
	b3->prev = b2;
	b3->next = b4;
	b4->prev = b3;
	b4->next = b5;
	b5->prev = b4;
	b5->next = b6;
	b6->prev = b5;
	b6->next = b7;
	b7->prev = b6;
    
	box<int>* l2 = new box<int> {1};
	auto bb2 = new box<int> {5};
	auto bb3 = new box<int>{99};
	l2->next = bb2;
	bb2->prev = l2;
	bb2->next = bb3;
	bb3->prev = bb2;


    complete(l1, l2, 2);
    print(l1);
}

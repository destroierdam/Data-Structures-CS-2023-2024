#include <iostream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <vector>

template<typename T>
struct box {
	T data;
	box* next;
	box* prev;
};

template<typename T>
void complete(box<T> * const l1, box<T> * const l2, const unsigned int k, std::ostream& log) {
	if (l1 == nullptr || l2 == nullptr || k == 0) { 
		std::string message = "Invalid input parameters to complete";
		log << message << "\n";
		throw std::runtime_error(message);
	}

	box<T> * it1 = l1;
	box<T> * it2 = l2;

	box<T>* prevIt1 = nullptr;

	unsigned int prefixLength = 0;

	while (it1 != nullptr) {
		prevIt1 = it1;
		log << "Working on it1: " << it1->data << " and it2: " << it2->data << "\n";


		// Match as many elements as you can from both lists, counting the number of the matched elements.
		// Be careful not to fall off the end of either list, otherwise you wil dereference a nullptr.
		while (it1 != nullptr && it2 != nullptr && it1->data == it2->data) {
			prefixLength++;
			log << "Match found: " << it2->data << "\n";
			it1 = it1->next;
			it2 = it2->next;
		}
		bool noElementsLeftInL2 = it2 == nullptr;
		bool noElementsLeftInL1 = it1 == nullptr;

		if (noElementsLeftInL1) { 
			log << "No elements left in L1\n";
			break;
		}


		if (noElementsLeftInL2) {
			log << "No elements left in L2\n";
			prefixLength = 0;
			it2 = l2;
			continue;
		}

		if (prefixLength >= k) {
			log << "Prefix found, and it is lengthy enough to complete it with the rest of L2.\n";
			// Put the new boxes behind the current box, pointed by it1.
			while (it2 != nullptr) {
				log << "Inserting " << it2->data << "\n";
				box<T>* newBox = new box<T>{ it2->data, nullptr, nullptr };
				// Insert the new box behind the current;
				newBox->prev = it1->prev;
				newBox->next = it1;

				// Since k > 0 there will always be a previous element in L1. No need to check whether it1->prev != nullptr
				it1->prev->next = newBox;
				it1->prev = newBox;

				it2 = it2->next;
			}
		} else {
			log << "Prefix not found\n";
			it1 = prevIt1->next;
		}
		prefixLength = 0;
		it2 = l2;
	}

	if (prefixLength >= k) {
		// Go to last element in l1
		it1 = prevIt1;
		while (it1->next != nullptr) { it1 = it1->next; }

		while (it2 != nullptr) {
			box<T>* newBox = new box<T>{ it2->data, nullptr, it1 };

			it1->next = newBox;
			it2 = it2->next;
			it1 = it1->next;
		}
	}
}

template<typename T>
void print(box<T>* l, std::ostream& out = std::cout) {
	int i = 0;
	while (l && i < 50) {
		out << l->data << " -> ";
		if (l->next) {
			if (l->next->prev != l) {
				out << "Wrong list\n";
			}
		}
		l = l->next;
		i++;


	}
	if (i == 50) {
		out << "Infinite list\n";
	}
	out << "nullptr\n";
}

template<typename T>
box<T>* makeList(const std::vector<T>& data) {
	if (data.size() == 0) return nullptr;
	box<T>* list = new box<T>{ data[0], nullptr, nullptr };
	box<T>* it = list;
	for (std::size_t i = 1; i < data.size(); ++i) {
		it->next = new box<T>{ data[i], nullptr, it };
		it = it->next;
	}
	return list;
}

template<typename T>
void test(const std::vector<T>& l1Data, const std::vector<T>& l2Data, const unsigned int k, const std::string& answer, const std::string& testName) {
	box<int>* l1 = makeList(l1Data);
	box<int>* l2 = makeList(l2Data);

	std::stringstream log;
	complete(l1, l2, k, log);

	std::stringstream result;
	print(l1, result);
	std::cout << testName << " ";
	if (answer != result.str()) {
		std::cout << "incorrect\n";
		std::cout << "Expected:\n" << answer << "\n";
		std::cout << "Got:\n" << result.str() << "\n";
		std::cout << "Debug log:\n----------------------------------------------\n";
		std::cout << log.str() << "\n----------------------------------------------\n";
	}
	else {
		std::cout << "passed\n";
	}
}

void testExample() {
	std::vector<int> l1Data = { 1, 2, 9, 1, 1, 2 };
	std::vector<int> l2Data = { 1, 2, 3 };
	unsigned int k = 2;
	std::string answer = "1 -> 2 -> 3 -> 9 -> 1 -> 1 -> 2 -> 3 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Example test");
}

void testMyExample() {
	std::vector<int> l1Data = {1, 5, 6, 11, 1, 1, 5};
	std::vector<int> l2Data = { 1, 5, 99 };
	unsigned int k = 2;
	std::string answer = "1 -> 5 -> 99 -> 6 -> 11 -> 1 -> 1 -> 5 -> 99 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "My example test");
}

void testLongInitialPartialMatch() {
	std::vector<int> l1Data = { 1, 1, 1, 1, 5, 6, 11, 1, 1, 5 };
	std::vector<int> l2Data = { 1, 5, 99 };
	unsigned int k = 2;
	std::string answer = "1 -> 1 -> 1 -> 1 -> 5 -> 99 -> 6 -> 11 -> 1 -> 1 -> 5 -> 99 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Long initial partial match");
}

void testLongInitialPartialMatchBigK() {
	std::vector<int> l1Data = { 1, 1, 5, 1, 5, 7, 1, 5, 7, 9, 6, 11, 1, 1, 5 };
	std::vector<int> l2Data = { 1, 5, 7, 9, 11 };
	unsigned int k = 4;
	std::string answer = "1 -> 1 -> 5 -> 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 9 -> 11 -> 6 -> 11 -> 1 -> 1 -> 5 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Long initial partial match Big K");
}

void testNoMatch() {
	std::vector<int> l1Data = { 2, 3, 5, 11, 5, 7, 4, 5, 7, 9, 6, 11, 6, 7, 5 };
	std::vector<int> l2Data = { 1, 5, 7, 9, 11 };
	unsigned int k = 4;
	std::string answer = "2 -> 3 -> 5 -> 11 -> 5 -> 7 -> 4 -> 5 -> 7 -> 9 -> 6 -> 11 -> 6 -> 7 -> 5 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "No match");
}

void testMatchNoAddition() {
	std::vector<int> l1Data = { 1, 1, 5, 1, 5, 7, 1, 5, 7, 6, 11, 1, 1, 5 };
	std::vector<int> l2Data = { 1, 5, 7, 9, 11 };
	unsigned int k = 4;
	std::string answer = "1 -> 1 -> 5 -> 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 6 -> 11 -> 1 -> 1 -> 5 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Match no addition");
}

void testMatchK1() {
	std::vector<int> l1Data = { 1, 2, 9, 1, 1, 2 };
	std::vector<int> l2Data = { 1, 2, 3 };
	unsigned int k = 1;
	std::string answer = "1 -> 2 -> 3 -> 9 -> 1 -> 2 -> 3 -> 1 -> 2 -> 3 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Test match with k = 1");
}

void testConsecutiveAddition() {
	std::vector<int> l1Data = { 1, 2, 1, 2, 9, 1, 1, 2 };
	std::vector<int> l2Data = { 1, 2, 3 };
	unsigned int k = 2;
	std::string answer = "1 -> 2 -> 3 -> 1 -> 2 -> 3 -> 9 -> 1 -> 1 -> 2 -> 3 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Test adding consecutively");
}

void testFullMatchSoNoAddition() {
	std::vector<int> l1Data = { 1, 2, 3, 9, 1, 1, 2, 3 };
	std::vector<int> l2Data = { 1, 2, 3 };
	unsigned int k = 2;
	std::string answer = "1 -> 2 -> 3 -> 9 -> 1 -> 1 -> 2 -> 3 -> nullptr\n";
	test(l1Data, l2Data, k, answer, "Test full match with no addition necessary");
}

void runTests() {
	std::function<void()> tests[] = {
		testExample,
		testMyExample,
		testLongInitialPartialMatch,
		testLongInitialPartialMatchBigK,
		testNoMatch,
		testMatchNoAddition,
		testFullMatchSoNoAddition,
		testMatchK1,
		testConsecutiveAddition
	};
	std::size_t testsSize = sizeof(tests) / sizeof(tests[0]);
	for (std::size_t i = 0; i < testsSize; ++i) {
		tests[i]();
	}
}

int main() {
	runTests();
}

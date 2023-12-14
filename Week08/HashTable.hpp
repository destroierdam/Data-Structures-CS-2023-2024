#pragma once
#include <cstddef>
#include <functional>
#include <vector>

template<typename Key, typename Value, std::size_t TABLE_SIZE = 10>
class HashTable {
public:

	HashTable() : table(TABLE_SIZE) {
		hashFunction = [](Key key) -> std::size_t {
			return std::hash<Key>()(key);
		};

		// hashFunction = std::hash<Key>();

		for(std::size_t i = 0; i < TABLE_SIZE; ++i) {
			this->table[i] = nullptr;
		}
		std::cout << "asd";
	}


	Value& operator[](const Key& key) {
		std::size_t index = this->hashFunction(key) % TABLE_SIZE;
		
		Node* prev = nullptr;
		Node* bucket = table[index];
		while (bucket != nullptr) {
			if (bucket->data.key == key) {
				return bucket->data.value;
			}
			prev = bucket;
			bucket = bucket->next;
		}
		if (prev != nullptr) {
			prev->next = new Node(Pair(key, Value()), nullptr);
			return prev->next->data.value;
		} else {
			table[index] = new Node(Pair(key, Value()), nullptr);
			return table[index]->data.value;
		}


		Node** nodeToChange = &table[index];
		while (*nodeToChange != nullptr) {
			if ((*nodeToChange)->data.key == key) {
				return (*nodeToChange)->data.value;
			}
			nodeToChange = &((*nodeToChange)->next);
		}
		(*nodeToChange) = new Node(Pair(key, Value()), nullptr);
		return (*nodeToChange)->data.value;
	}
private:
	struct Pair {
		Key key;
		Value value;
		Pair(const Key& key, const Value& value): key(key), value(value){}
	};
	struct Node {
		Pair data;
		Node* next;
		Node(const Pair& data, Node* next): data(data), next(next){}
	};
private:

	std::vector<Node*> table;

	std::function<std::size_t(const Key&)> hashFunction;
};


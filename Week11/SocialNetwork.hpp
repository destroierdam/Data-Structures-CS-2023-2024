
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>

enum GENDER { GENDER_MALE , GENDER_FEMALE, GENDER_OTHER };

class SocialNetwork {
public:
	struct User {
		std::string name, email;
		GENDER gender;

		User(const std::string& name, const std::string& email, GENDER gender): 
			name(name), email(email), gender(gender){}

		bool isMale() const {
			return this->gender == GENDER_MALE;
		}
		bool isFemale() const {
			return this->gender == GENDER_FEMALE;
		}
		void print() const {
			std::cout << "Name: " << this->name 
				<< ", email: " << this->email
				<< ", gender: " << this->gender << "\n";
		}
		bool operator==(const User& other) const {
			return this->name == other.name &&
				   this->email == other.email &&
				   this->gender == other.gender;
		}
	};
public:

	void addPerson(const User& newUser) {
		this->users.push_back(newUser);
		this->friendships.push_back(std::vector<std::size_t>());
	}
	bool hasPerson(const User& user) const {
		return std::find(this->users.begin(), this->users.end(), user) != users.end();
	}
	void makeFriends(const User& u1, const User& u2) {
		std::size_t u1Index = this->findIndexOf(u1);

		if (u1Index == this->users.size()) { // User is not in the network
			this->addPerson(u1);
		}
		
		std::size_t u2Index = this->findIndexOf(u2);
		if (u2Index == this->users.size()) { // User is not in the network
			this->addPerson(u2);
		}
		if (this->areFriends(u1, u2)) {
			throw std::runtime_error("These people are already friends");
		}
		
		this->friendships[u1Index].push_back(u2Index);
		this->friendships[u2Index].push_back(u1Index);
	}
	bool areFriends(const User& u1, const User& u2) const {
		std::size_t u1Index = this->findIndexOfThrows(u1);
		std::size_t u2Index = this->findIndexOfThrows(u2);

		for(std::size_t i = 0; i < this->friendships[u1Index].size(); ++i) {
			
			// if (this->users[this->friendships[u1Index][i]] == u2) {
			if (this->friendships[u1Index][i] == u2Index) {
				return true;
			}
		}
		return false;
	}

	std::vector<User> friendsOf(const User& user) {
		std::size_t index = this->findIndexOfThrows(user);
		
		std::vector<User> result;

		for (std::size_t friendIndex : this->friendships[index]) {
			result.push_back(this->users[friendIndex]);
		}
		return result;
	}
	void deleteUser(const User& toBeDeleted) {
		std::size_t indexToBeDeleted = this->findIndexOfThrows(toBeDeleted);
		
		if (this->users.size() == 1) { // User is the only one
			this->users.clear();
			this->friendships.clear();
			return;
		}

		if (indexToBeDeleted == this->users.size() - 1) { // user is the last user

			for(std::size_t friendIndex : this->friendships[indexToBeDeleted]) {

				// this->friendships[friendIndex].erase(indexToBeDeleted);
				
				this->removeElementFromVector(this->friendships[friendIndex], indexToBeDeleted);
			}
			this->friendships.pop_back();
			this->users.pop_back();
			return;
		}

		for(std::size_t friendIndex : this->friendships[indexToBeDeleted]) {
			this->removeElementFromVector(this->friendships[friendIndex], indexToBeDeleted);
		}
		std::swap(this->friendships[indexToBeDeleted], this->friendships.back());
		this->friendships.pop_back();
		for(std::size_t friendIndex : this->friendships[indexToBeDeleted]) {
			this->replaceElement(this->friendships[friendIndex], this->friendships.size(), indexToBeDeleted);
		}

		std::swap(this->users[indexToBeDeleted], this->users.back());
		this->users.pop_back();

	}
/*

P  T  a  e
0, 1, 2, 3

0: 1, 2, 3
1: 0, 3
2: 0
3: 2, 0, 1


*/


	// hasPath(u1, u2) {

	// 	vector<size_t> visited;

	// 	dfs(u1, visited);

	// 	return visited.contains(u2);
	// }

	// dfs(user, &  visited) {
	// 	if (visited.contains(user)) {
	// 		return;
	// 	}

	// 	visited.push(user);

	// 	// cout "Visiting " + user.name

	// 	for(size_t friend : user.friends) {
	// 		dfs(friend);
	// 	}

	// }

	void printGraph() const {
		for (std::size_t i = 0; i < this->friendships.size(); ++i) {
			std::cout << i << ": ";
			for (auto person : this->friendships[i]) {
				std::cout << person << " ";
			}
			std::cout << std::endl;
		}
	}

	bool areConnected(const User& u1, const User& u2) {
		std::size_t u1Index = this->findIndexOfThrows(u1);
		std::size_t u2Index = this->findIndexOfThrows(u2);


		std::set<std::size_t> visited;
		std::queue<std::size_t> queue;
		queue.push(u1Index);

		while(queue.empty() == false) {
			std::size_t currentIndex = queue.front();
			queue.pop();


			// if (visited.count(currentIndex)) {
			// 	continue;
			// }

			visited.insert(currentIndex);

			if (currentIndex == u2Index) {
				return true;
			}

			for (std::size_t friendIndex : this->friendships[currentIndex]) {

				if (visited.count(friendIndex) == 0) {
					queue.push(friendIndex);
				}
			}

		}
		return false;
	}

	std::vector<User> getClosestFriends(const User& user, std::size_t distance) const {
		std::size_t userIndex = this->findIndexOfThrows(user);

		std::set<std::size_t> visited;

		std::vector<User> friends;

		std::function<void(std::size_t)> f = 
			[&friends, userIndex, &users = this->users] (std::size_t friendIndex) {
				
			if (friendIndex != userIndex) {
				friends.push_back(users[friendIndex]);
			}
		};

		dfs(userIndex, visited, f, distance + 1);
		return friends;
	}
	
private:


	void dfs(std::size_t userIndex, std::set<std::size_t>& visited, std::function<void(std::size_t)> f, std::size_t depth) const {
		if (depth == 0) {
			return;
		}
		if (visited.count(userIndex)) {
			return;
		}
		visited.insert(userIndex);

		f(userIndex);

		for(std::size_t i = 0; i < this->friendships[userIndex].size(); ++i) {
			dfs(this->friendships[userIndex][i], visited, f, depth - 1);
		}
	}

	void removeElementFromVector(std::vector< std::size_t> & vec, std::size_t element) {
		for(std::size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] == element) {
				std::size_t lastElement = vec.back();
				vec[i] = lastElement;
				vec.pop_back();
			}
		}
	}

	void replaceElement(std::vector< std::size_t> & vec, std::size_t element, std::size_t replacement) {
		for(std::size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] == element) {
				vec[i] = replacement;
			}
		}
	}

	std::size_t findIndexOfThrows(const User& user) const {
		std::size_t index = this->findIndexOf(user);
		if (index == this->users.size()) {
			throw std::runtime_error("User does not exist");
		}
		return index;
	}

	std::size_t findIndexOf(const User& user) const {
		for(std::size_t i = 0; i < this->users.size(); ++i) {
			if (this->users[i] == user) {
				return i;
			}
		}
		return this->users.size();
	}
private:
	std::vector<User> users;
	std::vector<std::vector<std::size_t> > friendships;
};

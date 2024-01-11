
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	SocialNetwork() {
		
	}

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
		std::size_t u1Index = this->findIndexOf(u1);
		std::size_t u2Index = this->findIndexOf(u2);

		for(std::size_t i = 0; i < this->friendships[u1Index].size(); ++i) {
			
			// if (this->users[this->friendships[u1Index][i]] == u2) {
			if (this->friendships[u1Index][i] == u2Index) {
				return true;
			}
		}
		return false;
	}
private:
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

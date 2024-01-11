#include <iostream>
#include <cassert>
#include "SocialNetwork.hpp"

int main() {
	SocialNetwork sn;
	SocialNetwork::User atanas = SocialNetwork::User("Atanas", "nasko@mail.com", GENDER_MALE);
	SocialNetwork::User kiro = SocialNetwork::User("Kiro", "Kiro@mail.com", GENDER_MALE);
	SocialNetwork::User penka = SocialNetwork::User("Penka", "penka@mail.com", GENDER_FEMALE);
	SocialNetwork::User kali = SocialNetwork::User("kali", "kali@mail.com", GENDER_FEMALE);
	sn.addPerson(atanas);
	sn.addPerson(kiro);
	// sn.addPerson(penka);
	assert(sn.hasPerson(atanas));

	sn.makeFriends(atanas, kiro);
	try {
		sn.makeFriends(atanas, kiro);
	} catch (std::runtime_error& error) {
		if (std::string(error.what()) == std::string("These people are already friends")) {
			// correct exception
		} else {
			assert(false);
		}
		// std::cout << error.what();
	}
	sn.makeFriends(kali, penka);
}
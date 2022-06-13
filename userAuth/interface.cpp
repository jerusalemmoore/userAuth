#include "interface.h"

#define FIRST true //flag for processing string as first name in functions

Interface::Interface() {
	account = new AccountInfo();
}
Interface::~Interface() {
	delete account;
}
/*
	run firstNameConfirmed until valid name is produced
	run lastNameConfirmed until valid name is produced
*/

void Interface::runInterface() {
	std::cout << "Please enter requested credentials" << std::endl;
	bool firstNameConfirmed = false;
	do {
		firstNameConfirmed = processFirstName();
	} while (!firstNameConfirmed);
	bool lastNameConfirmed = false;
	do {
		lastNameConfirmed = processLastName();
	} while (!lastNameConfirmed);
}

std::string Interface::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleaned name " << name << std::endl;
	return name;
}/*
	routine for extracting first name from user input
	return false until first name is verified and cleaned
*/

bool Interface::processFirstName() {
	std::cout << "Please enter valid first name" << std::endl;
	std::string firstName;
	std::cin >> firstName;
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}
bool Interface::processLastName() {
	std::cout << "Please enter valid last name" << std::endl;
	std::string lastName;
	std::cin >> lastName;
	bool confirmed = confirmName(lastName, !FIRST);
	return confirmed;
}
bool Interface::confirmName(std::string name, bool isFirst) {
	//just get the first string of input to evaluate as the first name 
//this line clears the buffer so the remaining inputs don't register for the following confirmation
//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm " << (isFirst ? "first" : "last") << "name is correct(y / n) : " << name << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "y") {
			//user confirmed, make sure name is alphabetical
			return isNameAlpha(name, isFirst);
		}
		else if (choice == "n") {
			std::cout << "Please re-enter " << (isFirst ? "first" : "last") << " name" << std::endl;
			return false;
		}
		else {
			std::cout << "invalid entry please try again..." << std::endl;
		}
	}
}

bool Interface::isNameAlpha(std::string name, bool first) {
	//is name alphabetical, if not return false 
	if (std::regex_match(name, std::regex("^[A-Za-z]+$"))) {
		std::cout << "all good" << std::endl;
		//std::cout << "Continuing" << std::endl;
		name = cleanName(name);
		if (first) {
			account->setFirstName(name);
		}
		else if (!first) {
			account->setLastName(name);
		}
		//might not need this, first is bool so shouldn't get anything unexpected 
		else {
			std::cout << "Error, invalid type: " << first << std::endl;
			return false;
		}
		//std::cout << "First name confirmed: " << firstName << std::endl;
		return true;
	}
	std::cout << "Error, name can only contain alphabetic characters" << std::endl;
	return false;


}
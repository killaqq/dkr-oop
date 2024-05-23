#include "Customer.h"

#include <sstream>

Customer::Customer()
	: id(0), lastName(""), firstName(""), creditCardNumber(0), bankAccountNumber(0) {}

Customer::Customer(int id, const char* lastName, const char* firstName, int creditCardNumber, int bankAccountNumber)
	: id(id), creditCardNumber(creditCardNumber), bankAccountNumber(bankAccountNumber)
{
	setLastName(lastName);
	setFirstName(firstName);
}

void Customer::setId(int id) { this->id = id; }

void Customer::setLastName(const char* lastName) { strcpy_s(this->lastName, lastName); }

void Customer::setFirstName(const char* firstName) { strcpy_s(this->firstName, firstName); }

void Customer::setCreditCardNumber(int creditCardNumber) { this->creditCardNumber = creditCardNumber; }

void Customer::setBankAccountNumber(int bankAccountNumber) { this->bankAccountNumber = bankAccountNumber; }

int Customer::getId() const { return id; }

const char* Customer::getLastName() const { return lastName; }

const char* Customer::getFirstName() const { return firstName; }

int Customer::getCreditCardNumber() const { return creditCardNumber; }

int Customer::getBankAccountNumber() const { return bankAccountNumber; }

std::string Customer::toString() const
{
	std::stringstream ss;
	ss << "ID: " << id << ", Last Name: " << lastName << ", First Name: " << firstName
		<< ", Credit Card Number: " << creditCardNumber << ", Bank Account Number: " << bankAccountNumber;
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Customer& customer)
{
	os << customer.toString();
	return os;
}

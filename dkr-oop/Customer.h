#pragma once

#include <string>

class Customer
{
    friend std::ostream& operator<<(std::ostream& os, const Customer& customer);
public:
    Customer();
    Customer(int id, const char* lastName, const char* firstName, int creditCardNumber, int bankAccountNumber);

    void setId(int id);
    void setLastName(const char* lastName);
    void setFirstName(const char* firstName);
    void setCreditCardNumber(int creditCardNumber);
    void setBankAccountNumber(int bankAccountNumber);

    int getId() const;
    const char* getLastName() const;
    const char* getFirstName() const;
    int getCreditCardNumber() const;
    int getBankAccountNumber() const;

    std::string toString() const;

private:
    int id;
    char lastName[64];
    char firstName[64];
    int creditCardNumber;
    int bankAccountNumber;
};


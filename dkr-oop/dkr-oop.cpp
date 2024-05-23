#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "Customer.h"
#include "Encryptor.h"
#include "Logger.h"

using namespace std;

vector<Customer> filterByCreditCardNumber(const vector<Customer>& customers, int lower, int upper) {
	vector<Customer> result;
	for (const auto& customer : customers) {
		if (customer.getCreditCardNumber() >= lower && customer.getCreditCardNumber() <= upper) {
			result.push_back(customer);
		}
	}
	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logger logger("log.txt");
	logger.log("Програма запущена");

	vector<Customer> customers;
	int option;
	do
	{
		cout << "Прочитати датні з файлу (1) чи використати значення за замовчуванням (2)?\n>> ";
		cin >> option;
		if (option != 1 && option != 2)
			cout << "Некоректне введення\n";
	} while (option != 1 && option != 2);
	if (option == 1)
	{
		string fileName;
		cout << "Введіть назву файлу: ";
		cin.ignore();
		getline(cin, fileName);
		ifstream inFile(fileName, ios::binary);
		if (inFile.is_open())
		{
			while (true)
			{
				int buffSize;
				inFile.read(reinterpret_cast<char*>(&buffSize), sizeof(buffSize));
				if (inFile.eof()) break;
				char* chBuff = new char[buffSize];
				inFile.read(chBuff, buffSize);
				string buff;
				for (size_t i = 0; i < buffSize; i++)
					buff += chBuff[i];
				buff = Encryptor::decrypt(buff);
				customers.push_back(*(reinterpret_cast<const Customer*>(buff.c_str())));
				delete[] chBuff;
			}
			inFile.close();
			logger.log("Дані прочитані з файлу та розшифровані");
		}
		else
		{
			cerr << "Failed to open input file!" << endl;
			return 1;
		}
	}
	else
	{
		customers = {
			Customer(1, "Smith", "John", 1234, 56789),
			Customer(2, "Doe", "Jane", 2345, 67890),
			Customer(3, "Brown", "Charlie", 3456, 78901),
			Customer(4, "Taylor", "Ann", 4567, 89012)
		};
	}

	sort(customers.begin(), customers.end(),
		[](const Customer& a, const Customer& b) {
			return a.getLastName() < b.getLastName();
		});
	cout << "Список покупців в алфавітному порядку:" << endl;
	for (const auto& customer : customers)
	{
		cout << customer << endl;
	}

	int lowerBound = 2000;
	int upperBound = 4000;
	vector<Customer> filteredCustomers = filterByCreditCardNumber(customers, lowerBound, upperBound);
	if (filteredCustomers.size() > 0)
	{
		cout << "\nСписок покупців, у яких номер кредитної картки знаходиться в інтервалі [" << lowerBound << ", " << upperBound << "]:" << endl;
		for (const auto& customer : filteredCustomers)
		{
			cout << customer << endl;
		}
	}
	else
	{
		cout << "\nСписок покупців, у яких номер кредитної картки знаходиться в інтервалі [" << lowerBound << ", " << upperBound << "] не знайдено" << endl;
	}

	string fileName;
	cout << "Введіть назву файлу: ";
	cin.ignore();
	getline(cin, fileName);
	ofstream outFile(fileName, ios::binary);
	if (outFile.is_open())
	{
		for (const auto& customer : customers)
		{
			string buff;
			const char* chBuff = reinterpret_cast<const char*>(&customer);
			for (size_t i = 0; i < sizeof(Customer); i++)
				buff += chBuff[i];
			buff = Encryptor::encrypt(buff);
			int buffSize = buff.size();
			outFile.write(reinterpret_cast<const char*>(&buffSize), sizeof(buffSize));
			outFile.write(buff.c_str(), buffSize);
		}
		outFile.close();
		logger.log("Дані зашифровані та записані у файл '" + fileName + "'");
	}
	else
	{
		cerr << "Failed to open output file!" << endl;
	}

	logger.log("Програма завершена");

	return 0;
}

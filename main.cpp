#include <iostream>
#include <string>

#include "hasher.h"

int main() {
	Hasher hasher;
	std::wstring message;
	std::wcout << L"Enter message: ";
	std::getline(std::wcin, message);
	std::wcout << L"Hash: " << hasher.Hash(message) << std::endl;

	return 0;
}
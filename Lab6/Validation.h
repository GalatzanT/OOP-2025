#pragma once
#include <vector>
#include <string>
#include "Medicament.h"
#include <assert.h>
using std::string;
using std::vector;




class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() const{
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};

class MedicamentValidation {
public:
	void validate(const Medicament& medicament) {
		vector<string> errorMessages;
		if (medicament.getDenumire().empty()) {
			errorMessages.push_back("Denumirea nu poate fi vida!");
		}
		if (medicament.getPret() <= 0) {
			errorMessages.push_back("Pretul trebuie sa fie mai mare decat 0!");
		}
		if (medicament.getProducator().empty()) {
			errorMessages.push_back("Producatorul nu poate fi vid!");
		}
		if (medicament.getSubstantaActiva().empty()) {
			errorMessages.push_back("Substanta activa nu poate fi vida!");
		}
		if (!errorMessages.empty()) {
			throw ValidationException(errorMessages);
		}
	}
};


	
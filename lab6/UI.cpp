#include <iostream>
using namespace std;
#include "Service.h"
//7 Farmacie
//Creați o aplicație care permite :
//· gestiunea unei liste de medicamente.Medicament : denumire, preț, producător,
//substanța activa
//· adăugare, ștergere, modificare și afișare medicamente
//· căutare medicament
//· filtrare medicamente după : preț, substanța activa
//· sortare medicamente după : denumire, producător, substanța activa + preț

void testValidation() {
	MedicamentValidation validator;


	Medicament validMed(1, "Paracetamol", 10.0, "GSK", "Acetaminofen");
	validator.validate(validMed);


	try {
		Medicament m(2, "", 10.0, "GSK", "Substanta");
		validator.validate(m);

	}
	catch (const ValidationException& ex) {
		string msg = ex.getErrorMessages();
		assert(msg.find("Denumirea nu poate fi vida!") != string::npos);
	}


	try {
		Medicament m(3, "Nurofen", 0, "GSK", "Ibuprofen");
		validator.validate(m);
	}
	catch (const ValidationException& ex) {
		string msg = ex.getErrorMessages();
		assert(msg.find("Pretul trebuie sa fie mai mare decat 0!") != string::npos);
	}

	try {
		Medicament m(4, "Nurofen", 10, "", "Ibuprofen");
		validator.validate(m);

	}
	catch (const ValidationException& ex) {
		string msg = ex.getErrorMessages();
		assert(msg.find("Producatorul nu poate fi vid!") != string::npos);
	}


	try {
		Medicament m(5, "Nurofen", 10, "GSK", "");
		validator.validate(m);

	}
	catch (const ValidationException& ex) {
		string msg = ex.getErrorMessages();
		assert(msg.find("Substanta activa nu poate fi vida!") != string::npos);
	}

	try {
		Medicament m(6, "", -5, "", "");
		validator.validate(m);
	}
	catch (const ValidationException& ex) {
		string msg = ex.getErrorMessages();
		assert(msg.find("Denumirea nu poate fi vida!") != string::npos);
		assert(msg.find("Pretul trebuie sa fie mai mare decat 0!") != string::npos);
		assert(msg.find("Producatorul nu poate fi vid!") != string::npos);
		assert(msg.find("Substanta activa nu poate fi vida!") != string::npos);
	}
}
void static testAll() {
	testMedicament();
	testRepo();
	testService();
	testValidation();
}
void printMenu() {
	cout << "Lab 6 Farmacie Tudor Galatan\n";
	cout << "1.Afiseaza medicamente\n";
	cout << "2.Adauga medicament\n";
	cout << "3.Sterge medicament\n";
	cout << "4.Update medicament\n";
	cout << "5.Cautare medicament\n";
	cout << "6.Filtrare medicamente dupa : pret\n";
	cout << "7.Sortare medicamente dupa : producator, pret\n";
	cout << "8.Iesire\n";
}
void afiseaza_medicamente(const vector<Medicament>& medicamente) {
	for (const auto& medicament : medicamente) {
		cout << medicament << endl;
	}
}

void add_10_meds(Service& s) {
	Medicament m1(1, "Paracetamol", 10.5, "Farmaceutica", "Paracetamol");
	Medicament m2(2, "Ibuprofen", 15.0, "Farmaceutica", "Ibuprofen");
	Medicament m3(3, "Aspirin", 12.0, "Farmaceutica", "Aspirin");
	Medicament m4(4, "Amoxicillin", 20.0, "Farmaceutica", "Amoxicillin");
	Medicament m5(5, "Ciprofloxacin", 25.0, "Farmaceutica", "Ciprofloxacin");
	Medicament m6(6, "Metformin", 30.0, "Farmaceutica", "Metformin");
	Medicament m7(7, "Atorvastatin", 35.0, "Farmaceutica", "Atorvastatin");
	Medicament m8(8, "Simvastatin", 40.0, "Farmaceutica", "Simvastatin");
	Medicament m9(9, "Omeprazole", 45.0, "Farmaceutica", "Omeprazole");
	Medicament m10(10, "Levothyroxine", 50.0, "Farmaceutica", "Levothyroxine");

	s.addMedicament(m1.getId(), m1.getDenumire(), m1.getPret(), m1.getProducator(), m1.getSubstantaActiva());
	s.addMedicament(m2.getId(), m2.getDenumire(), m2.getPret(), m2.getProducator(), m2.getSubstantaActiva());
	s.addMedicament(m3.getId(), m3.getDenumire(), m3.getPret(), m3.getProducator(), m3.getSubstantaActiva());
	s.addMedicament(m4.getId(), m4.getDenumire(), m4.getPret(), m4.getProducator(), m4.getSubstantaActiva());
	s.addMedicament(m5.getId(), m5.getDenumire(), m5.getPret(), m5.getProducator(), m5.getSubstantaActiva());
	s.addMedicament(m6.getId(), m6.getDenumire(), m6.getPret(), m6.getProducator(), m6.getSubstantaActiva());
	s.addMedicament(m7.getId(), m7.getDenumire(), m7.getPret(), m7.getProducator(), m7.getSubstantaActiva());
	s.addMedicament(m8.getId(), m8.getDenumire(), m8.getPret(), m8.getProducator(), m8.getSubstantaActiva());
	s.addMedicament(m9.getId(), m9.getDenumire(), m9.getPret(), m9.getProducator(), m9.getSubstantaActiva());
	s.addMedicament(m10.getId(), m10.getDenumire(), m10.getPret(), m10.getProducator(), m10.getSubstantaActiva());

}

void add_medicament_ui(Service& s) {
	cout << "Introduceti id-ul medicamentului: ";
	int id;
	cin >> id;
	cin.ignore(); //sare peste '\n'
	cout << "Introduceti denumirea medicamentului: ";
	string denumire;
	getline(cin, denumire);
	cout << "Introduceti pretul medicamentului: ";
	double pret;
	cin >> pret;
	cin.ignore();
	cout << "Introduceti producatorul medicamentului: ";
	string producator;
	getline(cin, producator);
	cout << "Introduceti substanta activa a medicamentului: ";
	string substantaActiva;
	getline(cin, substantaActiva);
	try {
		s.addMedicament(id, denumire, pret, producator, substantaActiva);
	}
	catch (const ValidationException& ex) {
		cout << ex.getErrorMessages() << endl;
	}
	catch (const RepoException& ex) {
		cout << ex.getMessage() << endl;
	}
}
void delete_medicament_ui(Service& s) {
	cout << "Introduceti id-ul medicamentului: ";
	int id;
	cin >> id;
	cin.ignore(); //sare peste '\n'
	try {
		s.deleteMedicamt(id);
	}
	catch (const RepoException& ex) {
		cout << ex.getMessage() << endl;
	}
}
void modify_med_ui(Service& s) {
	cout << "Introduceti id-ul medicamentului: ";
	int id;
	cin >> id;
	cin.ignore(); //sare peste '\n'
	cout << "Introduceti denumirea medicamentului: ";
	string denumire;
	getline(cin, denumire);
	cout << "Introduceti pretul medicamentului: ";
	double pret;
	cin >> pret;
	cin.ignore();
	cout << "Introduceti producatorul medicamentului: ";
	string producator;
	getline(cin, producator);
	cout << "Introduceti substanta activa a medicamentului: ";
	string substantaActiva;
	getline(cin, substantaActiva);
	try {
		s.updateMedicament(id, denumire, pret, producator, substantaActiva);
	}
	catch (const ValidationException& ex) {
		cout << ex.getErrorMessages() << endl;
	}
	catch (const RepoException& ex) {
		cout << ex.getMessage() << endl;
	}
}


void filter_ui(Service& s) {
	cout << "Introduceti pretul minim: ";
	double pretMin;
	cin >> pretMin;
	cin.ignore(); //sare peste '\n'
	cout << "Introduceti pretul maxim: ";
	double pretMax;
	cin >> pretMax;
	cin.ignore(); //sare peste '\n'
	try
	{
		s.filter_price(pretMin, pretMax);
	}
	catch (RepoException& ex) {
		cout << ex.getMessage() << endl;
	}
	
	
	

}


void sort_ui(Service& s) {
	cout << "Sortare dupa(p/s):\n";
	cout << "p - pret\n";
	cout << "s - substanta activa\n";
	string optiune;
	getline(cin, optiune);
	if (optiune != "p" && optiune != "s") {
		cout << "Optiune invalida!\n";
		return;
	}
	else if (optiune == "s") {
		cout << "Medicamentele sortate dupa substanta activa:\n";
		s.sort_by_substanta_activa();
	}
	else if (optiune == "p") {
		cout << "Medicamentele sortate dupa pret:\n";
		s.sort_by_price();
	}
	else
		cout << "Optiune invalida!\n";


}



void search_med_ui(Service& s) {
	cout << "Introduceti id-ul medicamentului: ";
	int id;
	cin >> id;
	cin.ignore(); //sare peste '\n'
	try {
		Medicament m = s.findMedicamentById(id);
		cout << m << endl;
	}
	catch (const RepoException& ex) {
		cout << ex.getMessage() << endl;
	}
	catch (const ValidationException& ex) {
		cout << ex.getErrorMessages() << endl;
	}
	
}

void static run() {
	testAll();
	Repo r;
	MedicamentValidation v = MedicamentValidation();
	Service s(r, v);
	add_10_meds(s);

	while (true) {
		printMenu();
		cout << ">>>";
		string input;
		getline(cin, input);  

		int opt;
		try {
			opt = stoi(input);  
		}
		catch (exception& e) {
			cout <<e.what()<< " trebuie sa introduci un intreg!\n";
			continue;
		}

		if (opt > 0 && opt < 9)
			switch (opt) {
			case 1: {
				afiseaza_medicamente(s.getAllMeds());
				break;
			}
			case 2: {
				add_medicament_ui(s);
				break;
			}
			case 3: {
				delete_medicament_ui(s);
				break;
			}
			case 4: {
				modify_med_ui(s);
				break;
			}
			case 5: {
				search_med_ui(s);
				break;
			}
			case 6: {
				filter_ui(s);
				break;
			}
			case 7: {
				sort_ui(s);
				break;
			}
			case 8: {
				cout << "Iesire...\n";
				return;
			}
			}
		else {
			cout << "Un intreg intre 1-8!\n";
			continue;
		}
	}
}


int main() {
	run();
	return 0;
}
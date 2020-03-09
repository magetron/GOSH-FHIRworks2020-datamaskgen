//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH

#include <vector>
#include <string>

#include <patient/patient.hh>
#include <generator/generator_random.hh>

using namespace std;

class masker {
public:
	vector<patient>& patients;

	explicit masker (vector<patient>& ps) : patients(ps) { }

	static bool is_number (char& c) {
		return c >= '0' && c <= '9';
	}

	vector<char> number_chars{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	void assign_number_with_weight (char& c) {
		random_selector<> selector;
		if (selector(number_chars) >= '8') c = selector(number_chars);
	}

	vector<patient>& mask () {
		for (auto& p : patients) {
			for (auto& a : p.addresses)
				for (auto& line : a.lines) for (auto &c : line) if (is_number(c)) assign_number_with_weight(c);
			for (auto& t : p.telecoms)
				for (auto& c : t.value) if (is_number(c)) assign_number_with_weight(c);
			for (auto& i : p.identifiers)
				for (auto& c : i.value) if (is_number(c)) assign_number_with_weight(c);
		}
		return patients;
	}

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH

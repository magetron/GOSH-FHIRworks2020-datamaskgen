//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_IDENTIFIER_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_IDENTIFIER_GENERATOR_HH

#include <vector>
#include <iostream>
#include <unordered_map>

#include "../patient/patient.hh"

using namespace std;

class identifier_generator {
public:
    vector<patient>& patients;
    vector<vector<identifier>> identifier_lib;

    explicit identifier_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) identifier_lib.push_back(patient.identifiers);
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_IDENTIFIER_GENERATOR_HH

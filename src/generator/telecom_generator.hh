//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../patient/patient.hh"

using namespace std;

class telecom_generator {
public:
    vector<patient>& patients;

    unordered_map<string, vector<telecom>> telecom_lib;

    telecom_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients)
            for (const auto& telecom : patient.telecoms)
                telecom_lib[telecom.use].push_back(telecom);
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH

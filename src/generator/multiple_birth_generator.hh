//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH

#include <unordered_map>
#include <vector>
#include <iostream>

#include "../patient/patient.hh"

using namespace std;

class multiple_birth_generator {
public:

    vector<patient>& patients;
    unordered_map<int, int> multiple_birth_lib;

    explicit multiple_birth_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            if (multiple_birth_lib.find(patient.multiple_birth_count) != multiple_birth_lib.end())
                multiple_birth_lib[patient.multiple_birth_count]++;
            else multiple_birth_lib.insert({patient.multiple_birth_count, 1});
        }
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH

//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH

#include <unordered_map>
#include <vector>
#include <iostream>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"

using namespace std;

class multiple_birth_generator {
public:

    vector<patient>& patients;
    unordered_map<int, int> multiple_birth_lib;
    generator_with_weight<int> m_birth_gen;

    explicit multiple_birth_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            if (multiple_birth_lib.find(patient.multiple_birth_count) != multiple_birth_lib.end())
                multiple_birth_lib[patient.multiple_birth_count]++;
            else multiple_birth_lib.insert({patient.multiple_birth_count, 1});
        }
        m_birth_gen = generator_with_weight<int>(multiple_birth_lib);
    }

    pair<bool, int> generate() {
        int m_birth_count = m_birth_gen.generate();
        if (m_birth_count > 1) return {true, m_birth_count};
        else return {false, m_birth_count};
    }
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_MULTIPLE_BIRTH_GENERATOR_HH

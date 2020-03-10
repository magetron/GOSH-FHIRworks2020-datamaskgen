//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_GENDER_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_GENDER_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"

using namespace std;

class gender_generator {
public:
    vector<patient>& patients;
    unordered_map<gender, int> gender_lib;
    generator_with_weight<gender> gw;

    explicit gender_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            if (gender_lib.find(patient.gender) != gender_lib.end())
                gender_lib[patient.gender]++;
            else gender_lib.insert({patient.gender, 1});
        }
        gw = generator_with_weight<gender>(gender_lib);
    }

    gender generate() {
        return gw.generate();
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_GENDER_GENERATOR_HH

//
// Created by Patrick Wu on 08/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_EXTENSION_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_EXTENSION_GENERATOR_HH

#include <patient/patient.hh>
#include "generator_random.hh"

using namespace std;

class extension_generator {
public:
    vector<patient>& patients;
    vector<string> extension_lib;

    explicit extension_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) extension_lib.push_back(patient.extensions);
    }

    string generate () {
        random_selector<> selector;
        return selector(extension_lib);
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_EXTENSION_GENERATOR_HH

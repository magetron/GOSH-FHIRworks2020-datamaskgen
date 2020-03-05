//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include "../patient/patient.hh"

using namespace std;

class address_generator {
public:
    vector<patient> patients;
    unordered_map<string, unordered_map<string, address>> address_library;

    explicit address_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            for (const auto& address : patient.addresses) {
                const string &ctry = address.country;
                const string &state = address.state;
                address_library[ctry][state] = address;
            }
        }
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_GENERATOR_HH

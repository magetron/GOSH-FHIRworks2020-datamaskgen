//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_ADDRESS_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_ADDRESS_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include "../patient/patient.hh"
#include "generator_with_weight.hh"
#include "generator_random.hh"

using namespace std;

class address_generator {
public:
    vector<patient> patients;
    unordered_map<string, unordered_map<string, vector<address>>> address_lib;
    unordered_map<string, int> country_lib;
    generator_with_weight<string> country_gen;

    explicit address_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            for (const auto& address : patient.addresses) {
                const string &ctry = address.country;
                const string &state = address.state;
                address_lib[ctry][state].push_back(address);
                if (country_lib.find(ctry) != country_lib.end()) country_lib[ctry]++;
                else country_lib.insert({ctry, 1});
            }
        }
        country_gen = generator_with_weight<string>(country_lib);
    }

    address generate() {
        string country = country_gen.generate();
        auto sub_lib = address_lib[country];
        unordered_map<string, int> state_lib;
        for (const auto& p : sub_lib)
            if (state_lib.find(p.first) != state_lib.end()) state_lib[p.first]++;
            else state_lib.insert({p.first, 1});
        generator_with_weight<string> state_gen(state_lib);
        string state = state_gen.generate();
        random_selector<> selector{};
        return selector(address_lib[country][state]);
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_ADDRESS_GENERATOR_HH

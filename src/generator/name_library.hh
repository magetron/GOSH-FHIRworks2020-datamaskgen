//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_LIBRARY_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_LIBRARY_HH

#include <vector>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"

using namespace std;

class name_library {
public:
    vector<patient>& patients;
    enum gender gender;
    unordered_map<string, int> given_name_lib;
    unordered_map<string, int> family_name_lib;
    unordered_map<string, int> prefix_lib;
    generator_with_weight<string> gn_gen;
    generator_with_weight<string> fn_gen;
    generator_with_weight<string> pre_gen;

    name_library (vector<patient>& p, enum gender g) : patients(p), gender(g) {
        for (auto patient : patients)
            if (patient.gender == gender) {
                string& gn = patient.name.given_name;
                if (given_name_lib.find(gn) != given_name_lib.end()) given_name_lib[gn]++;
                else given_name_lib.insert({gn, 1});
                string& fn = patient.name.family_name;
                if (family_name_lib.find(fn) != family_name_lib.end()) family_name_lib[fn]++;
                else family_name_lib.insert({fn, 1});
                if (!patient.name.prefix.empty()) {
                    string& pre = patient.name.prefix;
                    if (prefix_lib.find(pre) != prefix_lib.end()) prefix_lib[pre]++;
                    else prefix_lib.insert({pre, 1});
                }
            }
        gn_gen = generator_with_weight<string>(given_name_lib);
        fn_gen = generator_with_weight<string>(family_name_lib);
        pre_gen = generator_with_weight<string>(prefix_lib);
    }

    name generate() {
        return name(pre_gen.generate(), gn_gen.generate(), fn_gen.generate());
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_LIBRARY_HH

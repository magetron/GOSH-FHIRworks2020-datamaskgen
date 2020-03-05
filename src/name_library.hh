//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_NAME_LIBRARY_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_NAME_LIBRARY_HH

#include <vector>

#include "patient/patient.hh"

using namespace std;

class name_library {
public:
    vector<patient>& patients;
    enum gender gender;
    unordered_map<string, int> given_names;
    unordered_map<string, int> family_names;
    unordered_map<string, int> prefixs;

    name_library (vector<patient>& p, enum gender g) : patients(p), gender(g) {
        for (auto patient : patients)
            if (patient.gender == gender) {
                string& gn = patient.name.given_name;
                if (given_names.find(gn) != given_names.end()) given_names[gn]++;
                else given_names.insert({gn, 1});
                string& fn = patient.name.family_name;
                if (family_names.find(fn) != family_names.end()) family_names[fn]++;
                else family_names.insert({fn, 1});
                if (patient.name.prefix != "") {
                    string& pre = patient.name.prefix;
                    if (prefixs.find(pre) != prefixs.end()) prefixs[pre]++;
                    else prefixs.insert({pre, 1});
                }
            }
    }


};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_NAME_LIBRARY_HH

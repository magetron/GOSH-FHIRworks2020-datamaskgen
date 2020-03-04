//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH

#include <unordered_set>
#include <vector>
#include <string>

#include "patient/patient.hh"

using namespace std;

class masker {
public:
    unordered_set<patient> original_patients;
    vector<name> name;

    explicit masker (unordered_set<patient>& p) : original_patients(std::move(p)) {

    }



};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_MASKER_HH

//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH

#include <vector>
#include <string>

#include <patient/patient.hh>

using namespace std;

class filter {
    vector<patient>& patients;

    explicit filter (vector<patient>& p) : patients (p) { }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH

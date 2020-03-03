//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_DB_HH
#define GOSH_FHIRWORKS2020_DATAGEN_DB_HH

#include <unordered_set>
#include "patient/patient.hh"

using namespace std;

class db {
public:
    unordered_set<patient> patients;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_DB_HH

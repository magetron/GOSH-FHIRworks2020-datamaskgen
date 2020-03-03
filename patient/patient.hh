//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_PATIENT_HH
#define GOSH_FHIRWORKS2020_DATAGEN_PATIENT_HH

#include <string>
#include <ctime>

#include "name.hh"
#include "address.hh"

using namespace std;

class Patient {
public:
    Name name;
    string gender;
    tm birthday;
    Address address;
    string maritial_status;


};


#endif

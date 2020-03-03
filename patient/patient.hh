//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_PATIENT_HH
#define GOSH_FHIRWORKS2020_DATAGEN_PATIENT_HH

#include <string>
#include <ctime>
#include <set>

#include "name.hh"
#include "address.hh"
#include "language.hh"
#include "telecom.hh"
#include "identifier.hh"

//TODO: extensions

using namespace std;

class Patient {
public:
    Name name;
    string gender;
    tm birthday;
    Address address;
    string maritial_status;
    set<Language> communication_languages;
    set<Telecom> telecoms;
    set<Identifier> identifiers;
    string uuid;

};


#endif

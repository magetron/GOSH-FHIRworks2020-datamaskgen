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

class patient {
public:
    name name;
    string gender;
    tm birthday;
    address address;
    string marital_status;
    set<language> communication_languages;
    set<telecom> telecoms;
    set<identifier> identifiers;
    string uuid;

    patient (string id, string pre, string gn, string fn) : uuid(std::move(id)), name(std::move(pre), std::move(gn), std::move(fn)) { }
};


#endif

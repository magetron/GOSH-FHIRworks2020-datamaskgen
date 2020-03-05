//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_PATIENT_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_PATIENT_HH

#include <string>
#include <ctime>
#include <set>

#include "name.hh"
#include "address.hh"
#include "language.hh"
#include "telecom.hh"
#include "identifier.hh"
#include "gender.hh"
#include "marital_status.hh"

//TODO: extensions

using namespace std;

class patient {
public:

    bool operator == (const patient& p1) const {
        return uuid == p1.uuid;
    }

    name name;
    gender gender;
    tm birthday;
    vector<address> addresses;
    marital_status marital_status;
    vector<language> communication_languages;
    vector<telecom> telecoms;
    vector<identifier> identifiers;
    string uuid;
    bool multiple_birth = false;
    int multiple_birth_count = 1;

    patient (string id, string pre, string gn, string fn, string gen,
            bool mul_birth, int mul_birth_count, string bday) : uuid(std::move(id)),
        name(std::move(pre), std::move(gn), std::move(fn)), multiple_birth(mul_birth),
        multiple_birth_count(mul_birth_count) {
        if (gen == "male") gender = MALE;
        else if (gen == "female") gender = FEMALE;
        else gender = OTHER;
        strptime(bday.c_str(), "%Y-%m-%d", &birthday);
    }

};

namespace std {
    template<>
    struct hash<patient> {
        size_t operator() (const patient& p) const {
            return std::hash<string>()(p.uuid);
        }
    };
}


#endif

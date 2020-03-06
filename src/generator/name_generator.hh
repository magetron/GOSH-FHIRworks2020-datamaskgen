//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_NAME_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_NAME_GENERATOR_HH

#include <string>
#include <vector>

#include "name_library.hh"
#include "../patient/patient.hh"

using namespace std;

class name_generator {
public:
    vector<patient>& patients;
    name_library male_lib, female_lib, other_lib;

    explicit name_generator(vector<patient>& p) :
        patients(p), male_lib(p, MALE), female_lib(p, FEMALE), other_lib(p, OTHER) { }

    name generate (gender g) {
        switch (g) {
            case MALE:
                return male_lib.generate(); break;
            case FEMALE:
                return female_lib.generate(); break;
            default:
                return other_lib.generate(); break;
        }
    }


};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_NAME_GENERATOR_HH

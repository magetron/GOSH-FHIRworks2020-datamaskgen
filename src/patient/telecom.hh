//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_TELECOM_HH
#define GOSH_FHIRWORKS2020_DATAGEN_TELECOM_HH

#include <string>

using namespace std;

class telecom {
public:
    string system;
    string value;
    string use;

    telecom (string sys, string val, string u) : system(std::move(sys)), value(std::move(val)),
                                                 use(std::move(u)) { }

    ~telecom() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_TELECOM_HH

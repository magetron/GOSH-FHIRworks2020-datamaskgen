//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_ADDRESS_HH
#define GOSH_FHIRWORKS2020_DATAGEN_ADDRESS_HH

#include <string>
#include <optional>
#include "geolocation.hh"

using namespace std;

class address {
public:
    string country;
    string postal_code;
    string state;
    string city;
    Geolocation geolocation;

    address () = default;

    address (string ctry, string pc, string s, string c, double la, double lg) : country(std::move(ctry)),
                                                                                 postal_code(std::move(pc)), state(std::move(s)), city(std::move(c)), geolocation(la, lg) { }

    ~address() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_ADDRESS_HH

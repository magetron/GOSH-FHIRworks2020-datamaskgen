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
    vector<string> lines;
    optional<geolocation> geolocation;

    address () = default;

    address (string ctry, string pc, string s, string c) : country(std::move(ctry)),
                                                                                 postal_code(std::move(pc)),
                                                                                 state(std::move(s)),
                                                                                 city(std::move(c)) { }

    void add_line (string line) {
        lines.emplace_back(line);
    }

    void add_geolocation (double la, double lo) {
        geolocation.emplace(la, lo);
    }

    ~address() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_ADDRESS_HH

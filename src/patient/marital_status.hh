//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_MARITAL_STATUS_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_MARITAL_STATUS_HH

#include <vector>
#include <string>

#include "encoding.hh"

using namespace std;

class marital_status {
public:
    vector<encoding> encodings;
    string text;

    marital_status () = default;

    explicit marital_status (string t) : text(std::move(t)) { }

    void add_encoding (const string& system, const string& code, const string& display) {
        encodings.emplace_back(system, code, display);
    }

    ~marital_status() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_MARITAL_STATUS_HH

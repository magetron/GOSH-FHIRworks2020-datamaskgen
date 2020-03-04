//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH

#include <vector>

#include "encoding.hh"

class language {
public:
    vector<encoding> encodings;
    string text;

    explicit language (string t) : text(std::move(t)) { }

    void add_encoding (const string& system, const string& code, const string& display) {
        encodings.emplace_back(system, code, display);
    }

    ~language() = default;

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH

//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_HH
#define GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_HH

#include <string>
#include <optional>

#include "identifier_type.hh"

using namespace std;

class Identifier {
    string system;
    string value;
    optional<IdentifierType> type;

    Identifier (string sys, string val) : system(std::move(sys)), value(std::move(val)) { }

    void init_type(const string& text) {
        if (!type.has_value()) {
            type = IdentifierType(text);
        } else {
            type -> text = text;
        }
    }

    void add_type_encoding (const string& system, const string& code, const string& display) {
        type->encodings.emplace_back(sys, code, display);
    }

};


#endif //GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_HH

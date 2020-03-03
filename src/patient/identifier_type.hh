//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_TYPE_HH
#define GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_TYPE_HH

#include <vector>
#include <string>

#include "encoding.hh"

using namespace std;

class IdentifierType {
public:
    vector<encoding> encodings;
    string text;

    explicit IdentifierType (string t) : text(std::move(t)) { }

    ~IdentifierType() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_IDENTIFIER_TYPE_HH

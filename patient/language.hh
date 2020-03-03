//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_LANGUAGE_HH
#define GOSH_FHIRWORKS2020_DATAGEN_LANGUAGE_HH

#include <vector>

#include "encoding.hh"

class Language {
public:
    vector<Encoding> encodings;
    string text;

    Language (string t) : text(std::move(t)) { }

    ~Language() = default;
    
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_LANGUAGE_HH

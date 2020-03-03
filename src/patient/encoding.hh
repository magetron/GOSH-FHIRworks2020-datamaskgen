//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_ENCODING_HH
#define GOSH_FHIRWORKS2020_DATAGEN_ENCODING_HH

#include <string>

using namespace std;

class encoding {
public:
    string system;
    string code;
    string display;

    encoding (string sys, string c, string d) : system(std::move(sys)), code(std::move(c)), display(std::move(d)) { }

    ~encoding() = default;

};


#endif //GOSH_FHIRWORKS2020_DATAGEN_ENCODING_HH

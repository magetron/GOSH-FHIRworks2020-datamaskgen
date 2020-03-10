//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_TYPE_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_TYPE_HH

#include <vector>
#include <string>
#include <sstream>

#include "encoding.hh"

using namespace std;

class identifier_type {
public:
    vector<encoding> encodings;
    string text;

    explicit identifier_type (string t) : text(std::move(t)) { }

    string jsonify () {
        stringstream ss;
        ss << "\"type\":{\"coding\":[";
        for (size_t i = 0; i < encodings.size() - 1; i++) ss << encodings[i].jsonify() << ",";
        ss << encodings.back().jsonify() << "],\"text\":\"" << text << "\"}";
        return ss.str();
    }

    ~identifier_type() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_IDENTIFIER_TYPE_HH

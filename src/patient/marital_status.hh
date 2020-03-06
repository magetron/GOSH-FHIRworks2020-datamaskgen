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

    bool operator==(const marital_status &m1) const {
        return text == m1.text;
    }

    vector<encoding> encodings;
    string text;

    marital_status() = default;

    explicit marital_status(string t) : text(std::move(t)) {}

    void add_encoding(const string &system, const string &code, const string &display) {
        encodings.emplace_back(system, code, display);
    }

    friend ostream& operator << (ostream& os, const marital_status& m) {
        os << m.text;
        return os;
    }

    ~marital_status() = default;
};

namespace std {
    template<>
    struct hash<marital_status> {
        size_t operator() (const marital_status& m) const {
            return std::hash<string>()(m.text);
        }
    };
}

#endif //GOSH_FHIRWORKS2020_DATAMASKER_MARITAL_STATUS_HH

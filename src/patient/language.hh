//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH

#include <vector>

#include "encoding.hh"

class language {
public:

    bool operator==(const language& l1) const {
        return text == l1.text;
    }

    vector<encoding> encodings;
    string text;

    language () = default;

    explicit language (string t) : text(std::move(t)) { }

    void add_encoding (const string& system, const string& code, const string& display) {
        encodings.emplace_back(system, code, display);
    }

    friend ostream& operator << (ostream& os, const language& l) {
        os << l.text;
        return os;
    }

    ~language() = default;

};

namespace std {
    template<>
    struct hash<language> {
        size_t operator() (const language& l) const {
            return std::hash<string>()(l.text);
        }
    };
}


#endif //GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_HH

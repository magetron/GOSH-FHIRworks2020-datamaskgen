//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH

#include <iostream>
#include <unordered_map>

#include "../patient/patient.hh"

using namespace std;

class language_generator {
public:
    vector<patient> patients;
    unordered_map<language, int> language_lib;
    unordered_map<size_t, int> language_count_lib;

    explicit language_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            size_t language_count = patient.communication_languages.size();
            if (language_count_lib.find(language_count) != language_count_lib.end())
                language_count_lib[language_count]++;
            else language_count_lib.insert({language_count, 1});
            for (const auto& language : patient.communication_languages)
                if (language_lib.find(language) != language_lib.end()) language_lib[language]++;
                else language_lib.insert({language, 1});
        }
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH

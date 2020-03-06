//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH

#include <vector>
#include <iostream>
#include <unordered_map>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"

using namespace std;

class language_generator {
public:
    vector<patient>& patients;
    unordered_map<language, int> language_lib;
    unordered_map<size_t, int> language_count_lib;
    generator_with_weight<size_t> l_count_gen;

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
        l_count_gen = generator_with_weight<size_t>(language_count_lib);
    }

    vector<language> generate () {
        int l_count = l_count_gen.generate();
        vector<language> gen_languages;
        auto l_lib = language_lib;
        for (int i = 0; i < l_count; i++) {
            generator_with_weight<language> l_gen(l_lib);
            language new_l = l_gen.generate();
            gen_languages.emplace_back(new_l);
            l_lib.erase(new_l);
        }
        return gen_languages;
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_LANGUAGE_GENERATOR_HH

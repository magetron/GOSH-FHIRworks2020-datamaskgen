//
// Created by Patrick Wu on 06/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_BIRTHDAY_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_BIRTHDAY_GENERATOR_HH

#include <vector>
#include <iostream>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"
#include "generator_random.hh"

using namespace std;

class birthday_generator {
public:
    vector<patient>& patients;
    unordered_map<int, vector<tm>> bday_lib;
    unordered_map<int, int> byear_count_lib;
    generator_with_weight<int> byear_gen;

    explicit birthday_generator (vector<patient>& p) : patients(p) {
        for (const auto& patient : patients) {
            bday_lib[patient.birthday.tm_year].push_back(patient.birthday);
            if (byear_count_lib.find(patient.birthday.tm_year) != byear_count_lib.end())
                byear_count_lib[patient.birthday.tm_year]++;
            else byear_count_lib.insert({patient.birthday.tm_year , 1});
        }
        byear_gen = generator_with_weight<int>(byear_count_lib);
    }

    tm generate () {
        int byear = byear_gen.generate();
        random_selector<> selector;
        return selector(bday_lib[byear]);
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_BIRTHDAY_GENERATOR_HH

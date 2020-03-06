//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../patient/patient.hh"
#include "generator_with_weight.hh"
#include "generator_random.hh"

using namespace std;

class telecom_generator {
public:
    vector<patient>& patients;

    unordered_map<string, vector<telecom>> telecom_lib;
    unordered_map<string, int> telecom_use_lib;
    unordered_map<size_t, int> telecom_count_lib;
    generator_with_weight<size_t> telecom_count_gen;
    generator_with_weight<string> telecom_use_gen;

    explicit telecom_generator (vector<patient>& p) : patients(p) {
        for (const auto &patient : patients) {
            for (const auto &telecom : patient.telecoms) {
                telecom_lib[telecom.use].push_back(telecom);
                if (telecom_use_lib.find(telecom.use) != telecom_use_lib.end())
                    telecom_use_lib[telecom.use]++;
                else telecom_use_lib.insert({telecom.use, 1});
            }
            size_t c = patient.telecoms.size();
            if (telecom_count_lib.find(c) != telecom_count_lib.end())
                telecom_count_lib[c]++;
            else telecom_count_lib.insert({c, 1});
        }
        telecom_count_gen = generator_with_weight<size_t>(telecom_count_lib);
        telecom_use_gen = generator_with_weight<string>(telecom_use_lib);
    }

    vector<telecom> generate () {
        int c = telecom_count_gen.generate();
        vector<telecom> new_telecoms;
        unordered_map<string, int> sample_lib;
        for (int i = 0; i < c; i++) {
            string use = telecom_use_gen.generate();
            if (sample_lib.find(use) != sample_lib.end())
                sample_lib[use]++;
            else sample_lib.insert({use, 1});
        }
        for (const auto& s : sample_lib) {
            vector<telecom>& t_lib = telecom_lib[s.first];
            sample(t_lib.begin(), t_lib.end(), back_inserter(new_telecoms), s.second,
                    std::mt19937{std::random_device{}()});
        }
        return new_telecoms;
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_GENERATOR_HH

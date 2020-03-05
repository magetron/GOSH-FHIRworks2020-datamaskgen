//
// Created by Patrick Wu on 04/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH

#include <unordered_set>
#include <random>
#include <vector>
#include <string>

#include "../patient/patient.hh"
#include "name_generator.hh"
#include "address_generator.hh"
#include "marital_status_generator.hh"
#include "language_generator.hh"

using namespace std;

class generator {
public:
    vector<patient> original_patients;

    class name_generator name_generator;
    class address_generator address_generator;
    class marital_status_generator marital_status_generator;
    class language_generator language_generator;

    explicit generator (vector<patient>& p) : original_patients(std::move(p)),
                                              name_generator(original_patients),
                                              address_generator(original_patients),
                                              marital_status_generator(original_patients),
                                              language_generator(original_patients) { }

    static string get_uuid() {
        static random_device dev;
        static mt19937 rng(dev());

        uniform_int_distribution<int> dist(0, 15);

        const char *v = "0123456789abcdef";
        const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

        string res;
        for (int i = 0; i < 16; i++) {
            if (dash[i]) res += "-";
            res += v[dist(rng)];
            res += v[dist(rng)];
        }
        return res;
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_HH

//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH

#include <utility>
#include <vector>
#include <string>

#include <patient/patient.hh>

using namespace std;

class filter {
public:

    function<bool(patient)> judger;

    explicit filter (function<bool(patient)> f) : judger(std::move(f)) { }

    vector<patient> vec (vector<patient>& ps) {
        vector<patient> new_patients;
        for (const auto& p : ps)
            if (judger(p)) new_patients.push_back(p);
        return new_patients;
    }

};


#endif //GOSH_FHIRWORKS2020_DATAMASKER_FILTER_HH

//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_NAME_CC
#define GOSH_FHIRWORKS2020_DATAMASKER_NAME_CC

#include <string>
#include <utility>
#include <vector>

using namespace std;

class name {
public:
    vector<tuple<string, string, string>> unofficial_names; // prefix, given name, family name
    string given_name;
    string family_name;
    string prefix;

    name () = default;

    name (string pre, string gn, string fn) : prefix(std::move(pre)), given_name(move(gn)), family_name(move(fn)) { }

    void add_unofficial_name (const string& pre, const string& gn, const string& fn) {
        unofficial_names.emplace_back(pre, gn, fn);
    }

    ~name () = default;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_NAME_CC

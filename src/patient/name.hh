//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_CC
#define GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_CC

#include <string>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

class name {
public:

    bool operator == (const name& n1) const {
        return given_name == n1.given_name && family_name == n1.family_name && prefix == n1.prefix;
    }

    vector<tuple<string, string, string>> unofficial_names; // prefix, given name, family name
    string prefix;
    string given_name;
    string family_name;

    name () = default;

    name (string pre, string gn, string fn) : prefix(std::move(pre)), given_name(std::move(gn)), family_name(std::move(fn)) { }

    void add_unofficial_name (const string& pre, const string& gn, const string& fn) {
        unofficial_names.emplace_back(pre, gn, fn);
    }

    friend ostream& operator << (ostream& os, const name& n) {
        os << n.prefix << " " << n.given_name << " " << n.family_name;
        return os;
    }

    string jsonify () {
        std::stringstream ss;
        ss << "\"name\":[{\"use\":\"official\",\"family\":\"" << family_name << "\",\"given\":[\"" << given_name <<
            "\"],\"prefix\":[\"" << prefix << "\"]}";
        for (auto t : unofficial_names) {
            ss << ",{\"use\":\"unofficial\",\"family\":\"" << get<2>(t) << "\",\"given\":[\"" << get<1>(t) <<
            "\"],\"prefix\":[\"" << get<0>(t) << "\"]}";
        }
        ss << "]";
        return ss.str();
    }

    ~name () = default;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKGEN_NAME_CC

//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_HH

#include <string>
#include <sstream>

using namespace std;

class telecom {
public:
    string system;
    string value;
    string use;

    telecom (string sys, string val, string u) : system(std::move(sys)), value(std::move(val)),
                                                 use(std::move(u)) { }

    friend ostream& operator << (ostream& os, const telecom& t) {
        os << t.system << " " << t.value << " " << t.use;
        return os;
    }

    string jsonify () {
        stringstream ss;
        ss << "{\"system\":\"" << system << "\",\"value\":\"" << value << "\",\"use\":\"" << use <<"\"}";
        return ss.str();
    }

    ~telecom() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_TELECOM_HH

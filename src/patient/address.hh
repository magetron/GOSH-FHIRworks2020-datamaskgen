//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_HH

#include <string>
#include <optional>
#include <sstream>

#include "geolocation.hh"

using namespace std;

class address {
public:
    string country;
    string postal_code;
    string state;
    string city;
    vector<string> lines;
    optional<geolocation> geolocation;

    address () = default;

    address (string ctry, string pc, string s, string c) : country(std::move(ctry)),
                                                             postal_code(std::move(pc)),
                                                             state(std::move(s)),
                                                             city(std::move(c)) { }

    void add_line (string line) {
        lines.emplace_back(line);
    }

    void add_geolocation (double la, double lo) {
        geolocation.emplace(la, lo);
    }

    friend ostream& operator << (ostream& os, const address& a) {
        for (auto line : a.lines) os << line << endl;
        os << a.city << " " << a.state << " " << a.country << endl;
        os << a.postal_code << endl;
        if (a.geolocation.has_value())
            os << a.geolocation -> latitude << " " << a.geolocation->longitude << endl;
        return os;
    }

    ~address() = default;

    string jsonify () {
        stringstream ss;
        ss << "{" << (geolocation.has_value() ? geolocation->jsonify() : "") << ",\"url\":\"http://hl7.org/fhir/StructureDefinition/geolocation\"}],\"line\":[";
        for (size_t i = 0; i < lines.size() - 1; i++) ss << "\"" << lines[i] << "\",";
        ss << "\"" << lines.back() << "\"],\"city\":\"" << city << "\",\"state\":\"" << state << "\",\"postalCode\":\"" << postal_code << "\",\"country\":\"" << country << "\"}";
        return ss.str();
    }
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_ADDRESS_HH

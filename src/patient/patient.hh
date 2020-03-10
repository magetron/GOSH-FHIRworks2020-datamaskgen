//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_PATIENT_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_PATIENT_HH

#include <string>
#include <ctime>
#include <vector>
#include <sstream>

#include "name.hh"
#include "address.hh"
#include "language.hh"
#include "telecom.hh"
#include "identifier.hh"
#include "gender.hh"
#include "marital_status.hh"

using namespace std;

class patient {
public:

    static string generate_current_timestamp () {
        time_t now;
        time(&now);
        char buf[sizeof "YYYY-MM-DDThh:mm:ssZ"];
        strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
        return buf;
    }

    bool operator == (const patient& p1) const {
        return uuid == p1.uuid;
    }

    string uuid;
    name name;
    gender gender;
    tm birthday;
    string extensions;
    vector<address> addresses;
    marital_status marital_status;
    vector<language> communication_languages;
    vector<telecom> telecoms;
    vector<identifier> identifiers;
    bool multiple_birth = false;
    int multiple_birth_count = 1;

    patient (string id, string pre, string gn, string fn, string gen,
            bool mul_birth, int mul_birth_count, string bday) : uuid(std::move(id)),
        name(std::move(pre), std::move(gn), std::move(fn)), multiple_birth(mul_birth),
        multiple_birth_count(mul_birth_count) {
        if (gen == "male") gender = MALE;
        else if (gen == "female") gender = FEMALE;
        else gender = OTHER;
        strptime(bday.c_str(), "%Y-%m-%d", &birthday);
    }

    patient (class name n, enum gender g, tm bday, vector<address> addrs, class marital_status m_status,
            vector<language> c_langs, vector<telecom> ts, vector<identifier> is, string exs, string uid,
            bool m_birth, int m_birth_count)
            : uuid(std::move(uid)), name(std::move(n)), gender(std::move(g)), birthday(std::move(bday)),
              addresses(std::move(addrs)), marital_status(std::move(m_status)),
              communication_languages(std::move(c_langs)), telecoms(std::move(ts)),
              identifiers(std::move(is)), extensions(exs), multiple_birth(m_birth),
              multiple_birth_count(m_birth_count) { }

    string jsonify () {
        stringstream ss;
        ss << R"({"fullUrl":"","resource":{"resourceType":"Patient","id":")" << uuid << "\",";
        ss << R"("meta":{"versionId":"4","lastUpdated":")" << generate_current_timestamp() << "\"},";
        ss << R"("text":{"status":"generated","div":""},)";
        ss << R"("extension":)" << extensions << ",";
        ss << "\"identifier\":[";
        for (size_t i = 0; i < identifiers.size() - 1; i++) ss << identifiers[i].jsonify() << ","; ss << identifiers.back().jsonify() << "],";
        ss << name.jsonify() << ",";
        ss << "\"telecom\":[";
        for (size_t i = 0; i < telecoms.size() - 1; i++) ss << telecoms[i].jsonify() << ","; ss << telecoms.back().jsonify() << "],";
        ss << "\"gender\":\"";
        switch (gender) {
            case MALE:
                ss << "male";
                break;
            case FEMALE:
                ss << "female";
                break;
            default:
                ss << "other";
                break;
        } ss << "\",";
        ss << "\"birthDate\":\"" << birthday.tm_year + 1900 << "-" << birthday.tm_mon << "-" << birthday.tm_mday << "\",";
        ss << "\"address\":[";
        for (size_t i = 0; i < addresses.size() - 1; i++) ss << addresses[i].jsonify() << ","; ss << addresses.back().jsonify() << "],";
        ss << marital_status.jsonify() << ",";
        if (!multiple_birth) ss << "\"multipleBirthBoolean\":" << multiple_birth << ",";
        else ss << "\"multipleBirthInteger\":" << multiple_birth_count << ",";
        ss << "\"communication\":[";
        for (size_t i = 0; i < communication_languages.size() - 1; i++) ss << communication_languages[i].jsonify() << ","; ss << communication_languages.back().jsonify() << "]";
        ss << "}}";
        return ss.str();
    }

};

namespace std {
    template<>
    struct hash<patient> {
        size_t operator() (const patient& p) const {
            return std::hash<string>()(p.uuid);
        }
    };
}


#endif

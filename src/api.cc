//
// Created by Patrick Wu on 02/03/2020.
//
#ifndef GOSH_FHIRWORKS2020_DATAGEN_API_CC
#define GOSH_FHIRWORKS2020_DATAGEN_API_CC
#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <nlohmann/json.hpp>

#include "api.hh"
#include "db.hh"

using namespace std;
using json = nlohmann::json;

class api {
public:
    static pair<string, bool> refresh_patients_json() {
        auto request = cpr::Get(cpr::Url{"https://localhost:5001/api/Patient"}, cpr::VerifySsl(false));
        if (request.status_code != 200) return {"", false};
        ofstream patients_json;
        patients_json.open(CACHE_FOLDER + "patients.json");
        patients_json.clear();
        try {
            auto parser = nlohmann::json::parse(request.text);
            patients_json << parser.dump();
        } catch (const exception &e) {
            return {"", false};
        }
        patients_json.close();
        return {request.text, true};
    }

    static pair<string, bool> read_patients_json() {
        ifstream patients_json;
        patients_json.open(CACHE_FOLDER + "patients.json");
        if (!patients_json) return {"", false};
        stringstream patients_json_stream;
        patients_json_stream << patients_json.rdbuf();
        patients_json.close();
        return {patients_json_stream.str(), true};
    }

    static unordered_set<patient> parse_raw_patients(string &json_string) {
        unordered_set<patient> patients;
        auto json = json::parse(json_string);
        for (auto & it : json) {
            auto entries = it["entry"];
            for (auto &eit : entries) {
                auto resources = eit["resource"];
                string id = resources["id"];
                auto name_json = resources["name"];
                auto telecom_json = resources["telecom"];
                auto address_json = resources["address"];
                auto identifier_json = resources["identifier"];
                string gender = resources["gender"];
                string birth_date = resources["birthDate"];
                auto marital_status_json = resources["maritalStatus"];
                bool multiple_birth;
                int multiple_birth_count;
                if (resources.contains("multipleBirthBoolean")) {
                    multiple_birth = resources["multipleBirthBoolean"];
                    multiple_birth_count = 1;
                } else {
                    multiple_birth = true;
                    multiple_birth_count = resources["multipleBirthInteger"];
                }
                auto communication_languages_json = resources["communication"];
                string pre, gn, fn;
                for (auto& nit : name_json) {
                    auto name_entry_json = nit;
                    if (name_entry_json["use"] == "official") {
                        if (name_entry_json.contains("prefix")) pre = name_entry_json["prefix"][0],
                        gn = name_entry_json["given"][0],
                        fn = name_entry_json["family"];
                    }
                }
                patient new_patient(id, pre, gn, fn, gender, multiple_birth, multiple_birth_count, birth_date);
                for (auto& nit: name_json) {
                    auto name_entry_json = nit;
                    if (name_entry_json["use"] != "official") {
                        string pre = name_entry_json["prefix"][0];
                        string gn = name_entry_json["given"][0];
                        string fn = name_entry_json["family"];
                        new_patient.name.add_unofficial_name(pre, gn, fn);
                    }
                }
                for (auto& identifier : identifier_json) {
                    string system = identifier["system"];
                    string value = identifier["value"];
                    class identifier new_identifier(system, value);
                    if (identifier.contains("type")) {
                        auto text = identifier["type"]["text"];
                        new_identifier.init_type(text);
                        auto codings = identifier["type"]["coding"];
                        for (auto& coding : codings)
                            new_identifier.add_type_encoding(coding["system"],
                                    coding["code"],
                                    coding["display"]);
                    }
                    new_patient.identifiers.emplace_back(new_identifier);
                }
                for (auto& telecom : telecom_json) {
                    string system = telecom["system"];
                    string value = telecom["value"];
                    string use = telecom["use"];
                    class telecom new_telecom(system, value, use);
                    new_patient.telecoms.emplace_back(new_telecom);
                }
                for (auto& address : address_json) {
                    string city = address["city"];
                    string state = address["state"];
                    string postal_code;
                    if (address.contains("postalCode")) postal_code = address["postalCode"];
                    string country = address["country"];
                    class address new_address(country, postal_code, state, city);
                    if (address.contains("extension")) {
                        double latitude = address["extension"][0]["extension"][0]["valueDecimal"];
                        double longitude = address["extension"][0]["extension"][1]["valueDecimal"];
                        new_address.add_geolocation(latitude, longitude);
                    }
                    auto lines = address["line"];
                    for (auto& line : lines) new_address.add_line(line);
                }
                patients.emplace(new_patient);
            }
        }
        return patients;
    }
};


#endif
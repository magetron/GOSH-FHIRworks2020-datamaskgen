//
// Created by Patrick Wu on 02/03/2020.
//
#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_API_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_API_HH

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include "../patient/patient.hh"

using namespace std;
using json = nlohmann::json;

class api {
public:
    static pair<string, bool> refresh_patients_json(const string& endpoint, const string& cache_loc) {
        auto request = cpr::Get(cpr::Url{endpoint}, cpr::VerifySsl(false));
        if (request.status_code != 200) return {"", false};
        std::filesystem::create_directories(cache_loc);
        ofstream patients_json;
        patients_json.open(cache_loc + "patients.json");
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

    static pair<string, bool> read_patients_json(const string& cache_loc) {
        ifstream patients_json;
        patients_json.open(cache_loc + "patients.json");
        if (!patients_json) return {"", false};
        stringstream patients_json_stream;
        patients_json_stream << patients_json.rdbuf();
        patients_json.close();
        return {patients_json_stream.str(), true};
    }

    static vector<patient> parse_raw_patients_from_endpoint(string& json_string) {
        vector<patient> patients;
        auto json = json::parse(json_string);
        for (auto & it : json) {
            auto entries = it["entry"];
            for (auto &eit : entries) {
                auto resources = eit["resource"];
                string id = resources["id"];
                auto name_json = resources["name"];
                auto telecom_json = resources["telecom"];
                auto address_json = resources["address"];
                auto extension_json = resources["extension"];
                auto identifier_json = resources["identifier"];
                string gender = resources["gender"];
                string birth_date = resources["birthDate"];
                auto marital_status_json = resources["maritalStatus"];
                auto communication_languages_json = resources["communication"];
                bool multiple_birth;
                int multiple_birth_count;
                if (resources.contains("multipleBirthBoolean")) {
                    multiple_birth = resources["multipleBirthBoolean"];
                    multiple_birth_count = 1;
                } else {
                    multiple_birth = true;
                    multiple_birth_count = resources["multipleBirthInteger"];
                }
                string pre, gn, fn;
                for (const auto& nit : name_json) {
                    auto name_entry_json = nit;
                    if (name_entry_json["use"] == "official") {
                        if (name_entry_json.contains("prefix")) pre = name_entry_json["prefix"][0];
                        gn = name_entry_json["given"][0],
                        fn = name_entry_json["family"];
                    }
                }

                patient new_patient(id, pre, gn, fn, gender, multiple_birth, multiple_birth_count, birth_date);
                for (const auto& nit: name_json) {
                    auto name_entry_json = nit;
                    if (name_entry_json["use"] != "official") {
                        string pre = name_entry_json["prefix"][0];
                        string gn = name_entry_json["given"][0];
                        string fn = name_entry_json["family"];
                        new_patient.name.add_unofficial_name(pre, gn, fn);
                    }
                }

                new_patient.extensions = extension_json.dump();

                for (const auto& identifier : identifier_json) {
                    string system = identifier["system"];
                    string value = identifier["value"];
                    class identifier new_identifier(system, value);
                    if (identifier.contains("type")) {
                        auto text = identifier["type"]["text"];
                        new_identifier.init_type(text);
                        auto codings = identifier["type"]["coding"];
                        for (const auto& coding : codings)
                            new_identifier.add_type_encoding(coding["system"],
                                    coding["code"],
                                    coding["display"]);
                    }
                    new_patient.identifiers.emplace_back(new_identifier);
                }
                for (const auto& telecom : telecom_json) {
                    string system = telecom["system"];
                    string value = telecom["value"];
                    string use = telecom["use"];
                    class telecom new_telecom(system, value, use);
                    new_patient.telecoms.emplace_back(new_telecom);
                }
                for (const auto& address : address_json) {
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
                    for (const auto& line : lines) new_address.add_line(line);
                    new_patient.addresses.emplace_back(new_address);
                }
                string m_text = marital_status_json["text"];
                marital_status m_status(m_text);
                if (marital_status_json.contains("coding")) {
                    auto m_codings = marital_status_json["coding"];
                    for (const auto& m_coding : m_codings) {
                        string system = m_coding["system"];
                        string code = m_coding["code"];
                        string display = m_coding["display"];
                        m_status.add_encoding(system, code, display);
                    }
                }
                new_patient.marital_status = m_status;
                for (const auto& language_json : communication_languages_json) {
                    auto language = language_json["language"];
                    string text = language["text"];
                    class language new_language(text);
                    auto codings = language["coding"];
                    for (const auto &coding : codings) {
                        string system = coding["system"];
                        string code = coding["code"];
                        string display = coding["display"];
                        new_language.add_encoding(system, code, display);
                    }
                    new_patient.communication_languages.emplace_back(new_language);
                }
                patients.emplace_back(new_patient);
            }
        }
        return patients;
    }

    static bool write_to_file (stringstream& ss, const string& output_loc) {
        std::filesystem::create_directories(output_loc);
        ofstream os;
        os.open(output_loc + "patients.json");
        os.clear();
        os << ss.rdbuf();
        os.close();
        return true;
    }

};


#endif
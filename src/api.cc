//
// Created by Patrick Wu on 02/03/2020.
//
#ifndef GOSH_FHIRWORKS2020_DATAGEN_API_CC
#define GOSH_FHIRWORKS2020_DATAGEN_API_CC
#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "api.hh"

using namespace std;

static pair<string, bool> refresh_patients_json () {
    auto request = cpr::Get(cpr::Url{"https://localhost:5001/api/patient"}, cpr::VerifySsl(false));
    if (request.status_code != 200) return {"", false};
    ofstream patients_json;
    patients_json.open(CACHE_FOLDER + "patients.json");
    patients_json.clear();
    try {
        auto parser = nlohmann::json::parse(request.text);
        patients_json << parser.dump();
    } catch (const exception& e) {
        return {"", false};
    }
    patients_json.close();
    return {request.text, true};
}

static pair<string, bool> read_patients_json () {
    ifstream  patients_json;
    patients_json.open(CACHE_FOLDER + "patients.json");
    if (!patients_json) return {"", false};
    stringstream patients_json_stream;
    patients_json_stream << patients_json.rdbuf();
    patients_json.close();
    return {patients_json_stream.str(), true};
}

#endif
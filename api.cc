//
// Created by Patrick Wu on 02/03/2020.
//
#ifndef GOSHDRIVE_FHIRWORKS_API
#define GOSHDRIVE_FHIRWORKS_API
#include <cpr/cpr.h>
#include <iostream>
#include <fstream>

using namespace std;

const string CACHE_FOLDER("/Users/patrick/Documents/University-College-London/UCL-CS/Year-2/COMP0016/FHIR-Hackathon/GOSH-FHIRworks2020-datagen/cache/");

static bool refresh_patients_json () {
    auto request = cpr::Get(cpr::Url{"https://localhost:5001/api/Patient"}, cpr::VerifySsl(false));
    if (request.status_code != 200) return false;
    ofstream patients_json;
    patients_json.open(CACHE_FOLDER + "patients.json");
    patients_json << request.text;
    patients_json.close();
    return true;
}

#endif
//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_CONFIG_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_CONFIG_HH

#include <string>

using namespace std;

static string CACHE_FOLDER("/Users/patrick/Documents/University-College-London/UCL-CS/Year-2/COMP0016/FHIR-Hackathon/GOSH-FHIRworks2020-datamasker/cache/");

static string PATIENTS_JSON_API_ENDPOINT("https://localhost:5001/api/Patient");

static size_t PATIENTS_GENERATED = 1000;

static string OUTPUT_FOLDER("/Users/patrick/Documents/University-College-London/UCL-CS/Year-2/COMP0016/FHIR-Hackathon/GOSH-FHIRworks2020-datamasker/output/");

static bool VERBOSE = false;

static bool USE_CACHE = false;

static bool MASK = false;

#endif

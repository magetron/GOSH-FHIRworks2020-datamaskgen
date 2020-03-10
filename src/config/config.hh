//
// Created by Patrick Wu on 02/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKGEN_CONFIG_HH
#define GOSH_FHIRWORKS2020_DATAMASKGEN_CONFIG_HH

#include <string>

using namespace std;

static string CACHE_FOLDER("./cache/");

static string PATIENTS_JSON_API_ENDPOINT("https://localhost:5001/api/Patient");

static size_t PATIENTS_GENERATED = 1000;

static string OUTPUT_FOLDER("./");

static bool VERBOSE = true;

static bool USE_CACHE = false;

static bool MASK = false;

#endif

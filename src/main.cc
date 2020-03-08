//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <argh.h>
#include <spdlog/spdlog.h>

#include "generator/generator.hh"
#include "api/api.hh"
#include "config/config.hh"
#include "cli/cli.hh"

using namespace std;
using json = nlohmann::json;

static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

void generate_patient_and_log (generator& g, stringstream& ss, bool log) {
    auto p = g.generate_patient();
    ss << p.jsonify();
    if (log) spdlog::info("new patient UUID = {}", p.uuid);
}

int main(int argc, char** argv) {

    argh::parser cmdl(argc, argv);

    if (!cmdl(1)) {
        spdlog::info("using default config");
        spdlog::info("\tCACHE_FOLDER_LOCATION = {}", CACHE_FOLDER);
        spdlog::info("\tAPI_ENDPOINT = {}", PATIENTS_JSON_API_ENDPOINT);
        spdlog::info("\tPATIENTS_GENERATED = {}", PATIENTS_GENERATED);
        spdlog::info("\tOUTPUT_FOLDER_LOCATION = {}", OUTPUT_FOLDER);
        spdlog::info("downloading...");
        auto result = api::refresh_patients_json(PATIENTS_JSON_API_ENDPOINT, CACHE_FOLDER);
        if (!result.second) spdlog::error("failed.");
        auto ps = api::parse_raw_patients_from_endpoint(result.first);
        spdlog::info("configuring generator...");
        generator g(ps);
        stringstream ss;
        ss << "\"patients\":[";
        for (size_t i = 0; i < PATIENTS_GENERATED - 1; i++) {
            spdlog::info("[{}%] generating in progress ...", i * 1.0 / PATIENTS_GENERATED * 100.0);
            generate_patient_and_log(g, ss, true);
            ss << ",";
        }
        spdlog::info("[{}%] generating in progress ...", 100.0);
        generate_patient_and_log(g, ss, true);
        api::write_to_file(ss, OUTPUT_FOLDER);
    }

    if (cmdl[{ "-v", "--verbose" }])
        std::cout << "Verbose, I am.\n";

    return 0;
}

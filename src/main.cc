//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <argh.h>
#include <spdlog/spdlog.h>
#include <tabulate/table.hpp>

#include "generator/generator.hh"
#include "masker/masker.hh"
#include "api/api.hh"
#include "config/config.hh"
#include "cli/cli.hh"

using namespace std;
using json = nlohmann::json;
using namespace tabulate;

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

    argh::parser cmdl;
    cmdl.add_params({"--cache-loc", "--api", "-g", "-o"});
    cmdl.parse(argc, argv);

    if (cmdl[{"--about"}]) {
        Table readme;
        readme.format().border_color(Color::white);

        readme.add_row({"GOSH FHIRworks 2020 Data Masker - Generator"});
        readme[0].format().font_align(FontAlign::center).font_color(Color::blue);

        readme.add_row({"https://github.com/magetron/GOSH-FHIRworks2020-datamasker"});
        readme[1]
                .format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::underline, FontStyle::italic})
                .font_color(Color::white)
                .hide_border_top();

        readme.add_row({"A data synthesizer and masker that takes in real FHIR patient data and generate data providing certain rules.\n "
                        "This tool is developed with performance and customisation in mind. See [TODO: UPDATES] on how to customise with custom data modules."});
        readme[2].format().font_style({FontStyle::italic}).font_color(Color::magenta);

        Table highlights;
        highlights.add_row({"Build: passing", "Requires C++17", "Apache-2.0 License"});
        readme.add_row({highlights});
        readme[3].format().font_align(FontAlign::center).hide_border_top();
        cout << readme << endl;
        return 0;
    }


    if (cmdl[{ "-v", "--verbose" }]) VERBOSE = true;
    if (cmdl["--use-cache"]) USE_CACHE = true;
    if (cmdl["--mask"]) MASK = true;
    if (!cmdl("--cache-loc").str().empty()) CACHE_FOLDER = cmdl( "--cache-loc").str();
    if (!cmdl("--api").str().empty()) PATIENTS_JSON_API_ENDPOINT = cmdl("--api").str();
    if (!cmdl("-g").str().empty()) cmdl("-g") >> PATIENTS_GENERATED;
    if (!cmdl("-o").str().empty()) OUTPUT_FOLDER = cmdl("-o").str();

    spdlog::info("using following config");
    spdlog::info("\tCACHE_FOLDER_LOCATION = {}", CACHE_FOLDER);
    spdlog::info("\tAPI_ENDPOINT = {}", USE_CACHE ? "USING CACHE" : PATIENTS_JSON_API_ENDPOINT );
    spdlog::info("\tPATIENTS_GENERATED = {}", PATIENTS_GENERATED);
    spdlog::info("\tOUTPUT_FOLDER_LOCATION = {}", OUTPUT_FOLDER);
    spdlog::info("\tMASKING = {}", MASK);
    spdlog::info("downloading / reading from cache...");
    pair<string, bool> result;
    if (!USE_CACHE) result = api::refresh_patients_json(PATIENTS_JSON_API_ENDPOINT, CACHE_FOLDER);
    else result = api::read_patients_json(CACHE_FOLDER);
    if (!result.second) spdlog::error("failed.");
    auto ps = api::parse_raw_patients_from_endpoint(result.first);
    if (MASK) {
        masker m(ps);
        ps = m.mask();
    }
    spdlog::info("configuring generator...");
    generator g(ps);
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < PATIENTS_GENERATED - 1; i++) {
        spdlog::info("[{}%] generating in progress ...", roundf(i * 1.0 / PATIENTS_GENERATED * 100.0 * 100) / 100);
        generate_patient_and_log(g, ss, VERBOSE);
        ss << ",";
    }
    spdlog::info("[{}%] generating in progress ...", 100.0);
    generate_patient_and_log(g, ss, VERBOSE);
    ss << "]";
    api::write_to_file(ss, OUTPUT_FOLDER);
    spdlog::info("{} patients generated, writing output json to {}", PATIENTS_GENERATED, OUTPUT_FOLDER + "patients.json");

    return 0;
}

//
// Created by Patrick Wu on 08/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_CLI_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_CLI_HH

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <argh.h>
#include <spdlog/spdlog.h>
#include <tabulate/table.hpp>

#include <generator/generator.hh>
#include <masker/masker.hh>
#include <api/api.hh>
#include <config/config.hh>

using namespace std;
using json = nlohmann::json;
using namespace tabulate;

class cli {
public:
    static string generate_patient_and_log (generator& g, stringstream& ss) {
        auto p = g.generate_patient();
        ss << p.jsonify();
        return p.uuid;
    }

    static int run (int argc, char** argv) {
        argh::parser cmdl;
        cmdl.add_params({"--cache-loc", "--api", "-g", "-o"});
        cmdl.parse(argc, argv);

        Table readme;
        readme.format().border_color(Color::white);
        readme.add_row({"GOSH FHIRworks 2020 Data Masker - Generator"});
        readme[0].format().font_align(FontAlign::center).font_color(Color::blue);
        readme.add_row({"https://github.com/magetron/GOSH-FHIRworks2020-datamasker"});
        readme[1].format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::underline, FontStyle::italic})
                .font_color(Color::white)
                .hide_border_top();
        readme.add_row({"A data synthesizer and masker that takes in real FHIR patient data and generate data providing certain rules.\n "
                        "This tool is developed with performance and customisation in mind. See [TODO: UPDATES] on how to customise with custom data modules."});
        readme[2].format().font_style({FontStyle::italic}).font_color(Color::magenta);
        Table highlights;
        highlights.add_row({"Build: passing", "C++17", "Apache-2.0 License"});
        readme.add_row({highlights});
        readme[3].format().font_align(FontAlign::center).hide_border_top().font_color(Color::yellow);
        cout << readme << endl;

        if (cmdl[{"--about"}]) return 0;
        if (cmdl["--use-cache"]) USE_CACHE = true;
        if (cmdl["--mask"]) MASK = true;
        if (cmdl["--quiet"]) VERBOSE = false;
        if (!cmdl("--cache-loc").str().empty()) CACHE_FOLDER = cmdl( "--cache-loc").str();
        if (!cmdl("--api").str().empty()) PATIENTS_JSON_API_ENDPOINT = cmdl("--api").str();
        if (!cmdl("-g").str().empty()) cmdl("-g") >> PATIENTS_GENERATED;
        if (!cmdl("-o").str().empty()) OUTPUT_FOLDER = cmdl("-o").str();

        if (VERBOSE) {
            Table generate_info;
            generate_info.format().border_color(Color::white);
            generate_info.add_row({"CONFIG"});
            Table config;
            config.add_row({"CACHE_FOLDER_LOCATION = ", CACHE_FOLDER});
            config.add_row({"API_ENDPOINT = ", USE_CACHE ? "USING CACHE" : PATIENTS_JSON_API_ENDPOINT});
            config.add_row({"PATIENTS_GENERATED = ", to_string(PATIENTS_GENERATED)});
            config.add_row({"OUTPUT_FOLDER_LOCATION = ", OUTPUT_FOLDER});
            config.add_row({"MASKING = ", MASK ? "ON" : "OFF"});
            generate_info.add_row({config});
            generate_info[1].format().font_color(Color::yellow);
            cout << generate_info << endl;
        }

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
            auto id = generate_patient_and_log(g, ss);
            if (VERBOSE) spdlog::info("[{}%] generating in progress ... {}", roundf(i * 1.0 / PATIENTS_GENERATED * 100.0 * 100) / 100, id);
            ss << ",";
        }
        auto id = generate_patient_and_log(g, ss);
        if (VERBOSE) spdlog::info("[{}%] generating in progress ... {}", 100.0, id);
        ss << "]";
        api::write_to_file(ss, OUTPUT_FOLDER);
        spdlog::info("{} patients generated, writing output json to {}", PATIENTS_GENERATED, OUTPUT_FOLDER + "patients.json");

        if (VERBOSE) {
            spdlog::info("SUMMARY generated below at time {}", patient::generate_current_timestamp());
            Table summary;
            summary.format().border_color(Color::white);
            summary.add_row({"SUMMARY", "WARNING", "SUMMARY", "WARNING"});
            summary[0].format().color(Color::green);
            Table name_summary;
            name_summary.add_row({"NAME generator", "VALUE"});
            name_summary.add_row({"MALE prefix types = ", to_string(g.name_generator.male_lib.prefix_lib.size())});
            name_summary.add_row({"MALE given name types = ", to_string(g.name_generator.male_lib.given_name_lib.size())});
            name_summary.add_row({"MALE family name types = ", to_string(g.name_generator.male_lib.family_name_lib.size())});
            name_summary.add_row({"FEMALE prefix types = ", to_string(g.name_generator.female_lib.prefix_lib.size())});
            name_summary.add_row({"FEMALE given name types = ", to_string(g.name_generator.female_lib.given_name_lib.size())});
            name_summary.add_row({"FEMALE family name types = ", to_string(g.name_generator.female_lib.family_name_lib.size())});
            name_summary.add_row({"OTHER prefix types = ", to_string(g.name_generator.other_lib.prefix_lib.size())});
            name_summary.add_row({"OTHER given name types = ", to_string(g.name_generator.other_lib.given_name_lib.size())});
            name_summary.add_row({"OTHER family name types = ", to_string(g.name_generator.other_lib.family_name_lib.size())});
            Table gender_summary;
            gender_summary.add_row({"GENDER generator", "VALUE"});
            gender_summary.add_row({"GENDER types = ", to_string(g.gender_generator.gender_lib.size())});
            gender_summary.add_row({"MALE weight = ", to_string(g.gender_generator.gender_lib[MALE] * 1.0 / ps.size())});
            gender_summary.add_row({"FEMALE weight = ", to_string(g.gender_generator.gender_lib[FEMALE] * 1.0 / ps.size())});
            gender_summary.add_row({"OTHER weight = ", to_string(g.gender_generator.gender_lib[OTHER] * 1.0 / ps.size())});
            summary.add_row({name_summary, "WARNING: INPUT DIVERSITY", gender_summary, "PASS"});
            summary[1][0].format().color(Color::yellow); summary[1][1].format().color(Color::yellow);
            summary[1][2].format().color(Color::green); summary[1][3].format().color(Color::green);
            Table multiple_birth_summary;
            multiple_birth_summary.add_row({"MULTIPLE BIRTH generator", "VALUE"});
            for (auto& p : g.multiple_birth_generator.multiple_birth_lib)
                multiple_birth_summary.add_row({to_string(p.first) + " children weight = ", to_string(p.second * 1.0 / ps.size())});
            Table address_summary;
            address_summary.add_row({"ADDRESS generator", "VALUE"});
            for (auto& p : g.address_generator.country_lib)
                address_summary.add_row({p.first + " weight = ", to_string(p.second * 1.0 / ps.size())});
            summary.add_row({multiple_birth_summary, "PASS", address_summary, "WARNING: INPUT DIVERSITY"});
            summary[2][0].format().color(Color::green);  summary[2][1].format().color(Color::green);
            summary[2][2].format().color(Color::yellow);  summary[2][3].format().color(Color::yellow);
            Table marital_status_summary;
            marital_status_summary.add_row({"MARTIAL generator", "VALUE"});
            for (auto& p : g.marital_status_generator.marital_lib)
                marital_status_summary.add_row({p.first.encodings.front().display + " weight = ", to_string(p.second * 1.0 / ps.size())});
            Table language_summary;
            language_summary.add_row({"LANGUAGE generator", "VALUE"});
            for (auto& p : g.language_generator.language_lib)
                language_summary.add_row({p.first.encodings.front().display + " weight = ", to_string(p.second * 1.0 / ps.size())});
            summary.add_row({marital_status_summary, "PASS", language_summary, "PASS"});
            summary[3][0].format().color(Color::green);  summary[3][1].format().color(Color::green);
            summary[3][2].format().color(Color::green);  summary[3][3].format().color(Color::green);
            cout << summary << endl;
        }
        return 0;
    }
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_CLI_HH

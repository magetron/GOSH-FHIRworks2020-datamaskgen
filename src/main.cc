//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <argh.h>
#include <spdlog/spdlog.h>

#include "generator/generator.hh"
#include "api/api.hh"
#include "config/config.hh"

using namespace std;
using json = nlohmann::json;

static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

int main(int argc, char** argv) {

    argh::parser cmdl(argc, argv);

    if (!cmdl(1)) {
        spdlog::info("DEFAULT CONFIG");
        spdlog::info("API_ENDPOINT = {}", PATIENTS_JSON_API_ENDPOINT);
        spdlog::info("CACHE_FOLDER_LOCATION = {}", CACHE_FOLDER);

    }

    if (cmdl[{ "-v", "--verbose" }])
        std::cout << "Verbose, I am.\n";

    return 0;
}

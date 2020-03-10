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

#include <generator/generator.hh>
#include <masker/masker.hh>
#include <api/api.hh>
#include <config/config.hh>
#include <cli/cli.hh>

using namespace std;
using namespace std;
using json = nlohmann::json;
using namespace tabulate;


static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

int main(int argc, char** argv) {
    cli::run(argc, argv);
    return 0;
}

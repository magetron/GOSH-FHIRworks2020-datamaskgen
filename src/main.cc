//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <unordered_set>
#include "api.cc"
#include "nlohmann/json.hpp"

using namespace std;


using json = nlohmann::json;

static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

void parse_raw_patients (string& json_string) {
    auto json = nlohmann::json::parse(json_string);
    for (auto it = json.begin(); it != json.end(); it++) {
        auto entries = (*it)["entry"];
        for (auto eit = entries.begin(); eit != entries.end(); eit++) {
            auto resources = (*it)["resource"];
        }
    }
}


int main(int argc, char** argv) {

    refresh_patients_json();
    string patients_json_string = read_patients_json().first;
    cout << patients_json_string << endl;
    auto data = json::parse(patients_json_string);
    cout << data.dump(4) << endl;

    return 0;
}

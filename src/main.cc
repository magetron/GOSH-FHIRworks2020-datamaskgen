//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <unordered_set>
#include <nlohmann/json.hpp>

#include "generator/generator.hh"
#include "api/api.hh"

using namespace std;
using json = nlohmann::json;

static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

int main(int argc, char** argv) {

    auto result = api::refresh_patients_json();
    string str = result.first;
    bool suc = result.second;
    cout << suc << endl;
    string patients_json_string = api::read_patients_json().first;
    //cout << patients_json_string << endl;
    //auto data = json::parse(patients_json_string);
    //cout << data.dump(4) << endl;

    auto patients = api::parse_raw_patients(patients_json_string);

    generator g(patients);
    for (int i = 0; i < 1000; i++) {
        auto p = g.generate_patient();
        cout << p.name << " " << p.marital_status << " " << p.multiple_birth << " " << p.multiple_birth_count << endl;
    }

    return 0;
}

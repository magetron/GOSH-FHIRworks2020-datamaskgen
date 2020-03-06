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

    //refresh_patients_json();
    string patients_json_string = api::read_patients_json().first;
    //cout << patients_json_string << endl;
    //auto data = json::parse(patients_json_string);
    //cout << data.dump(4) << endl;

    auto patients = api::parse_raw_patients(patients_json_string);

    generator g(patients);
    for (auto gg : g.gender_generator.gender_lib) cout << gg.first << " " << gg.second << endl;
    int a_count = 0, b_count = 0;
    for (int i = 0; i < 100000; i++) {
        int k = (int)g.generate_patient();
        if (k == 0) a_count ++; else b_count++;
    }
    cout << a_count << " " << b_count << endl;

    return 0;
}

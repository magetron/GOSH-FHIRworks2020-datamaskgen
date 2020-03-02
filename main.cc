//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include "api.cc"
#include "nlohmann/json.hpp"

static int fast_io = [] () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
} ();

using namespace std;

int main(int argc, char** argv) {
    refresh_patients_json();
    string patients_json_string = read_patients_json().first;
    cout << patients_json_string << endl;
    auto parser = nlohmann::json::parse(patients_json_string);
    cout << parser.dump(4) << endl;
    return 0;
}

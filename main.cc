//
// Created by Patrick Wu on 02/03/2020.
//

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "api.cc"

using namespace std;

int main(int argc, char** argv) {
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    auto json = nlohmann::json::parse(response.text);
    cout << json.dump(4) << endl;
    refresh_patients_json();
    return 0;
}

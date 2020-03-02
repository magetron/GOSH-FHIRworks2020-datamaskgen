#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;

int main(int argc, char** argv) {
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    auto json = nlohmann::json::parse(response.text);
    cout << json.dump(4) << endl;
    return 0;
}

#include <iostream>
#include <cpr/cpr.h>

using namespace std;

int main(int argc, char** argv) {
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    cout << response.text << endl;
}

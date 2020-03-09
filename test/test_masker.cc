//
// Created by Patrick Wu on 09/03/2020.
//

#include <catch2/catch.hpp>
#include <masker/masker.hh>
#include <api/api.hh>

#include "test_config.hh"

using namespace std;

TEST_CASE("masking patient data should work", "[masker]") {

    auto patients_str =
            api::refresh_patients_json(TEST_ENDPOINT, TEST_CACHE_LOC).first;
    auto patients = api::parse_raw_patients_from_endpoint(patients_str);
    auto one_patient_vector = vector<patient>{patients[0]};

    SECTION("masked data should be different from real patient data") {
        masker m(one_patient_vector);
        auto vec_p = m.mask();
        REQUIRE(vec_p.size() == 1);
        auto p = vec_p.front();
        REQUIRE(p.name == patients.front().name);
        REQUIRE(((p.telecoms != patients.front().telecoms) || (p.addresses != patients.front().addresses)));
    }
}

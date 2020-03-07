//
// Created by Patrick Wu on 06/03/2020.
//

#include <catch2/catch.hpp>
#include <generator/generator.hh>
#include <api/api.hh>

#include "test_config.hh"

using namespace std;

TEST_CASE("static generation of uuid should meet standards", "[generator][uuid]") {
    string uuid_sample = generator::generate_uuid();

    SECTION("uuid should be 36 in length") {
        REQUIRE(generator::generate_uuid().length() == 36);
    }

    SECTION("uuid should be in range [0..f] or '-'") {
        for (auto c : uuid_sample)
            REQUIRE(((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c == '-')));
    }

}

TEST_CASE("generate patient should work", "[generator]") {

    auto patients_str =
            api::refresh_patients_json(TEST_ENDPOINT, TEST_CACHE_LOC).first;
    auto patients = api::parse_raw_patients(patients_str);
    auto one_patient_vector = vector<patient>{patients[0]};

    SECTION("generation of patient should be based on real data") {
        generator g(one_patient_vector);
        auto p = g.generate_patient();
        REQUIRE(p.name == one_patient_vector.front().name);
    }

}

//
// Created by Patrick Wu on 06/03/2020.
//

#include <catch2/catch.hpp>
#include <generator/generator.hh>
#include <api/api.hh>

TEST_CASE("generate uuid should be 16 in length","[generator]") {
    REQUIRE(generator::generate_uuid().length() == 36);
}

TEST_CASE("API should read from cache", "[api]") {
    auto result = api::read_patients_json();
    REQUIRE(result.second == true);
    //REQUIRE_NOTHROW(api::parse_raw_patients(result));
}
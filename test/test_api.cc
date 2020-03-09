//
// Created by Patrick Wu on 06/03/2020.
//

#include <catch2/catch.hpp>
#include <api/api.hh>

#include "test_config.hh"

using namespace std;

TEST_CASE("API should download and read data", "[api]") {

    SECTION("API should download data correctly") {
        auto download_result = api::refresh_patients_json(TEST_ENDPOINT, TEST_CACHE_LOC);
        REQUIRE(download_result.second);
        auto read_result = api::read_patients_json(TEST_CACHE_LOC);
        REQUIRE(read_result.second);
        auto parse_download = nlohmann::json::parse(download_result.first);
        auto parse_read = nlohmann::json::parse(read_result.first);
        REQUIRE(parse_download.dump() == parse_read.dump());
    }

    SECTION("API should parse patient data correctly") {
        auto read_result = api::read_patients_json(TEST_CACHE_LOC);
        REQUIRE(read_result.second);
        REQUIRE_NOTHROW(api::parse_raw_patients_from_endpoint(read_result.first));
    }
}


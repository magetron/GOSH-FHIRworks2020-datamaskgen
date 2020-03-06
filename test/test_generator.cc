//
// Created by Patrick Wu on 06/03/2020.
//

#include <catch2/catch.hpp>
#include <generator/generator.hh>

TEST_CASE("generate uuid should be 16 in length","[generator]") {
    REQUIRE(generator::generate_uuid().length() == 36);
}

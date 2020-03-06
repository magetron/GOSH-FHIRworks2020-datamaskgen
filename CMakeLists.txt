cmake_minimum_required(VERSION 3.12)
project(GOSH_FHIRworks2020_datamasker)

set(CMAKE_CXX_STANDARD 17)
set(OPENSSL_ROOT_DIR /usr/local/ssl)
set(OPENSSL_LIBRARIES /usr/local/ssl/lib)

add_subdirectory(dependencies)
add_subdirectory(src)

include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS} ${CATCH2_INCLUDE_DIRS} ${SOURCE_DIRS})

add_executable(GOSH_FHIRworks2020_datamasker src/main.cc src/api/api.hh src/api/api_config.hh
        src/patient/patient.hh src/patient/name.hh src/patient/address.hh src/patient/geolocation.hh
        src/patient/language.hh
        src/patient/encoding.hh src/patient/telecom.hh src/patient/identifier.hh src/patient/identifier_type.hh
        src/patient/marital_status.hh src/patient/gender.hh src/generator/generator.hh src/generator/name_library.hh
        src/generator/address_generator.hh src/generator/name_generator.hh src/generator/marital_status_generator.hh
        src/generator/language_generator.hh src/generator/telecom_generator.hh src/generator/identifier_generator.hh
        src/generator/multiple_birth_generator.hh src/masker/masker.hh src/filter/filter.hh
        src/generator/gender_generator.hh src/generator/generator_with_weight.hh
        src/generator/generator_random.hh src/generator/birthday_generator.hh)
target_link_libraries(GOSH_FHIRworks2020_datamasker ${CPR_LIBRARIES})


add_executable(GOSH_FHIRworks2020_datamasker_test test/test_main.cc test/generator/test_generator.cc)
target_link_libraries(GOSH_FHIRworks2020_datamasker_test Catch2::Catch2 ${CPR_LIBRARIES})


cmake_minimum_required(VERSION 3.15)
project(GOSH_FHIRworks2020_datagen)

set(CMAKE_CXX_STANDARD 17)
set(OPENSSL_ROOT_DIR /usr/local/ssl)
set(OPENSSL_LIBRARIES /usr/local/ssl/lib)

add_subdirectory(dependencies)

add_executable(GOSH_FHIRworks2020_datagen main.cc api.cc api.hh
        patient/patient.hh patient/name.hh patient/address.hh patient/geolocation.hh patient/language.hh
        patient/encoding.hh patient/telecom.hh patient/identifier.hh patient/identifier_type.hh)

include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
target_link_libraries(GOSH_FHIRworks2020_datagen ${CPR_LIBRARIES})
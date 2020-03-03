cmake_minimum_required(VERSION 3.15)
project(GOSH_FHIRworks2020_datagen)

set(CMAKE_CXX_STANDARD 17)
set(OPENSSL_ROOT_DIR /usr/local/ssl)
set(OPENSSL_LIBRARIES /usr/local/ssl/lib)

add_subdirectory(dependencies)

add_executable(GOSH_FHIRworks2020_datagen src/db.hh src/main.cc src/api.cc src/api.hh
        src/patient/patient.hh src/patient/name.hh src/patient/address.hh src/patient/geolocation.hh
        src/patient/language.hh
        src/patient/encoding.hh src/patient/telecom.hh src/patient/identifier.hh src/patient/identifier_type.hh
        src/patient/marital_status.hh src/patient/gender.hh )

include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
target_link_libraries(GOSH_FHIRworks2020_datagen ${CPR_LIBRARIES})
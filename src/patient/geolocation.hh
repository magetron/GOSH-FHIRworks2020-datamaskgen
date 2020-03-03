//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH
#define GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH

#include <string>

class geolocation {
public:
    double latitude, longitude;

    geolocation () = default;

    geolocation (double la, double lo) : latitude(la), longitude(lo) { }

    ~geolocation() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH

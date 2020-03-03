//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH
#define GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH

#include <string>

class Geolocation {
public:
    double latitude, longitude;

    Geolocation () = default;

    Geolocation (double la, double lo) : latitude(la), longitude(lo) { }

    ~Geolocation() = default;
};

#endif //GOSH_FHIRWORKS2020_DATAGEN_GEOLOCATION_HH

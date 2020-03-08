//
// Created by Patrick Wu on 03/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_GEOLOCATION_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_GEOLOCATION_HH

#include <string>
#include <sstream>

class geolocation {
public:
    double latitude, longitude;

    geolocation () = default;

    geolocation (double la, double lo) : latitude(la), longitude(lo) { }

    ~geolocation() = default;

    string jsonify () {
        stringstream ss;
        ss << "\"extension\":[{\"extension\":[{\"url\":\"latitude\",\"valueDecimal\":" << latitude << "},{\"url\":\"longitude\",\"valueDecimal\":" << longitude << "}]";
        return ss.str();
    }
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_GEOLOCATION_HH

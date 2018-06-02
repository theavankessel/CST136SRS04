#ifndef location_h
#define location_h

#include "gps.h"
#include "latitude.h"
#include "longitude.h"

namespace GPS
{
    class Location
    {
    private:
        const std::string name_;
        const Latitude latitude_;
        const Longitude longitude_;
        
    public:
        Location(const std::string name, const Latitude latitude, const Longitude longitude);
        Latitude getLatitude() const;
        Longitude getLongitude() const;
        std::string getName() const;
    };
}

#endif 

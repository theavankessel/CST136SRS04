#include <iostream>
#include "location.h"

GPS::Location::Location(const std::string name, const Latitude latitude, const Longitude longitude) : name_{name}, latitude_{latitude}, longitude_{longitude}
{
    
}

GPS::Latitude GPS::Location::getLatitude() const
{
    return latitude_;
}

GPS::Longitude GPS::Location::getLongitude() const
{
    return longitude_;
}

std::string GPS::Location::getName() const
{
    return name_;
}

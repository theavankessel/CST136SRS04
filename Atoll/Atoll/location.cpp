#include <iostream>
#include "location.h"

GPS::Location::Location(const std::string name, const Latitude latitude, const Longitude longitude) : name_{name}, latitude_{latitude}, longitude_{longitude}
{
    
}

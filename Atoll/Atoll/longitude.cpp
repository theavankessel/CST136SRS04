#include <iostream>
#include "longitude.h"

GPS::Longitude::Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) : Angle<-180, 180>((cardinal == Cardinal::W) ? -degree.getValue() : degree, minute, second)
{
    
}



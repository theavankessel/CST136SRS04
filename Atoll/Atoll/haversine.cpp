#include <math.h>
#include "haversine.h"

double haversine(double latitude1, double latitude2, double longitude1, double longitude2)
{
    double distance{0.0};
    double radius{6373.0};
    double dlat{latitude2 - latitude1};
    double dlon{longitude2 - longitude1};
    double a{pow(sin(dlat/2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(dlon/2), 2) };
    double c{ 2 * atan2( sqrt(a), sqrt(1-a) )};
  
    //distance = 2 * radius * asin(sqrt(pow(sin(lat / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(lng / 2), 2)));
    distance = radius * c;
    
    return distance;
}

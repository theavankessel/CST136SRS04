#include <math.h>
#include "haversine.h"

double haversine(double latitude1, double latitude2, double longitude1, double longitude2)
{
    return 2 * 6378 * asin(sqrt(pow(sin((latitude2 - latitude1) / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin((longitude2 - longitude1) / 2), 2)));
}

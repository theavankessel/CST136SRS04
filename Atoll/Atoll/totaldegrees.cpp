#include <iostream>
#include "totaldegrees.h"

double totalDegrees(double deg, double min, double sec)
{
    return deg + (min/60) + (sec/3600);
}

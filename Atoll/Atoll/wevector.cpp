#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "wevector.h"
#include "location.h"
#include "totaldegrees.h"
#include "degreetoradian.h"
#include "haversine.h"

double weVector(const std::array<GPS::Location, 12> island)
{
    double result{0.0};
    
    const auto iter {island.cbegin()};
    const auto end {island.cend()};
    std::vector<std::reference_wrapper<const GPS::Location>> islandList(iter, end);
    
    std::vector<double> distance;

    auto compareLocations
    {
        [ ](const GPS::Location locationA, const GPS::Location locationB)
        {
            double locationALong = locationA.getLongitude().getDegree().getValue();
            double locationBLong = locationB.getLongitude().getDegree().getValue();
            
            if(locationALong < 0)
            {
                locationALong += 360;
            }
            if(locationBLong < 0)
            {
                locationBLong += 360;
            }
            
            if(locationALong == locationBLong)
            {
                if(locationA.getLongitude().getMinute().getValue() == locationB.getLongitude().getMinute().getValue())
                {
                    return locationA.getLongitude().getSecond().getValue() < locationB.getLongitude().getSecond().getValue();
                }
                return locationA.getLongitude().getMinute().getValue() < locationB.getLongitude().getMinute().getValue();
            }
            
            return locationALong < locationBLong;
        }
    };
    
    std::sort(islandList.begin(), islandList.end(), compareLocations);

    auto current{islandList.cbegin()};
    auto previous{current};
     
    const auto endIter{islandList.cend()};
     
    while (current != endIter)
    {
     
        auto currLatDegree{totalDegrees(current->get().getLatitude().getDegree().getValue(), current->get().getLatitude().getMinute().getValue(), current->get().getLatitude().getSecond().getValue())};
        auto currLongDegree{totalDegrees(current->get().getLongitude().getDegree().getValue(), current->get().getLongitude().getMinute().getValue(), current->get().getLongitude().getSecond().getValue())};
        auto prevLatDegree{totalDegrees(previous->get().getLatitude().getDegree().getValue(), previous->get().getLatitude().getMinute().getValue(), previous->get().getLatitude().getSecond().getValue())};
        auto prevLongDegree{totalDegrees(previous->get().getLongitude().getDegree().getValue(), previous->get().getLongitude().getMinute().getValue(), previous->get().getLongitude().getSecond().getValue())};
        distance.push_back(haversine(degreeToRadian(prevLatDegree), degreeToRadian(currLatDegree), degreeToRadian(prevLongDegree), degreeToRadian(currLongDegree)));

        previous = current;
        ++current;
    }
     
    return std::accumulate(distance.begin(), distance.end(), 0.0);
}


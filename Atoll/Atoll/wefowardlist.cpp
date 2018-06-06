#include <iostream>
#include <array>
#include <forward_list>
#include <vector>
#include <numeric>
#include "location.h"
#include "snforwardlist.h"
#include "haversine.h"
#include "degreetoradian.h"
#include "totaldegrees.h"

double weForwardList(const std::array<GPS::Location, 12> island)
{
    std::vector<double> distance;
    
    std::forward_list<GPS::Location> islandList(island.begin(), island.end());
    
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
    
    islandList.sort(compareLocations);
    
    auto current{islandList.cbegin()};
    auto previous{current};
    const auto end{islandList.cend()};
    
    while (current != end)
    {
        auto currLatDegree{totalDegrees(current->getLatitude().getDegree().getValue(), current->getLatitude().getMinute().getValue(), current->getLatitude().getSecond().getValue())};
        auto currLongDegree{totalDegrees(current->getLongitude().getDegree().getValue(), current->getLongitude().getMinute().getValue(), current->getLongitude().getSecond().getValue())};
        auto prevLatDegree{totalDegrees(previous->getLatitude().getDegree().getValue(), previous->getLatitude().getMinute().getValue(), previous->getLatitude().getSecond().getValue())};
        auto prevLongDegree{totalDegrees(previous->getLongitude().getDegree().getValue(), previous->getLongitude().getMinute().getValue(), previous->getLongitude().getSecond().getValue())};
        distance.push_back(haversine(degreeToRadian(prevLatDegree), degreeToRadian(currLatDegree), degreeToRadian(prevLongDegree), degreeToRadian(currLongDegree)));
        //std::cout << current->getLongitude().getDegree().getValue() << std::endl;
        previous = current;
        ++current;
    }
    
    return std::accumulate(distance.begin(), distance.end(), 0.0);
}

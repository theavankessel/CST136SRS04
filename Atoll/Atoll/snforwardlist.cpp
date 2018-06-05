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

// TODO: Minutes and Seconds need to be negative for South
double snForwardList(const std::array<GPS::Location, 12> island)
{
    std::vector<double> distance;
    
    std::forward_list<GPS::Location> islandList(island.begin(), island.end());
    
    auto compareLocations
    {
        [ ](const GPS::Location locationA, const GPS::Location locationB)
        {
            if(locationA.getLatitude().getDegree().getValue() == locationB.getLatitude().getDegree().getValue())
            {
                if(locationA.getLatitude().getMinute().getValue() == locationB.getLatitude().getMinute().getValue())
                {
                    return locationA.getLatitude().getSecond().getValue() < locationB.getLatitude().getSecond().getValue();
                }
                return locationA.getLatitude().getMinute().getValue() < locationB.getLatitude().getMinute().getValue();
            }
            
            return locationA.getLatitude().getDegree().getValue() < locationB.getLatitude().getDegree().getValue();
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
        previous = current;
        ++current;
    }

    return std::accumulate(distance.begin(), distance.end(), 0.0);
}





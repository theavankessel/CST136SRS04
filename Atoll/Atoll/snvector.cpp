#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "snvector.h"
#include "location.h"
#include "totaldegrees.h"
#include "degreetoradian.h"
#include "haversine.h"

double snVector(const std::array<GPS::Location, 12> island)
{
    //const std::array<GPS::Location, 12>::const_iterator
    const auto iter {island.cbegin()};
    const auto end {island.cend()};
    std::vector<std::reference_wrapper<const GPS::Location>> islandList(iter, end);
    
    /*
    std::array<GPS::Location, 12>::const_iterator iter {island.cbegin()};
    const std::array<GPS::Location, 12>::const_iterator end {island.cend()};
    std::vector<std::reference_wrapper<const GPS::Location>> islandList;
    while(iter != end)
    {
        const GPS::Location& location = *iter;
        islandList.push_back(location);
    }
     */
    
    std::vector<double> distance;
    
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
    
    std::sort(islandList.begin(), islandList.end(), compareLocations);
    
    auto current{islandList.cbegin()};
    auto previous{current};
    
    const auto endIter{islandList.cend()};
    
    while (current != endIter)
    {
        std::cout << current->get().getName() << std::endl;
        
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

#include <iostream>
#include <array>
#include <map>
#include <string>
#include <vector>
#include <numeric>
#include "wemap.h"
#include "location.h"
#include "totaldegrees.h"
#include "degreetoradian.h"
#include "haversine.h"

double weMap(const std::array<GPS::Location, 12> island)
{
    std::vector<double> distance;
    std::map<double, GPS::Location> islandList;
    
    for(auto& i: island)
    {
        if(i.getLongitude().getDegree().getValue() < 0)
        {
            islandList.insert(std::pair<double, GPS::Location>(totalDegrees(i.getLongitude().getDegree().getValue() + 360, i.getLongitude().getMinute().getValue(), i.getLongitude().getSecond().getValue()), i));
        } else {
            islandList.insert(std::pair<double, GPS::Location>(totalDegrees(i.getLongitude().getDegree().getValue(), i.getLongitude().getMinute().getValue(), i.getLongitude().getSecond().getValue()), i));
        }
    }
    
    auto current{islandList.cbegin()};
    auto previous{current};
    const auto end{islandList.cend()};
    
    while (current != end)
    {
        auto currLatDegree{totalDegrees(current->second.getLatitude().getDegree().getValue(), current->second.getLatitude().getMinute().getValue(), current->second.getLatitude().getSecond().getValue())};
        auto prevLatDegree{totalDegrees(previous->second.getLatitude().getDegree().getValue(), previous->second.getLatitude().getMinute().getValue(), previous->second.getLatitude().getSecond().getValue())};
        
        distance.push_back(haversine(degreeToRadian(prevLatDegree), degreeToRadian(currLatDegree), degreeToRadian(previous->first), degreeToRadian(current->first)));
        
        previous = current;
        ++current;
    }
    
    return std::accumulate(distance.begin(), distance.end(), 0.0);
}

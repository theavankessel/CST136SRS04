#include <iostream>
#include <array>
#include <map>
#include <string>
#include <vector>
#include <numeric>
#include "snmap.h"
#include "location.h"
#include "totaldegrees.h"
#include "degreetoradian.h"
#include "haversine.h"

double snMap(const std::array<GPS::Location, 12> island)
{
    std::vector<double> distance;
    std::map<double, GPS::Location> islandList;

    for(auto& i: island)
    {
        islandList.insert(std::pair<double, GPS::Location>(totalDegrees(i.getLatitude().getDegree().getValue(), i.getLatitude().getMinute().getValue(), i.getLatitude().getSecond().getValue()), i));
    }
    
    auto current{islandList.cbegin()};
    auto previous{current};
    const auto end{islandList.cend()};
    
    while (current != end)
    {
        auto currLongDegree{totalDegrees(current->second.getLongitude().getDegree().getValue(), current->second.getLongitude().getMinute().getValue(), current->second.getLongitude().getSecond().getValue())};
        auto prevLongDegree{totalDegrees(previous->second.getLongitude().getDegree().getValue(), previous->second.getLongitude().getMinute().getValue(), previous->second.getLongitude().getSecond().getValue())};
        
        distance.push_back(haversine(degreeToRadian(previous->first), degreeToRadian(current->first), degreeToRadian(prevLongDegree), degreeToRadian(currLongDegree)));
        
        previous = current;
        ++current;
    }

    return std::accumulate(distance.begin(), distance.end(), 0.0);
}














#include <iostream>
#include <array>
#include <forward_list>
#include <vector>
#include <numeric>
#include "location.h"
#include "snforwardlist.h"
#include "haversine.h"
#include "degreetoradian.h"

// TODO: Minutes and Seconds need to be negative for South
double snForwardList(const std::array<GPS::Location, 12> island)
{
    auto result = 0.0;
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
    
    // d + m/60 + s/3600
    auto current{islandList.cbegin()};
    auto previous{current};
    const auto end{islandList.cend()};
    
    while (current != end)
    {
        // TODO: get longitude values to radians as well. Make this cleaner
        double deg = current->getLatitude().getDegree().getValue();
        double min = current->getLatitude().getMinute().getValue();
        double sec = current->getLatitude().getSecond().getValue();
        double currDegree = deg + (min/60) + (sec/3600);
        double deg2 = previous->getLatitude().getDegree().getValue();
        double min2 = previous->getLatitude().getMinute().getValue();
        double sec2 = previous->getLatitude().getSecond().getValue();
        double prevDegree = deg2 + (min2/60) + (sec2/3600);

        double currRadian = degreeToRadian(currDegree);
        double prevRadian = degreeToRadian(prevDegree);

        
        previous = current;
        ++current;
    }
    //double sum = std::accumulate(distance.begin(), distance.end(), 0.0);
   // std::cout << "The sum is: " << sum;
    
    return result;
}





#include "TrafficSimulate.h"
#include "MapUtil.h"
#include <iostream>
#include <thread>


namespace ADSB {

void TrafficSimulate::getIntermediatePoints(LngLat coord1, LngLat coord2, std::vector<LngLat>& vCoords) {
    prec_t bearing = calculateBearing(coord1, coord2);
    double dist = distanceBetweenTwoPoints(coord1, coord2) * 1000; // In meter
    int cntPoints = dist / interval;

    vCoords.push_back(coord1);
    float counter = interval;

    for (int i = 0; i < cntPoints; i++) {
        LngLat coord = getDestinationLatLong(coord1, bearing, counter);
        counter = counter + interval;
        vCoords.emplace_back(coord);
    }
    vCoords.push_back(coord2);
}

void TrafficSimulate::fly(TrafficDataWriter& smWriter) {
    
    Position *ptrPrev = nullptr;
    long time_in_millisec = getTimeInMilliSec(interval, traffic.groundSpeed);
    // std::cout << "\nTime : " << time_in_millisec;

    for(Position& position : traffic.path) {
        
        Aircraft acft;
        acft.AircraftID = traffic.AircraftID;
        // acft.position = position;
        if (ptrPrev) {
            std::vector<LngLat> intervalPts;
            getIntermediatePoints(ptrPrev->coord, position.coord, intervalPts);
            for (auto point : intervalPts) {

                acft.position.coord = point;
                acft.heading = calculateBearing(ptrPrev->coord, position.coord);
                acft.groundSpeed = traffic.groundSpeed;
                acft.position.altitude = position.altitude;

                // std::cout << "Lat : " << point.latitude << ", Lon : " << point.longitude 
                // << ", Alt : " << acft.position.altitude << ", Id : " << acft.AircraftID << ", Heading : " << acft.heading << std::endl;
                
                // handle.setValue(offset, (uint8_t*) &acft, sizeof(acft));
                smWriter.writeTrafficData(acft, idx);
                std::this_thread::sleep_for(std::chrono::milliseconds(time_in_millisec));
            }
        }
        ptrPrev = &position;
    }
    std::cout << "\nFinished Id : " << traffic.AircraftID;
}

}
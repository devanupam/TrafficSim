
#pragma once

#include "traffic.h"
#include "TrafficDataWriter.h"

namespace ADSB {

    class TrafficSimulate
    {
    private:
        Traffic traffic;
        uint8_t idx;

    public:
        static constexpr int interval = 1;
        TrafficSimulate() = delete;

        TrafficSimulate(Traffic _traffic, int _idx) : 
                        traffic(_traffic), idx(_idx) {}

        void getIntermediatePoints(LngLat coord1, LngLat coord2, std::vector<LngLat>& vCoords);

        void fly(TrafficDataWriter& smWriter);

    };
}



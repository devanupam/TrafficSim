
#pragma once

#include "TrafficDataReader.h"
#include "TrafficDataWriter.h"

namespace ADSB {

class TrafficMgr
{
private:
    /* data */
public:
    TrafficMgr(/* args */);
    void init();
    void runSimulation();
    ~TrafficMgr();
};


}

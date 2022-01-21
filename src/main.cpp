#include "TrafficDataReader.h"
#include "TrafficDataWriter.h"
#include "TrafficSimulate.h"
#include <thread>
#include <iostream>

using namespace ADSB;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Please provide flight plan filepath.";
        exit(1);
    }

    std::vector<Traffic> trafficData;
    TrafficDataReader reader(argv[1], trafficData);

    TrafficDataWriter smWriter("ADSBAircraftData");

    smWriter.writeTrafficCount(trafficData.size());
    
    std::vector<std::thread> simThreads;
    for(auto idx = 0; idx < trafficData.size(); idx++) {
        TrafficSimulate objTrfcSim (trafficData[idx], idx);
        simThreads.emplace_back(&TrafficSimulate::fly, std::move(objTrfcSim), std::ref(smWriter));
    }

    for(auto& simThrd : simThreads) simThrd.join();
}
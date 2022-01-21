#include "TrafficDataReader.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

using namespace rapidjson;

constexpr uint32_t trafficDataSize = 1024*1024*1024;

TrafficDataReader::TrafficDataReader(const char* filepath, std::vector<Traffic>& vTraffic)
{
    FILE* fp = fopen(filepath, "rb"); // non-Windows use "r"
    
    char *readBuffer = new char[trafficDataSize];
    FileReadStream is(fp, readBuffer, trafficDataSize);
    
    Document doc;
    if (doc.ParseStream(is).HasParseError()) {
        std::cout << "\nParse error in : " << filepath << std::endl;
        return;
    }
    const Value& jsonTraffic = doc["traffic"];

    for (SizeType i = 0; i < jsonTraffic.Size(); i++) {
        Traffic traffic;
        traffic.AircraftID = jsonTraffic[i]["id"].GetInt();
        traffic.groundSpeed = jsonTraffic[i]["groundSpeed"].GetInt();
        
        std::cout << "\nId : " << traffic.AircraftID;
        const Value& jsonTrafficPath = jsonTraffic[i]["path"];

        for (SizeType j = 0; j < jsonTrafficPath.Size(); j++) {
            Position pos;
            pos.coord.latitude = jsonTrafficPath[j]["latitude"].GetFloat();
            pos.coord.longitude = jsonTrafficPath[j]["longitude"].GetFloat();
            pos.altitude = jsonTrafficPath[j]["altitude"].GetFloat();

            traffic.path.emplace_back(pos);
        }
        std::cout << ", Count : " << traffic.path.size() << std::endl;

        vTraffic.emplace_back(traffic);
    }

}

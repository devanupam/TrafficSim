#pragma once

#include <stdint.h>

#pragma pack(push,1)

using prec_t = float;

struct LngLat {
    prec_t latitude;
    prec_t longitude;
};

struct Position
{
    LngLat coord;
    prec_t altitude;
};

struct Aircraft
{
    Position position;
    prec_t heading = 0;
    prec_t groundSpeed;
    uint32_t AircraftID;
};

#pragma pack(pop)
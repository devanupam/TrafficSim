#pragma once

#include <vector>
#include "Aircraft.h"

struct Traffic
{
    uint16_t AircraftID;
    prec_t groundSpeed; // In knots
    std::vector<Position> path;
};

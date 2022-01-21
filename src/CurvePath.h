#pragma once

#include <vector>
#include "Aircraft.h"
#include "MapUtil.h"

namespace ADSB {

enum class LateralPathNode {
    point,
    straight,
    curve_l,
    curve_r
};

struct ArcSeg {
    Position initPos;
    Position termPos;
    LateralPathNode nodeType;
    prec_t radius;
};

class CurvePath {
    private:
        static constexpr uint8_t min_turning_radius = 30; // In meter
        static constexpr uint8_t min_heading_change_threshold = 3; //In degree
        static constexpr int16_t max_accel = 100; //In m2/s
        static constexpr int16_t max_radius = 1400; //Max Radius in meter
        static constexpr int16_t hdg_change_radius = 10; //Radius change in meter for one degree heading change

        Position origin;
        std::vector<ArcSeg> arcs;
        Position destination;

    public:
        ArcSeg calcArcSegment(Position start, Position inter, Position end);
        void calcArcSegments(std::vector<Position>& positions);
        void getArcPath(std::vector<LngLat>& arcPath, int idx);
};

}
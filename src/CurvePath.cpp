#include "CurvePath.h"
#include <math.h>
#include <iostream>

namespace ADSB {

ArcSeg CurvePath::calcArcSegment(Position start, Position inter, Position end) {
    prec_t brngStartInter = calculateBearing(start.coord, inter.coord);
    prec_t brngStartEnd = calculateBearing(start.coord, end.coord);
    prec_t headingChange = abs(brngStartEnd - brngStartInter);

    std::cout << "\nHeading change : " << headingChange << std::endl;

    ArcSeg arcSeg;

    //Consider less than min threshold heading change as straight line points
    if(headingChange < min_heading_change_threshold) {
        arcSeg.initPos = start;
        arcSeg.termPos = end;
        arcSeg.nodeType = LateralPathNode::straight;
        arcSeg.radius = 0;
    }
    else {
        float turning_radius = max_radius - (hdg_change_radius * headingChange);
    }
}

void CurvePath::calcArcSegments(std::vector<Position>& positions) {
    auto pathCnt = positions.size();
    if (pathCnt < 2) return;

    origin = positions.at(0);

    for (size_t i = 1; i < pathCnt-1; i++) {
        arcs.emplace_back(calcArcSegment(positions[i], positions[i+1], positions[i+2]));
    }
    destination = positions.at(pathCnt-1);    
}


}
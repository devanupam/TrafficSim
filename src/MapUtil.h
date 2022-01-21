
#pragma once

#include <vector>
#include "Aircraft.h"

namespace ADSB {

#ifndef M_PI
constexpr prec_t M_PI = 3.14159265358979323846;
#endif

// Knots to meter per second
static constexpr prec_t knots_to_ms = 0.514444;

// earth's radius from wikipedia varies between 6,356.750 km — 6,378.135 km (˜3,949.901 — 3,963.189 miles)
// The IUGG value for the equatorial radius of the Earth is 6378.137 km (3963.19 mile) and Mean radius = 6371 km
static constexpr float earth_radius_in_km = 6371;

inline prec_t deg2rad(prec_t deg) { return deg * M_PI / 180; }

inline prec_t rad2deg(prec_t rad) { return rad * 180 / M_PI; }

///@brief Distance in meter, speed in knots
long getTimeInMilliSec(int dist, prec_t speed);

prec_t calculateBearing(LngLat coord1, LngLat coord2);

///@brief Get great circle distance in KM
prec_t distanceBetweenTwoPoints(LngLat coord1, LngLat coord2);

LngLat getDestinationLatLong(LngLat wp, prec_t azimuth, float distance);

}
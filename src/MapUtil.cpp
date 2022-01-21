
#include "MapUtil.h"
#include <math.h>

namespace ADSB {

prec_t calculateBearing(LngLat coord1, LngLat coord2) {
    prec_t teta1 = deg2rad(coord1.latitude);
    prec_t teta2 = deg2rad(coord2.latitude);
    prec_t delta1 = deg2rad(coord2.latitude - coord1.latitude);
    prec_t delta2 = deg2rad(coord2.longitude - coord1.longitude);

    //==================Heading Formula Calculation================//

    prec_t y = sin(delta2) * cos(teta2);
    prec_t x = cos(teta1)*sin(teta2) - sin(teta1)*cos(teta2)*cos(delta2);
    prec_t brng = atan2(y,x);
    brng = rad2deg(brng);// radians to degrees
    // brng = ( ((int)brng + 360) % 360 ); 

    return brng;
}

LngLat getDestinationLatLong(LngLat wp, prec_t azimuth, float distance) {
    prec_t brng = deg2rad(azimuth); // Bearing is degrees converted to radians.

    float d = distance / 1000; // Distance m converted to km

    prec_t lat1 = deg2rad(wp.latitude);  // Current dd lat point converted to radians
    prec_t lon1 = deg2rad(wp.longitude); // Current dd long point converted to radians

    prec_t lat2 = asin(sin(lat1) * cos(d / earth_radius_in_km) + cos(lat1) * sin(d / earth_radius_in_km) * cos(brng));
    prec_t lon2 = lon1 + atan2(sin(brng) * sin(d / earth_radius_in_km) * cos(lat1), cos(d / earth_radius_in_km) - sin(lat1) * sin(lat2));

    // convert back to degrees
    LngLat nextWp;
    nextWp.latitude = rad2deg(lat2);
    nextWp.longitude = rad2deg(lon2);

    return nextWp;
}

prec_t distanceBetweenTwoPoints(LngLat coord1, LngLat coord2) {
    // main code inside the class
    prec_t dlat1 = deg2rad(coord1.latitude);
    prec_t dlong1 = deg2rad(coord1.longitude);

    prec_t dlat2 =  deg2rad(coord2.latitude);
    prec_t dlong2 = deg2rad(coord2.longitude);

    prec_t dLong = dlong1 - dlong2;
    prec_t dLat = dlat1 - dlat2;

    prec_t aHarv = pow(sin(dLat / 2.0), 2.0) + cos(dlat1) * cos(dlat2) * pow(sin(dLong / 2), 2);
    prec_t cHarv = 2 * atan2(sqrt(aHarv), sqrt(1.0 - aHarv));

    return earth_radius_in_km * cHarv;
}


long getTimeInMilliSec(int dist, prec_t speed) {
    prec_t speed_ms = knots_to_ms * speed;
    return (dist * 1000 / speed_ms );
}

}
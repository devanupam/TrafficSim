#include "TrafficDataWriter.h"

namespace ADSB {

    void TrafficDataWriter::writeTrafficData(Aircraft acft, uint8_t idx) {
        int offset = (idx * aircraft_data_size) + aircraft_cnt_size;
        sm_handle.setValue(offset, (uint8_t*) &acft, sizeof(acft));
    }

    void TrafficDataWriter::writeTrafficCount(uint8_t count) {
        sm_handle.setValue(0, &count, aircraft_cnt_size);
    }

}

#pragma once

#include "SharedMemoryHandle.h"
#include "Aircraft.h"

namespace ADSB {

    class TrafficDataWriter
    {
    private:
        static constexpr int aircraft_data_size = sizeof(Aircraft);
        static constexpr uint8_t aircraft_cnt_size = sizeof(uint8_t);

        SharedMemoryHandle sm_handle;
    public:
        TrafficDataWriter(const char* smName) : sm_handle(smName) { }

        void writeTrafficData(Aircraft acft, uint8_t idx);

        void writeTrafficCount(uint8_t count);

    };

}
#pragma once

#include <math.h>
#include <windows.h>

namespace ADSB {

class SharedMemoryHandle
{
private:
    static constexpr int BUF_SIZE = 256;
    HANDLE hMapFile;
    unsigned char* pBuf = nullptr;

public:
    SharedMemoryHandle() = default;
    SharedMemoryHandle(const char* szName);
    void create(const char* szName, int size = BUF_SIZE);
    void open(const char* szName, int size);

    bool isOpen();

    float getValue(int offset, int size);
    int setValue(int offset, int size, float value);

    void getValue(int offset, unsigned char* value, int size);
    void setValue(int offset, unsigned char* value, int size);
    ~SharedMemoryHandle();
};

}
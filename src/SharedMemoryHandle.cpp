
#include "SharedMemoryHandle.h"
#include <assert.h>
#include <iostream>
#include <mutex>

namespace ADSB {

static std::mutex adsbMtx;

SharedMemoryHandle::SharedMemoryHandle(const char* szName)
{
    create(szName);
}

SharedMemoryHandle::~SharedMemoryHandle()
{
    if (pBuf) {
        std::cout << "\nShared memory destroyed" << std::endl;
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
        pBuf = nullptr;
    }
}

void SharedMemoryHandle::create(const char* szName, int size) {
    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, szName);    
    pBuf = (unsigned char*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, size);
    if (pBuf == nullptr)
    {
	    CloseHandle(hMapFile);
        std::cout << "\nShared memory creation failed : " << szName << std::endl;
        // assert(pBuf);
    }
    else {
        std::cout << "\nShared memory created : " << szName << std::endl;
    }
}

void SharedMemoryHandle::open(const char* szName, int size) {
    hMapFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, szName );
    if (!hMapFile) {
        std::cout << "Could not open file mapping object : " << szName << std::endl;
        return;
    }

    pBuf = (unsigned char*) MapViewOfFile( hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, size );
    if (!pBuf) {
        std::cout << "Could not open map view of file : " << szName << std::endl;
        CloseHandle(hMapFile);
    }
}

bool SharedMemoryHandle::isOpen() {
    return (pBuf ? true : false);
}

float SharedMemoryHandle::getValue(int offset, int size)
{
    float value = 0.0;
    if (pBuf) {
        memcpy(&value, (pBuf + offset), size);
    }
    return value;
}

int SharedMemoryHandle::setValue(int offset, int size, float value)
{
    if (pBuf) {
        memcpy((pBuf + offset), &value, size);
        return 0;
    }
    return -1;
}

void SharedMemoryHandle::setValue(int offset, unsigned char* value, int size)
{
    std::lock_guard<std::mutex> stateLock(adsbMtx);
    memcpy((pBuf + offset), value, size);
}

void SharedMemoryHandle::getValue(int offset, unsigned char* value, int size)
{
    memcpy(value, (pBuf + offset), size);
}

}
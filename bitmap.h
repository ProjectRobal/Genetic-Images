#ifndef BITMAP_H
#define BITMAP_H

#include <cinttypes>

namespace bitmap
{

    struct header
    {
        char signature[2];
        uint32_t FileSize;
        uint32_t reserved;
        uint32_t DataOffset;
    };

    struct InfoHeader
    {
        uint32_t size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bitCount;
        uint32_t compression;
        uint32_t ImageSize;
        uint32_t XpixelsPerM;
        uint32_t YpixelsPerM;
        uint32_t ColorsUsed;
        uint32_t ColorsImportant;
    };

    struct ColorTable
    {
        uint8_t Red;
        uint8_t Green;
        uint8_t Blue;
        uint8_t Reserved;
    };


};

#endif // BITMAP_H

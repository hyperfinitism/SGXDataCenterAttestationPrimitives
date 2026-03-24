/*
* Copyright(c) 2011-2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _ENCODE_HELPER_H_
#define _ENCODE_HELPER_H_

#include <iostream>
#include <vector>
#include <string>


using Bytes = std::vector<uint8_t>;

static inline uint32_t swapBytes(uint32_t val)
{
	return (
		((val << 24) & 0xff000000) |
		((val << 8) & 0x00ff0000) |
		((val >> 8) & 0x0000ff00) |
		((val >> 24) & 0x000000ff)
		);
}

static inline uint16_t toUint16(uint8_t leftMostByte, uint8_t rightMostByte)
{
	uint32_t ret = 0;
	ret |= static_cast<uint16_t>(rightMostByte);
	ret |= (static_cast<uint16_t>(leftMostByte) << 8) & 0xff00;
	return static_cast<uint16_t>(ret);
}

static inline uint32_t toUint32(uint16_t msBytes, uint16_t lsBytes)
{
	uint32_t ret = 0;

	ret |= static_cast<uint32_t>(lsBytes);
	ret |= (static_cast<uint32_t>(msBytes) << 16) & 0xffff0000;

	return ret;
}


static inline uint32_t toUint32(uint8_t leftMostByte, uint8_t leftByte, uint8_t rightByte, uint8_t rightMostByte)
{
	return toUint32(toUint16(leftMostByte, leftByte), toUint16(rightByte, rightMostByte));
}



static inline uint8_t asciiToValue(const char in)
{
    if (std::isxdigit(in))
    {
        if(in >= '0' && in <= '9')
        {
            return static_cast<uint8_t>(in - '0');
        }
        if(in >= 'A' && in <= 'F')
        {
            return static_cast<uint8_t>(in - 'A' + 10);
        }
        if(in >= 'a' && in <= 'f')
        {
            return static_cast<uint8_t>(in - 'a' + 10);
        }
    }
    throw std::invalid_argument("Invalid hex character");
}


static inline Bytes hexStringToBytes(const std::string& hexEncoded)
{
    try {
        auto pos = hexEncoded.cbegin();
        Bytes outBuffer;
        outBuffer.reserve(hexEncoded.length() / 2);

        while (pos < hexEncoded.cend())
        {
            outBuffer.push_back(static_cast<uint8_t>(asciiToValue(*(pos + 1)) + (asciiToValue(*pos) << 4)));
            pos = std::next(pos, 2);
        }
        return outBuffer;
    }
    catch(const std::invalid_argument&)
    {
        return {};
    }
}

static inline uint32_t BytesToUint32(const Bytes& input)
{
	auto position = input.cbegin();
	return swapBytes(toUint32(*position, *(std::next(position)), *(std::next(position, 2)), *(std::next(position, 3))));
}


static inline Bytes applyMask(const Bytes& base, const Bytes& mask)
{
    Bytes result;

    if(base.size() != mask.size())
    {
        return result;
    }

    auto mask_it = mask.cbegin();
    std::transform(base.cbegin(), base.cend(), std::back_inserter(result), [&mask_it](const unsigned char &base_it) {
        return (uint8_t)((base_it) & (*(mask_it++)));
    });

    return result;
}


#endif

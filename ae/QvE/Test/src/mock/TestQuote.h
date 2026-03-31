/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TEST_QUOTE_H
#define _TEST_QUOTE_H

#include "QuoteVerification/Quote.h"
#include <array>
#include <cstdint>

namespace intel { namespace sgx { namespace dcap {

// Helper class to expose protected members for testing
class TestQuote : public Quote {
public:
    void setHeaderVersion(uint16_t version) {
        header.version = version;
    }

    void setTeeType(uint32_t teeType) {
        header.teeType = teeType;
    }

    void setTdReport10TeeTcbSvn(const std::array<uint8_t, 16>& svn) {
        tdReport10.teeTcbSvn = svn;
    }

    void setTdReport15TeeTcbSvn(const std::array<uint8_t, 16>& svn) {
        tdReport15.teeTcbSvn = svn;
    }

    void setTdReport15ExTeeTcbSvn(const std::array<uint8_t, 16>& svn) {
        tdReport15Ex.teeTcbSvn = svn;
    }
};

}}} // namespace intel::sgx::dcap

#endif //_TEST_QUOTE_H

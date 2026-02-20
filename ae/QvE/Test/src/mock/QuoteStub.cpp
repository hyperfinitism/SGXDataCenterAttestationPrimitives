/*
* Copyright(c) 2026 Intel Corporation
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <algorithm>
#include "QuoteVerification/Quote.h"

namespace intel { namespace sgx { namespace dcap {

    const std::array<uint8_t, 16>& Quote::getTeeTcbSvn() const
    {
        // Prefer tdReport10 if it looks initialized, otherwise fall back to a static zero array.
        static const std::array<uint8_t, 16> emptySvn{};

        // Try tdReport10
        if (std::any_of(tdReport10.teeTcbSvn.begin(),
                        tdReport10.teeTcbSvn.end(),
                        [](uint8_t b){ return b != 0; }))
        {
            return tdReport10.teeTcbSvn;
        }

        // Try tdReport15
        if (std::any_of(tdReport15.teeTcbSvn.begin(),
                        tdReport15.teeTcbSvn.end(),
                        [](uint8_t b){ return b != 0; }))
        {
            return tdReport15.teeTcbSvn;
        }

        // Try tdReport15Ex
        if (std::any_of(tdReport15Ex.teeTcbSvn.begin(),
                        tdReport15Ex.teeTcbSvn.end(),
                        [](uint8_t b){ return b != 0; }))
        {
            return tdReport15Ex.teeTcbSvn;
        }

        // Default stub value
        return emptySvn;
    }

    const std::array<uint8_t, 48>& Quote::getMrSignerSeam() const
    {
        static const std::array<uint8_t, 48> emptyMrSigner{};
        return emptyMrSigner;
    }

    const std::array<uint8_t, 8>& Quote::getSeamAttributes() const
    {
        static const std::array<uint8_t, 8> emptyAttrs{};
        return emptyAttrs;
    }

    const Header& Quote::getHeader() const
    {
        return header;
    }

    const Body& Quote::getBody() const
    {
        return body;
    }

    const EnclaveReport& Quote::getEnclaveReport() const
    {
        return enclaveReport;
    }

    const TDReport10& Quote::getTdReport10() const
    {
        return tdReport10;
    }

    const TDReport15& Quote::getTdReport15() const
    {
        return tdReport15;
    }

    const TDReport15Ex& Quote::getTdReport15Ex() const
    {
        return tdReport15Ex;
    }

    const std::vector<uint8_t>& Quote::getSignedData() const
    {
        return signedData;
    }

}}} // namespace intel::sgx::dcap

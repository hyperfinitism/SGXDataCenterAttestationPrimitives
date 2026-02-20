/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MOCK_PCK_CERTIFICATE_H
#define _MOCK_PCK_CERTIFICATE_H

#include <gmock/gmock.h>
#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap {

    class MockPckCertificate : public parser::x509::PckCertificate {
    public:
        MOCK_METHOD(const parser::x509::Tcb&, getTcb, (), (const, override));
        MOCK_METHOD(const std::vector<uint8_t>&, getPceId, (), (const, override));
        MOCK_METHOD(const std::vector<uint8_t>&, getFmspc, (), (const, override));
        MOCK_METHOD(const std::vector<uint8_t>&, getPpid, (), (const, override));
        MOCK_METHOD(parser::x509::SgxType, getSgxType, (), (const, override));
    };

}}} // namespace intel::sgx::dcap

#endif // _MOCK_PCK_CERTIFICATE_H


/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace x509 {

    PckCertificate::PckCertificate(const Certificate& certificate)
        : Certificate(certificate),
          _ppid{},
          _pceId{},
          _fmspc{},
          _tcb{},
          _sgxType{}
    {}

    bool PckCertificate::operator==(const PckCertificate& other) const
    {
        return Certificate::operator==(other) &&
               _ppid == other._ppid &&
               _pceId == other._pceId &&
               _fmspc == other._fmspc &&
               _tcb == other._tcb &&
               _sgxType == other._sgxType;
    }

    const std::vector<uint8_t>& PckCertificate::getPpid() const
    {
        return _ppid;
    }

    const std::vector<uint8_t>& PckCertificate::getPceId() const
    {
        return _pceId;
    }

    const std::vector<uint8_t>& PckCertificate::getFmspc() const
    {
        return _fmspc;
    }

    SgxType PckCertificate::getSgxType() const
    {
        return _sgxType;
    }

    const Tcb& PckCertificate::getTcb() const
    {
        return _tcb;
    }

    PckCertificate PckCertificate::parse(const std::string& pem)
    {
        return PckCertificate(pem);
    }

    // Private

    PckCertificate::PckCertificate(const std::string& pem)
        : Certificate(pem),
          _ppid{},
          _pceId{},
          _fmspc{},
          _tcb{},
          _sgxType{}
    {}

}}}}} // namespace intel::sgx::dcap::parser::x509


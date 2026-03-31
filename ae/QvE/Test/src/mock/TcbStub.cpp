/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace x509 {

    Tcb::Tcb(const std::vector<uint8_t>& cpusvn,
             const std::vector<uint8_t>& cpusvnComponents,
             uint32_t pcesvn) :
            _cpuSvn(cpusvn),
            _cpuSvnComponents(cpusvnComponents),
            _pceSvn(pcesvn)
    {}

    uint32_t Tcb::getSgxTcbComponentSvn(uint32_t componentNumber) const
    {
        if (componentNumber >= _cpuSvnComponents.size())
        {
            return 0;
        }
        return _cpuSvnComponents[componentNumber];
    }

    const std::vector<uint8_t>& Tcb::getSgxTcbComponents() const
    {
        return _cpuSvnComponents;
    }

    uint32_t Tcb::getPceSvn() const
    {
        return _pceSvn;
    }

    const std::vector<uint8_t>& Tcb::getCpuSvn() const
    {
        return _cpuSvn;
    }

    bool Tcb::operator==(const Tcb& other) const
    {
        return _cpuSvn == other._cpuSvn &&
               _cpuSvnComponents == other._cpuSvnComponents &&
               _pceSvn == other._pceSvn;
    }

}}}}} // namespace intel::sgx::dcap::parser::x509


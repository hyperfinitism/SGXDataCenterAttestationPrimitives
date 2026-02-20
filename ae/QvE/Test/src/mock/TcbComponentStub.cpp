/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace json {

    uint8_t TcbComponent::getSvn() const
    {
        return _svn;
    }

    const std::string& TcbComponent::getCategory() const
    {
        return _category;
    }

    const std::string& TcbComponent::getType() const
    {
        return _type;
    }

    bool TcbComponent::operator>(const TcbComponent& other) const
    {
        return _svn > other._svn;
    }

    bool TcbComponent::operator<(const TcbComponent& other) const
    {
        return _svn < other._svn;
    }

}}}}} // namespace intel::sgx::dcap::parser::json

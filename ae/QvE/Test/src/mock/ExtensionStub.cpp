/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace x509 {

    Extension::Extension()
        : _nid{},
          _name{},
          _value{}
    {}

    Extension::Extension(int nid,
                         const std::string& name,
                         const std::vector<uint8_t>& value) noexcept
        : _nid(nid),
          _name(name),
          _value(value)
    {}

    bool Extension::operator==(const Extension& other) const
    {
        return _nid == other._nid &&
               _name == other._name &&
               _value == other._value;
    }

    bool Extension::operator!=(const Extension& other) const
    {
        return !(*this == other);
    }

    int Extension::getNid() const
    {
        return _nid;
    }

    const std::string& Extension::getName() const
    {
        return _name;
    }

    const std::vector<uint8_t>& Extension::getValue() const
    {
        return _value;
    }

}}}}} // namespace intel::sgx::dcap::parser::x509


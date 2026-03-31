/*
 * Copyright(c) 2025-2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace json {
    const std::vector<uint8_t> &TdxModule::getAttributes() const {
        return _attributes;
    }

    const std::vector<uint8_t> &TdxModule::getAttributesMask() const {
        return _attributesMask;
    }

    const std::vector<uint8_t> &TdxModule::getMrSigner() const {
        return _mrsigner;
    }
}}}}} // namespace intel::sgx::dcap::parser::json

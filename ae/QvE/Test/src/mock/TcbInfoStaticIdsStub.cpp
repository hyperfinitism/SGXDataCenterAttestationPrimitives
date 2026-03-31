/*
 * Copyright(c) 2026 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SgxEcdsaAttestation/AttestationParsers.h"

namespace intel { namespace sgx { namespace dcap { namespace parser { namespace json {

// Provide definitions for static identifiers used in QvE tests when the full
// AttestationParsers library is not linked.

const std::string TcbInfo::SGX_ID = "SGX";
const std::string TcbInfo::TDX_ID = "TDX";

}}}}} // namespace intel::sgx::dcap::parser::json

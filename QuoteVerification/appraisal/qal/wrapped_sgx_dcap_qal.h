/*
* Copyright(c) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @brief Wrapper include for @c sgx_dcap_qal.h.
 *
 * This header resolves the ambiguity between two variants of
 * @c sgx_dcap_qal.h:
 * - the legacy, self‑contained version shipped with SGX SDK <= 2.28, and
 * - the current version in this repository, which depends on
 *   @c sgx_dcap_qal_types.h which is available starting with SGX SDK >= 2.29.
 *
 * Using a distinct wrapper header ensures deterministic build behavior,
 * independent of the SGX SDK version installed on the system.
 *
 * @note This is a temporary proxy header. It may be removed in a future
 *       DCAP release once SGX SDK 2.29+ is sufficiently widespread.
 */


#pragma once

#if defined(__has_include)

  #if __has_include(<sgx_dcap_qal_types.h>)
    #include "sgx_dcap_qal.h"
  #else
    #pragma message( \
        "NOTICE: Building with an older SGX SDK (missing <sgx_dcap_qal_types.h>). " \
        "Please upgrade SGX SDK (and/or 'libsgx-headers', if installed) to version >= 2.29.")
    #include <sgx_dcap_qal.h>
  #endif

#else
  /* __has_include not available: fall back to local header */
  #include "sgx_dcap_qal.h"
#endif
/**
 * Copyright(c) 2026 Intel Corporation
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Include wrapper for sgx_quote_5.h — suppress C-mode warnings from SDK header.
 *
 * sgx_quote_5.h contains anonymous enums inside tee_info_v1_5_ex_t.  When
 * compiled as C (e.g. tdx_verify.c) these trigger "declaration does not declare
 * anything" errors under -Werror.  The system_header pragma treats the included
 * content as a system header, suppressing all warnings (including -Werror) for it.
 */
#pragma once

#pragma GCC system_header
#include <sgx_quote_5.h>

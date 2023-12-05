/*
 * Copyright HeteroCL authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hcl-c/Dialect/Dialects.h"

#include "amc/Dialect/AmcDialect.h"
#include "hcl/Dialect/HeteroCLDialect.h"
#include "mlir/CAPI/Registration.h"

MLIR_DEFINE_CAPI_DIALECT_REGISTRATION(HCL, hcl, mlir::hcl::HeteroCLDialect)
MLIR_DEFINE_CAPI_DIALECT_REGISTRATION(AMC, amc, circt::amc::AmcDialect)
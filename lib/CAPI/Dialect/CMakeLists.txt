# Copyright HeteroCL authors. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

get_property(circt_dialect_libs GLOBAL PROPERTY CIRCT_DIALECT_LIBS)
get_property(circt_conversion_libs GLOBAL PROPERTY CIRCT_CONVERSION_LIBS)

add_mlir_public_c_api_library(MLIRHCLCAPI
  Dialects.cpp
  HCLTypes.cpp
  HCLAttributes.cpp
  Registration.cpp
  ${PROJECT_SOURCE_DIR}/lib/Transforms/Passes.cpp
  ${PROJECT_SOURCE_DIR}/lib/Transforms/LoopTransformations.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir-c

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRCAPIIR
  MLIRSupport
  MLIRHeteroCL
  MLIRHCLTransformOps
  MLIRHCLPasses
  MLIRHCLConversion
  CIRCTAmc
  CIRCTAmcSupport
  CIRCTCalyx
  CIRCTCalyxTransforms
  CIRCTHW
  CIRCTAmcPasses
  ${circt_dialect_libs}
  ${circt_conversion_libs}
  )

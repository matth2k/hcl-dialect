/*
 * Copyright HeteroCL authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hcl-c/Dialect/HCLTypes.h"
#include "hcl/Dialect/HeteroCLTypes.h"
#include "mlir/CAPI/Registration.h"

using namespace mlir;
using namespace hcl;

bool hclMlirTypeIsALoopHandle(MlirType type) {
  return isa<hcl::LoopHandleType>(unwrap(type));
}

MlirType hclMlirLoopHandleTypeGet(MlirContext ctx) {
  return wrap(hcl::LoopHandleType::get(unwrap(ctx)));
}

bool hclMlirTypeIsAOpHandle(MlirType type) {
  return isa<hcl::OpHandleType>(unwrap(type));
}

MlirType hclMlirOpHandleTypeGet(MlirContext ctx) {
  return wrap(hcl::OpHandleType::get(unwrap(ctx)));
}

bool hclMlirTypeIsAFixedType(MlirType type) {
  return isa<hcl::FixedType>(unwrap(type));
}

MlirType hclMlirFixedTypeGet(MlirContext ctx, size_t width, size_t frac) {
  return wrap(hcl::FixedType::get(unwrap(ctx), width, frac));
}

unsigned hclMlirFixedTypeGetWidth(MlirType type) {
  return cast<hcl::FixedType>(unwrap(type)).getWidth();
}

unsigned hclMlirFixedTypeGetFrac(MlirType type) {
  return cast<hcl::FixedType>(unwrap(type)).getFrac();
}

bool hclMlirTypeIsAUFixedType(MlirType type) {
  return isa<hcl::UFixedType>(unwrap(type));
}

MlirType hclMlirUFixedTypeGet(MlirContext ctx, size_t width, size_t frac) {
  return wrap(hcl::UFixedType::get(unwrap(ctx), width, frac));
}

unsigned hclMlirUFixedTypeGetWidth(MlirType type) {
  return cast<hcl::UFixedType>(unwrap(type)).getWidth();
}

unsigned hclMlirUFixedTypeGetFrac(MlirType type) {
  return cast<hcl::UFixedType>(unwrap(type)).getFrac();
}

bool hclMlirTypeIsAStructType(MlirType type) {
  return isa<hcl::StructType>(unwrap(type));
}

MlirType hclMlirStructTypeGet(MlirContext ctx, intptr_t numElements,
                              MlirType const *elements) {
  SmallVector<Type, 4> types;
  ArrayRef<Type> typeRef = unwrapList(numElements, elements, types);
  return wrap(hcl::StructType::get(unwrap(ctx), typeRef));
}

MlirType hclMlirStructGetEleType(MlirType type, size_t pos) {
  return wrap(cast<hcl::StructType>(unwrap(type)).getElementTypes()[pos]);
}

unsigned hclMlirStructTypeGetNumFields(MlirType type) {
  return cast<hcl::StructType>(unwrap(type)).getElementTypes().size();
}

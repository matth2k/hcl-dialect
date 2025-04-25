/*
 * Copyright HeteroCL authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hcl/Translation/Utils.h"
#include "llvm/Support/raw_ostream.h"

using namespace mlir;
using namespace hcl;

// TODO: update naming rule.
SmallString<8> HCLEmitterBase::addName(Value val, bool isPtr,
                                       std::string name) {
  assert(!isDeclared(val) && "has been declared before.");

  SmallString<8> valName;
  if (isPtr)
    valName += "*";

  if (name != "") {
    if (state.nameConflictCnt.count(name) > 0) {
      state.nameConflictCnt[name]++;
      valName += StringRef(name + std::to_string(state.nameConflictCnt[name]));
    } else { // first time
      state.nameConflictCnt[name] = 0;
      valName += name;
    }
  } else {
    valName += StringRef("v" + std::to_string(state.nameTable.size()));
  }
  state.nameTable[val] = valName;

  return valName;
};

SmallString<8> HCLEmitterBase::getName(Value val) {
  // For constant scalar operations, the constant number will be returned
  // rather than the value name.
  if (auto defOp = val.getDefiningOp()) {
    if (auto constOp = dyn_cast<arith::ConstantOp>(defOp)) {
      auto constAttr = constOp.getValue();

      if (auto boolAttr = dyn_cast<BoolAttr>(constAttr)) {
        return SmallString<8>(std::to_string(boolAttr.getValue()));

      } else if (auto floatAttr = dyn_cast<FloatAttr>(constAttr)) {
        auto value = floatAttr.getValueAsDouble();
        if (std::isfinite(value))
          return SmallString<8>(std::to_string(value));
        else if (value > 0)
          return SmallString<8>("INFINITY");
        else
          return SmallString<8>("-INFINITY");

      } else if (auto intAttr = dyn_cast<IntegerAttr>(constAttr)) {
        auto value = intAttr.getInt();
        return SmallString<8>(std::to_string(value));
      }
    }
  }
  return state.nameTable.lookup(val);
};

void fixUnsignedType(Value &result, bool isUnsigned) {
  if (isUnsigned) { // unsigned type
    if (isa<MemRefType>(result.getType())) {
      auto arrayType = dyn_cast<MemRefType>(result.getType());
      Type elt = IntegerType::get(
          arrayType.getContext(),
          cast<IntegerType>(arrayType.getElementType()).getWidth(),
          IntegerType::SignednessSemantics::Unsigned);
      result.setType(MemRefType::get(arrayType.getShape(), elt,
                                     arrayType.getLayout(),
                                     arrayType.getMemorySpace()));
    } else if (isa<IntegerType>(result.getType())) {
      Type type =
          IntegerType::get(result.getType().getContext(),
                           cast<IntegerType>(result.getType()).getWidth(),
                           IntegerType::SignednessSemantics::Unsigned);
      result.setType(type);
    }
  }
}

void fixUnsignedType(memref::GlobalOp &op, bool isUnsigned) {
  if (isUnsigned) { // unsigned type
    auto type = op.getTypeAttr().getValue();
    if (isa<MemRefType>(type)) {
      auto arrayType = dyn_cast<MemRefType>(type);
      Type elt = IntegerType::get(
          arrayType.getContext(),
          cast<IntegerType>(arrayType.getElementType()).getWidth(),
          IntegerType::SignednessSemantics::Unsigned);
      // get a memref type attr
      op.setTypeAttr(TypeAttr::get(
          MemRefType::get(arrayType.getShape(), elt, arrayType.getLayout(),
                          arrayType.getMemorySpace())));
    } else if (isa<IntegerType>(type)) {
      Type type = IntegerType::get(type.getContext(),
                                   cast<IntegerType>(type).getWidth(),
                                   IntegerType::SignednessSemantics::Unsigned);
      op.setTypeAttr(TypeAttr::get(type));
    }
  }
}

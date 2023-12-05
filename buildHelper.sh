cmake -G Ninja .. \
 -DMLIR_DIR=/home/mrh259/shared/amc-dialect/circt/llvm/build/lib/cmake/mlir \
 -DAMC_DIR=/home/mrh259/shared/amc-dialect/build/lib/cmake/mlir \
 -DLLVM_EXTERNAL_LIT=/home/mrh259/shared/amc-dialect/circt/llvm/build/bin/llvm-lit \
 -DPYTHON_BINDING=ON \
 -DPython3_EXECUTABLE=`which python3` \
 -DCMAKE_CXX_FLAGS="-Wfatal-errors -std=c++17" \
 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

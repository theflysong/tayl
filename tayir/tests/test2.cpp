#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

void test2() {
    using namespace tayir;
    OperandPool opPool;
    opPool.AppendOperand(new ImmediateOperand(imm::itype::I16, ImmediateValue{.i32Val = 65535}));
    opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 65535}));
    opPool.AppendOperand(new ImmediateOperand(imm::itype::UI8, ImmediateValue{.i32Val = 65537}));
    opPool.AppendOperand(new ArgListOperand({0, 1, 2}));
    std::cout << opPool.GetOperand(3)->ToString(opPool) << std::endl;
}
#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

int main(int argc, const char **argv) {
    using namespace tayir;
    Operand op(OperandType::CONSTANT, OperandPos::DEST, "111");
    printf("%p\n", op.GetOperandValue());
    Operand op1(op);
    printf("%p\n", op1.GetOperandValue());
    Operand op2(std::move(op));
    printf("%p %p\n", op.GetOperandValue(), op2.GetOperandValue());
    return 0;
}
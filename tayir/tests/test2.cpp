#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

void test2() {
    using namespace tayir;
    TypeManager man;

    IRFunctionBuilder fnBuilder;
    fnBuilder.GetDecl().name = "main";
    fnBuilder.GetDecl().conventionId = 0;
    fnBuilder.GetDecl().returnTypeId = man.GetI32Id();
    fnBuilder.GetDecl().args.push_back(Argument(man.GetI32Id(), "%argc"));
    fnBuilder.GetDecl().args.push_back(Argument(man.GetP64Id(), "%argv"));
    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
            .AppendIns(
                Ins(
                    InsType::ADD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%a"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%b"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC2, "%c")
                )
            )
            .AppendIns(
                Ins(
                    InsType::SUB,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%d"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%a"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC2, "%c")
                )
            )
            .AppendIns(
                Ins(
                    InsType::RET,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%d"),
                    Operand(OperandPos::DEST)
                )
            )
            .Build("start")
    );
    IRFunction *func = fnBuilder.Build();

    IRFuncDecl decl = func->GetDecl();

    std::cout << "def @" << decl.name << "(";
    if (decl.args.size() != 0) {
        Argument firstArg = decl.args.at(0);
        std::cout << man.GetType(firstArg.GetTypeId())->GetName() << " " << firstArg.GetName();
        for (int i = 1 ; i < (int)decl.args.size() ; i ++) {
            std::cout << ", " << man.GetType(decl.args.at(i).GetTypeId())->GetName() << " " << decl.args.at(i).GetName();
        }
    }
    std::cout << ") ";
    if (decl.returnTypeId != -1) {
        std::cout << "-> " << man.GetType(decl.returnTypeId)->GetName() << " ";
    }
    std::cout << "{" << std::endl;
    for (int i = 0 ; i < func->GetBlockNum() ; i ++) {
        const IRBasicBlock *block = func->GetBlock(i);
        std::cout << block->GetName();
        if (block->GetArgNum() != 0) {
            std::cout << "(";
            Argument firstArg = block->GetArg(0);
            std::cout << man.GetType(firstArg.GetTypeId())->GetName() << " " << firstArg.GetName();
            for (int i = 1 ; i < block->GetArgNum() ; i ++) {
                std::cout << ", " << man.GetType(block->GetArg(i).GetTypeId())->GetName() << " " << block->GetArg(i).GetName();
            }
            std::cout << ")";
        }
        std::cout << ":\n";
        for (int j = 0 ; j < block->GetInsNum() ; j ++) {
            std::cout << "    ";
            Ins ins = block->GetIns(j);
            if (ins.GetDestOp().GetOperandType() != OperandType::EMPTY) {
                std::cout << ins.GetDestOp().GetOperandValue() << " = ";
            }
            std::cout << ToString(ins.GetInsType()) << " ";
            if (ins.GetSrc1Op().GetOperandType() != OperandType::EMPTY) {
                std::cout << ins.GetSrc1Op().GetOperandValue();
            }
            if (ins.GetSrc2Op().GetOperandType() != OperandType::EMPTY) {
                std::cout << ", " << ins.GetSrc2Op().GetOperandValue();
            }
            std::cout << std::endl;
        }
    }
    std::cout << "}" << std::endl;
    delete func;
}
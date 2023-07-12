#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

void test2() {
    using namespace tayir;
    TypeManager man;
    ArgOpPool pool;
    int arg0Id = pool.AppendArg({
        Operand(OperandType::CONSTANT, OperandPos::DEST, "\"%d%d\""),
        Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%a"),
        Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%b")
    });
    int arg1Id = pool.AppendArg({
        Operand(OperandType::CONSTANT, OperandPos::DEST, "\"%d\\n\""),
        Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%c")
    });

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
                    InsType::ALLOC,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%a$ptr"),
                    Operand(OperandType::TYPE, OperandPos::SRC1, "i32"),
                    Operand(OperandPos::SRC2)
                )
            )
            .AppendIns(
                Ins(
                    InsType::ALLOC,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%b$ptr"),
                    Operand(OperandType::TYPE, OperandPos::SRC1, "i32"),
                    Operand(OperandPos::SRC2)
                )
            )
            .AppendIns(
                Ins(
                    InsType::CALL,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::LABEL, OperandPos::SRC1, "@scanf"),
                    Operand(OperandPos::SRC2),
                    arg0Id
                )
            )
            .AppendIns(
                Ins(
                    InsType::LOAD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%a$val"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%a$ptr"),
                    Operand(OperandPos::SRC2)
                )
            )
            .AppendIns(
                Ins(
                    InsType::LOAD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%b$val"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%b$ptr"),
                    Operand(OperandPos::SRC2)
                )
            )
            .AppendIns(
                Ins(
                    InsType::MUL,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%temp$0"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%b$val"),
                    Operand(OperandType::CONSTANT, OperandPos::SRC2, "2")
                )
            )
            .AppendIns(
                Ins(
                    InsType::ADD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%c"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%a"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC2, "%temp$0")
                )
            )
            .AppendIns(
                Ins(
                    InsType::CALL,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::LABEL, OperandPos::SRC1, "@printf"),
                    Operand(OperandPos::SRC2),
                    arg1Id
                )
            )
            .AppendIns(
                Ins(
                    InsType::RET,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::CONSTANT, OperandPos::SRC1, "0"),
                    Operand(OperandPos::SRC2)
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
            std::cout << block->GetIns(j).ToString(pool) << std::endl;
        }
    }
    std::cout << "}" << std::endl;
    delete func;
}
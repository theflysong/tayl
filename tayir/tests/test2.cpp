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
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::ALLOC,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%b$ptr"),
                    Operand(OperandType::TYPE, OperandPos::SRC1, "i32"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::CALL,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::LABEL, OperandPos::SRC1, "@scanf"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3),
                    arg0Id
                )
            )
            .AppendIns(
                Ins(
                    InsType::LOAD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%a$val"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%a$ptr"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::LOAD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%b$val"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%b$ptr"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::MUL,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%temp$0"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%b$val"),
                    Operand(OperandType::CONSTANT, OperandPos::SRC2, "2"),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::ADD,
                    Operand(OperandType::SSA_VALUE, OperandPos::DEST, "%c"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC1, "%a"),
                    Operand(OperandType::SSA_VALUE, OperandPos::SRC2, "%temp$0"),
                    Operand(OperandPos::SRC3)
                )
            )
            .AppendIns(
                Ins(
                    InsType::CALL,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::LABEL, OperandPos::SRC1, "@printf"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3),
                    arg1Id
                )
            )
            .AppendIns(
                Ins(
                    InsType::RET,
                    Operand(OperandPos::DEST),
                    Operand(OperandType::CONSTANT, OperandPos::SRC1, "0"),
                    Operand(OperandPos::SRC2),
                    Operand(OperandPos::SRC3)
                )
            )
            .Build("start")
    );
    IRFunction *func = fnBuilder.Build();

    func->PrintRawString(man, pool, std::cout);
    
    delete func;
}
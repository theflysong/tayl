#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

void test2() {
    using namespace tayir;

    TypeManager man;

    //TODO: Const String Pool
    OperandPool opPool;
    int FuncFib     = opPool.AppendOperand(new SymbolOperand(SymbolScope::GLOBAL,  "fin"));

    int ValN        = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "n"));
    int ValTmpCond0 = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$cond$0"));
    int ValTmpCond1 = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$cond$1"));
    int ValTmpRet0  = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$ret$0"));
    int ValTmpRet1  = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$ret$1"));
    int ValTmpRes0  = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$res$0"));
    int ValTmpRes1  = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$res$1"));
    int ValTmpRes2  = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "tmp$res$2"));
    
    int LabelIf0    = opPool.AppendOperand(new LabelOperand("if0"));
    int LabelElse0  = opPool.AppendOperand(new LabelOperand("else0"));
    int LabelElse1  = opPool.AppendOperand(new LabelOperand("else1"));

    int ArgComp1    = opPool.AppendOperand(new ArgListOperand({ValTmpRes0}));
    int ArgComp2    = opPool.AppendOperand(new ArgListOperand({ValTmpRes1}));

    int Const0      = opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 0}));
    int Const1      = opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 1}));
    int Const2      = opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 2}));

    IRFunctionBuilder fnBuilder;
    fnBuilder.GetDecl().name = "fib";
    fnBuilder.GetDecl().conventionId = 0;
    fnBuilder.GetDecl().returnTypeId = man.GetI32Id();
    fnBuilder.GetDecl().args.push_back(Argument(man.GetI32Id(), "n"));

    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
            .AppendIns(Ins(InsType::EQU, ValTmpCond0, ValN, Const0))
            .AppendIns(Ins(InsType::BR,  ValTmpCond0, LabelIf0, LabelElse0))
            .Build("start")
    );

    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
            .AppendIns(Ins(InsType::EQU, ValTmpCond1, ValN, Const1))
            .AppendIns(Ins(InsType::BR,  ValTmpCond1, LabelIf0, LabelElse1))
            .Build("else0")
    );

    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
            .AppendIns(Ins(InsType::RET,          -1, Const1))
            .Build("if0")
    );

    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
            .AppendIns(Ins(InsType::SUB,  ValTmpRes0, ValN, Const1))
            .AppendIns(Ins(InsType::SUB,  ValTmpRes1, ValN, Const2))
            .AppendIns(Ins(InsType::CALL, ValTmpRet0, FuncFib, ArgComp1))
            .AppendIns(Ins(InsType::CALL, ValTmpRet1, FuncFib, ArgComp2))
            .AppendIns(Ins(InsType::ADD,  ValTmpRes2, ValTmpRet0, ValTmpRet1))
            .AppendIns(Ins(InsType::RET,          -1, ValTmpRes2))
            .Build("else1")
    );

    IRFunction *func = fnBuilder.Build();
    func->PrintRawString(man, opPool, std::cout);
    delete func;
}
#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

void test2() {
    using namespace tayir;

    TypeManager man;

    //TODO: Const String Pool
    OperandPool opPool;
    int TypeI32    = opPool.AppendOperand(new SymbolOperand(SymbolScope::BUILTIN, "i32"));
    int FuncScanf  = opPool.AppendOperand(new SymbolOperand(SymbolScope::GLOBAL,  "scanf"));
    int FuncPrintf = opPool.AppendOperand(new SymbolOperand(SymbolScope::GLOBAL,  "printf"));
    int ValAPtr    = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "a$ptr"));
    int ValBPtr    = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "b$ptr"));
    int ValAVal    = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "a$val"));
    int ValBVal    = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "b$val"));
    int ValTemp0   = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "temp$0"));
    int ValC       = opPool.AppendOperand(new SymbolOperand(SymbolScope::LOCAL,   "c"));
    int CS0        = opPool.AppendOperand(new SymbolOperand(SymbolScope::GLOBAL,  "cs$annoymous$0"));
    int CS1        = opPool.AppendOperand(new SymbolOperand(SymbolScope::GLOBAL,  "cs$annoymous$1"));

    int ArgComp1   = opPool.AppendOperand(new ArgListOperand({CS0, ValAPtr, ValBPtr}));
    int ArgComp2   = opPool.AppendOperand(new ArgListOperand({CS1, ValC}));

    int Const1     = opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 2}));
    int Const2     = opPool.AppendOperand(new ImmediateOperand(imm::itype::I32, ImmediateValue{.i32Val = 0}));

    IRFunctionBuilder fnBuilder;
    fnBuilder.GetDecl().name = "main";
    fnBuilder.GetDecl().conventionId = 0;
    fnBuilder.GetDecl().returnTypeId = man.GetI32Id();
    fnBuilder.GetDecl().args.push_back(Argument(man.GetI32Id(), "argc"));
    fnBuilder.GetDecl().args.push_back(Argument(man.GetP64Id(), "argv"));

    fnBuilder.AppendBlock(
        IRBasicBlockBuilder()
        .AppendIns(Ins(InsType::ALLOC,  ValAPtr, TypeI32))
        .AppendIns(Ins(InsType::ALLOC,  ValBPtr, TypeI32))
        .AppendIns(Ins(InsType::CALL,        -1, FuncScanf,  ArgComp1))
        .AppendIns(Ins(InsType::LOAD,   ValAVal, ValAPtr))
        .AppendIns(Ins(InsType::LOAD,   ValBVal, ValBPtr))
        .AppendIns(Ins(InsType::MUL,   ValTemp0, ValBVal,    Const1))
        .AppendIns(Ins(InsType::ADD,       ValC, ValAVal,    ValTemp0))
        .AppendIns(Ins(InsType::CALL,        -1, FuncPrintf, ArgComp2))
        .AppendIns(Ins(InsType::RET,         -1, Const2))
        .Build("start")
    );

    IRFunction *func = fnBuilder.Build();
    func->PrintRawString(man, opPool, std::cout);
    delete func;
}
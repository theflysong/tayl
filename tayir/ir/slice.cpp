/**
 * @file slice.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 代码切片
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <ir/slice.h>

namespace tayir {
//---------------------------------------------------------
//|                                                       |
//|                      ir fragment                      |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief IRFragment构造函数
     * 
     * @param insList 指令列表
     */
    IRFragment::IRFragment(std::vector<Ins> insList) 
        : insNum(insList.size()), instructions(new Ins[insNum])
    {
        for (int i = 0 ; i < insNum ; i ++) {
            instructions[i] = insList.at(i);
        }
    }

    /**
     * @brief IRFragment析构函数
     * 
     */
    IRFragment::~IRFragment() {
        if (instructions != NULL) {
            delete[] instructions;
            instructions = NULL;
        }
    }

    /**
     * @brief 获取指令数量
     * 
     * @return 指令数量
     */
    const int IRFragment::GetInsNum() const {
        return insNum;
    }

    /**
     * @brief 获取指令
     * 
     * @param sub 下标
     * @return 指令
     */
    const Ins IRFragment::GetIns(int sub) const {
        if (sub < 0 || sub >= insNum) {
            //TODO: throw an exception instead of const char *
            throw "Out of boundary!";
        }
        return instructions[sub];
    }

    /**
     * @brief 打印
     * 
     * @param pool 操作数池
     * @param outs 输出流 
     */
    void IRFragment::PrintRawString(OperandPool &pool, std::ostream &outs) const {
        for (int i = 0 ; i < insNum ; i ++) {
            outs << "    ";
            instructions[i].PrintRawString(pool, outs);
            outs << std::endl;
        }
    }

//--------------------------------------

    /**
     * @brief IRFragmentBuilder构造函数
     * 
     */
    IRFragmentBuilder::IRFragmentBuilder() {
    }

    /**
     * @brief 获取指令数量
     * 
     * @return 指令数量
     */
    const int IRFragmentBuilder::GetInsNum() const {
        return instructions.size();
    }

    /**
     * @brief 获取指令
     * 
     * @param sub 下标
     * @return 指令
     */
    Ins &IRFragmentBuilder::GetIns(int sub) {
        if (sub < 0 || sub >= (int)instructions.size()) {
            //TODO: throw an exception instead of const char *
            throw "Out of boundary!";
        }
        return instructions.at(sub);
    }

    /**
     * @brief 获取指令
     * 
     * @param ins 指令
     * @return Builder自身
     */
    IRFragmentBuilder &IRFragmentBuilder::AppendIns(Ins ins) {
        instructions.push_back(ins);
        return *this;
    }

    /**
     * @brief 构造IRFragment
     * 
     * @return IRFragment
     */
    IRFragment *IRFragmentBuilder::Build() {
        return new IRFragment(instructions);
    }

//---------------------------------------------------------
//|                                                       |
//|                     ir basicblock                     |
//|                                                       |
//---------------------------------------------------------
    
    /**
     * @brief IRBasicBlock构造函数
     * 
     * @param frag 片段
     * @param name 基本块名
     * @param argList 参数列表
     */
    IRBasicBlock::IRBasicBlock(IRFragment *frag, std::string name, std::vector<Argument> argList) 
        : frag(frag), name(name), argNum(argList.size()), args(new Argument[argNum])
    {
        for (int i = 0 ; i < argNum ; i ++) {
            args[i] = argList.at(i);
        }
    }
    
    /**
     * @brief IRBasicBlock析构函数
     * 
     */
    IRBasicBlock::~IRBasicBlock() {
        if (args != NULL) {
            delete[] args;
        }
        if (frag != NULL) {
            delete frag;
        }
    }

    /**
     * @brief 获取指令数量
     * 
     * @return 指令数量
     */
    const int IRBasicBlock::GetInsNum() const {
        return frag->GetInsNum();
    }

    /**
     * @brief 获取指令
     * 
     * @param sub 下标
     * @return 指令
     */
    const Ins IRBasicBlock::GetIns(int sub) const {
        return frag->GetIns(sub);
    }

    /**
     * @brief 获取获取参数数量
     * 
     * @return 获取参数数量
     */
    const int IRBasicBlock::GetArgNum() const {
        return argNum;
    }

    /**
     * @brief 获取参数
     * 
     * @param sub 下标
     * @return 参数
     */
    const Argument IRBasicBlock::GetArg(int sub) const {
        if (sub < 0 || sub >= argNum) {
            //TODO: throw an exception
            return Argument();
        }
        return args[sub];
    }

    /**
     * @brief 获取基本块名
     * 
     * @return 基本块名
     */
    std::string IRBasicBlock::GetName() const {
        return name;
    }

    /**
     * @brief 打印
     * 
     * @param man 类型管理器
     * @param pool 操作数池
     * @param stream 输出流 
     */
    void IRBasicBlock::PrintRawString(TypeManager &man, OperandPool &pool, std::ostream &outs) const {
        outs << name;
        if (argNum != 0) {
            outs << "(";
            Argument firstArg = args[0];
            outs << man.GetType(firstArg.GetTypeId())->GetName() << " %" << firstArg.GetName();
            for (int i = 1 ; i < argNum ; i ++) {
                outs << ", " << man.GetType(args[i].GetTypeId())->GetName() << " %" << args[i].GetName();
            }
            outs << ")";
        }
        outs << ":\n";
        frag->PrintRawString(pool, outs);
    }

//--------------------------------------

    /**
     * @brief IRBasicBlockBuilder构造函数
     * 
     */
    IRBasicBlockBuilder::IRBasicBlockBuilder() {
    }

    /**
     * @brief 获取指令数量
     * 
     * @return 指令数量
     */
    int IRBasicBlockBuilder::GetInsNum() const {
        return frag.GetInsNum();
    }

    /**
     * @brief 获取指令
     * 
     * @param sub 下标
     * @return 指令
     */
    Ins &IRBasicBlockBuilder::GetIns(int sub) {
        return frag.GetIns(sub);
    }

    /**
     * @brief 追加指令
     * 
     * @param ins 指令
     * @return Builder自身
     */
    IRBasicBlockBuilder &IRBasicBlockBuilder::AppendIns(Ins ins) {
        frag.AppendIns(ins);
        return *this;
    }

    /**
     * @brief 获取参数
     * 
     * @param sub 下标
     * @return 参数
     */
    Argument &IRBasicBlockBuilder::GetArg(int sub) {
        if (sub < 0 || sub >= (int)args.size()) {
            //TODO: throw an exception instead of throw const char *
            throw "out of boundary!";
        }
        return args.at(sub);
    }
    /**
     * @brief 追加参数
     * 
     * @param arg 参数
     * @return Builder自身
     */
    IRBasicBlockBuilder &IRBasicBlockBuilder::AppendArg(Argument arg) {
        args.push_back(arg);
        return *this;
    }

    /**
     * @brief 构建IR基本块
     * 
     * @param name 基本块名
     * @return IR基本块
     */
    IRBasicBlock *IRBasicBlockBuilder::Build(std::string name) {
        return new IRBasicBlock(frag.Build(), name, args);
    }

//---------------------------------------------------------
//|                                                       |
//|                      ir function                      |
//|                                                       |
//---------------------------------------------------------
        
    /**
     * @brief 打印
     * 
     * @param man 类型管理器
     * @param outs 输出流 
     */
    void IRFuncDecl::PrintRawString(TypeManager &man, std::ostream &outs) const {
        outs << "def @" << name << "(";
        if (args.size() != 0) {
            Argument firstArg = args.at(0);
            outs << man.GetType(firstArg.GetTypeId())->GetName() << " %" << firstArg.GetName();
            for (int i = 1 ; i < (int)args.size() ; i ++) {
                outs << ", " << man.GetType(args.at(i).GetTypeId())->GetName() << " %" << args.at(i).GetName();
            }
        }
        outs << ") ";
        if (returnTypeId != -1) {
            outs << "-> " << man.GetType(returnTypeId)->GetName();
        }
    }

    /**
     * @brief IRFunction构造函数
     * 
     * @param blockList 基本块表
     * @param decl 函数声明
     */
    IRFunction::IRFunction(std::vector<IRBasicBlock *> blockList, IRFuncDecl decl) 
        : decl(decl), insNum(0), blockNum(blockList.size()), blocks(new IRBasicBlock*[blockNum])
    {
        for (int i = 0 ; i < blockNum ; i ++) {
            insNum += blockList.at(i)->GetInsNum();
            blocks[i] = blockList.at(i);
        }
    }
    
    /**
     * @brief IRFunction析构函数
     * 
     */
    IRFunction::~IRFunction() {
    }
    
    /**
     * @brief 获取指令数量
     * 
     * @return 指令数量
     */
    const int IRFunction::GetInsNum() const {
        return insNum;
    }
    
    /**
     * @brief 获取指令
     * 
     * @param sub 下标
     * @return 指令
     */
    const Ins IRFunction::GetIns(int sub) const {
        if (sub < 0 || sub >= insNum) {
            //TODO: throw an exception instead of throw const char *
            throw "Out of boundary!";
        }
        for (int i = 0 ; i < blockNum ; i ++) {
            if (sub < blocks[i]->GetInsNum()) {
                return blocks[i]->GetIns(i);
            }
            sub -= blocks[i]->GetInsNum();
        }
        //TODO: throw an exception instead of throw const char *
        throw "Unreachable!";
    }
    
    /**
     * @brief 获取基本块数量
     * 
     * @return 基本块数量
     */
    const int IRFunction::GetBlockNum() const {
        return blockNum;
    }
    
    /**
     * @brief 获取基本块
     * 
     * @param sub 下标
     * @return 基本块
     */
    const IRBasicBlock *IRFunction::GetBlock(int sub) const {
        if (sub < 0 || sub >= blockNum) {
            //TODO: throw an exception instead of throw const char *
            throw "Out of boundary!";
        }
        return blocks[sub];
    }
    
    /**
     * @brief 获取基本块
     * 
     * @param name 名称
     * @return 基本块
     */
    const IRBasicBlock *IRFunction::GetBlock(std::string name) const {
        for (int i = 0 ; i < blockNum ; i ++) {
            if (blocks[i]->GetName() == name) {
                return blocks[i];
            }
        }
        return NULL;
    }
    
    /**
     * @brief 获取函数声明
     * 
     * @return 函数声明
     */
    const IRFuncDecl IRFunction::GetDecl() const {
        return decl;
    }

    /**
     * @brief 打印
     * 
     * @param man 类型管理器
     * @param pool 操作数池
     * @param outs 输出流 
     */
    void IRFunction::PrintRawString(TypeManager &man, OperandPool &pool, std::ostream &outs) const {
        decl.PrintRawString(man, outs);
        outs << " {" << std::endl;
        for (int i = 0 ; i < blockNum ; i ++) {
            blocks[i]->PrintRawString(man, pool, outs);
        }
        outs << "}" << std::endl;
    }

//--------------------------------------

    /**
     * @brief IRFunctionBuilder构造函数
     * 
     */
    IRFunctionBuilder::IRFunctionBuilder() {
    }

    /**
     * @brief IRFunctionBuilder析构函数
     * 
     */
    IRFunctionBuilder::~IRFunctionBuilder() {
        for (IRBasicBlock *block : blocks) {
            delete block;
        }
        blocks.clear();
    }
    
    /**
     * @brief 获取函数声明
     * 
     * @param decl 函数声明
     * @return 函数声明
     */
    IRFuncDecl &IRFunctionBuilder::GetDecl() {
        return decl;
    }
    
    /**
     * @brief 获取基本块数量
     * 
     * @return 基本块数量
     */
    int IRFunctionBuilder::GetBlockNum() {
        return blocks.size();
    }
    
    /**
     * @brief 获取基本块
     * 
     * @param sub 下标
     * @return 基本块
     */
    IRBasicBlock *IRFunctionBuilder::GetBlock(int sub) {
        if (sub < 0 || sub >= (int)blocks.size()) {
            //TODO: throw an exception
            return NULL;
        }
        return blocks.at(sub);
    }
    
    /**
     * @brief 替换基本块
     * 
     * @param sub 下标
     * @param block 基本块
     * @return Builder自身
     */
    IRFunctionBuilder &IRFunctionBuilder::ReplaceBlock(int sub, IRBasicBlock *block) {
        delete blocks.at(sub);
        blocks.at(sub) = block;
        return *this;
    }
    
    /**
     * @brief 追加基本块
     * 
     * @param block 基本块
     * @return Builder自身
     */
    IRFunctionBuilder &IRFunctionBuilder::AppendBlock(IRBasicBlock *block) {
        blocks.push_back(block);
        return *this;
    }
    
    /**
     * @brief 构建IRFunction
     * 
     * @return IRFunction
     */
    IRFunction *IRFunctionBuilder::Build() {
        IRFunction *func = new IRFunction(blocks, decl);
        blocks.clear();
        return func;
    }

//--------------------------------------

    /**
     * 
     * @brief IRFuncDeclTab构造函数
     * 
     */
    IRFuncDeclTab::IRFuncDeclTab() {
    }

    /**
     * @brief 获取函数声明
     * 
     * @param name 函数名
     * @return 函数声明
     */
    const IRFuncDecl IRFuncDeclTab::GetFuncDecl(std::string name) const {
        if (declTab.count(name) == 0) {
            //TODO: throw an exception instead of const char *
            throw "don't exist key!";
        }
        return declTab.at(name);
    }

    /**
     * @brief 追加函数声明
     * 
     * @param decl 函数声明
     */
    void IRFuncDeclTab::AppendFuncDecl(IRFuncDecl decl) {
        declTab.insert(std::make_pair(decl.name, decl));
    }
}
/**
 * @file slice.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 代码切片
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <ir/ins.h>
#include <ir/type.h>

#include <vector>

namespace tayir {
    /**
     * @brief IR程序切片
     * 
     */
    class IRSlice {
    public:
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() const = 0;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins GetIns(int sub) const = 0;
    };

    /**
     * @brief IR片段
     * @see IRBasicBlock
     * 
     * 存储IR指令程序片段
     * 
     */
    class IRFragment: public IRSlice {
    protected:
        /** 指令数组 */
        Ins *instructions;
        /**
         * @brief IRFragment构造函数
         * 
         * @param insList 指令列表
         */
        IRFragment(std::vector<Ins> insList);
    public:
        /**
         * @brief IRFragment析构函数
         * 
         */
        virtual ~IRFragment();
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() const override;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins GetIns(int sub) const override;
        friend class IRFragmentBuilder;
    };

    /**
     * @brief IR片段Builder
     * @see IRFragmentBuilder
     * 
     */
    class IRFragmentBuilder {
    protected:
        /** 指令列表 */
        std::vector<Ins> instrutions;
    public:
        /**
         * @brief IRFragmentBuilder构造函数
         * 
         */
        IRFragmentBuilder();
        /**
         * @brief IRFragmentBuilder析构函数
         * 
         */
        ~IRFragmentBuilder();
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        const int GetInsNum() const;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        Ins &GetIns(int sub);
        /**
         * @brief 获取指令
         * 
         * @param ins 指令
         * @return Builder自身
         */
        IRFragmentBuilder &AppendIns(Ins *ins);
        /**
         * @brief 构造IRFragment
         * 
         * @return IRFragment
         */
        IRFragment *Build();
    };

    /**
     * @brief 参数
     * 
     * @see IRBasicBlock
     * @see IRFunction
     * 
     */
    class Argument {
    protected:
        /** 类型Id */
        const int typeId;
        /** 名称 */
        std::string name;
    public:
        /**
         * @brief Argument构造函数
         * 
         * @param typeId 类型ID
         * @param name 名称
         */
        Argument(const int typeId, std::string name);
        /**
         * @brief 获取类型ID
         * 
         * @return 类型ID
         */
        const int GetTypeId() const;
        /**
         * @brief 获取名称
         * 
         * @return 名称
         */
        std::string GetName() const;
    };

    /**
     * @brief IR基本块
     * 
     * @see IRFunction
     * 
     * IR程序基本块
     * 控制流基本跳转单位
     * 
     */
    class IRBasicBlock : public IRSlice {
    protected:
        /** IR片段 */
        IRFragment *frag;
        /** 偏移 */
        const int offset;
        /** 基本块参数表 */
        Argument *args;
        /**
         * @brief IRBasicBlock构造函数
         * 
         * @param frag 片段
         * @param offset 偏移
         * @param argList 参数列表
         */
        IRBasicBlock(IRFragment *frag, const int offset, std::vector<Argument> argList);
    public:
        /**
         * @brief IRBasicBlock析构函数
         * 
         */
        virtual ~IRBasicBlock();
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() const override;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins GetIns(int sub) const override;
        /**
         * @brief 获取参数
         * 
         * @param sub 下标
         * @return 参数
         */
        virtual const Argument GetArg(int sub);
        /**
         * @brief 获取偏移
         * 
         * @return 偏移
         */
        virtual const int GetOffset();
        friend class IRBasicBlockBuilder;
    };

    /**
     * @brief IR基本块Builder
     * 
     * @see IRBasicBlock
     * 
     */
    class IRBasicBlockBuilder {
    protected:
        /** 片段 */
        IRFragmentBuilder frag;
        /** 参数 */
        std::vector<Argument> args;
    public:
        /**
         * @brief IRBasicBlockBuilder构造函数
         * 
         */
        IRBasicBlockBuilder();
        /**
         * @brief IRBasicBlockBuilder析构函数
         * 
         */
        ~IRBasicBlockBuilder();
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        virtual int GetInsNum() const;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual Ins &GetIns(int sub);
        /**
         * @brief 获取指令
         * 
         * @param ins 指令
         * @return Builder自身
         */
        virtual IRBasicBlockBuilder &AppendIns(Ins ins);
        /**
         * @brief 获取参数
         * 
         * @param sub 下标
         * @return 参数
         */
        virtual Argument &GetArg(int sub);
        /**
         * @brief 追加参数
         * 
         * @param arg 参数
         * @return Builder自身
         */
        virtual IRBasicBlockBuilder &AppendArg(Argument *arg);
        /**
         * @brief 构建IR基本块
         * 
         * @param offset 偏移
         * @return IR基本块
         */
        virtual IRBasicBlock *Build(int offset);
    };

    /**
     * @brief IR函数声明
     * 
     * @see IRFunciton
     * 
     * IR函数声明
     * 
     */
    struct IRFuncDecl {
        /** 参数 */
        std::vector<Argument> args;
        /** 名称 */
        std::string name;
        /** 返回类型 */
        int returnTypeId;
        /** 调用约定 */
        int conventionId;
    };

    /**
     * @brief IR函数声明表
     * 
     * @see 存储已知的所有函数声明
     *  
     */
    class IRFuncDeclTab {
    protected:
        /** 声明表 */
        std::map<std::string, IRFuncDecl> declTab;
    public:
        /**
         * @brief IRFuncDeclTab构造函数
         * 
         */
        IRFuncDeclTab();
        /**
         * @brief 获取函数声明
         * 
         * @param name 函数名
         * @return 函数声明
         */
        const IRFuncDecl GetFuncDecl(std::string name) const;
        /**
         * @brief 追加函数声明
         * 
         * @param decl 函数声明
         */
        void AppendFuncDecl(IRFuncDecl decl);
    };

    /**
     * @brief IR函数
     * 
     * 程序接口的基本单位
     * 
     */
    class IRFunction : public IRSlice {
    protected:
        /** 函数声明 */
        const IRFuncDecl decl;
        /** 函数基本块表 */
        IRBasicBlock **blocks;
        /** 函数基本块数量 */
        int blockNum;
        /**
         * @brief IRFunction构造函数
         * 
         * @param frag 片段
         * @param offset 偏移
         * @param argList 参数列表
         */
        IRFunction(std::vector<IRBasicBlock *> blocks, IRFuncDecl decl);
    public:
        /**
         * @brief IRFunction析构函数
         * 
         */
        virtual ~IRFunction();
        /**
         * @brief 获取指令数量
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() const override;
        /**
         * @brief 获取指令
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins GetIns(int sub) const override;
        /**
         * @brief 获取基本块数量
         * 
         * @return 基本块数量
         */
        virtual const int GetBlockNum() const;
        /**
         * @brief 获取基本块
         * 
         * @param sub 下标
         * @return 基本块
         */
        virtual const IRBasicBlock *GetBlock(int sub) const;
        /**
         * @brief 获取基本块
         * 
         * @param name 名称
         * @return 基本块
         */
        virtual const IRBasicBlock *GetBlock(std::string name) const;
        /**
         * @brief 获取函数声明
         * 
         * @return 函数声明
         */
        const IRFuncDecl GetDecl() const;
    };
}
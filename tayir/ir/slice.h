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
         * @brief 获取Ins Num
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() = 0;
        /**
         * @brief 获取Ins
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins *GetIns(int sub) = 0;
    };

    /**
     * @brief IR片段
     * 
     */
    class IRFragment: public IRSlice {
    protected:
        /** 指令数组 */
        Ins **instructions;
        /**
         * @brief IRFragment构造函数
         * 
         * @param insList 指令列表
         */
        IRFragment(std::vector<Ins *> insList);
    public:
        /**
         * @brief IRFragment析构函数
         * 
         */
        virtual ~IRFragment();
        /**
         * @brief 获取Ins Num
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() override;
        /**
         * @brief 获取Ins
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins *GetIns(int sub) override;
        friend class IRFragmentBuilder;
    };

    /**
     * @brief IR片段Builder
     * 
     */
    class IRFragmentBuilder {
    protected:
        /** 指令列表 */
        std::vector<Ins *> instrutions;
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
         * @brief 获取Ins Num
         * 
         * @return 指令数量
         */
        int GetInsNum();
        /**
         * @brief 获取Ins
         * 
         * @param sub 下标
         * @return 指令
         */
        Ins *GetIns(int sub);
        /**
         * @brief 替换Ins
         * 
         * @param sub 下标
         * @param ins 指令
         * @return Builder
         */
        IRFragmentBuilder &ReplaceIns(int sub, Ins *ins);
        /**
         * @brief 追加Ins
         * 
         * @param ins 指令
         * @return Builder
         */
        IRFragmentBuilder &AppendIns(Ins *ins);
        /**
         * @brief 构造IRFragment
         * 
         * @return IRFragment
         */
        IRFragment *build();
    };

    /**
     * @brief 参数
     * 
     */
    class Argument {
    protected:
        /** 类型Id */
        const int typeId;
        /** 名称 */
        char *name;
    public:
        /**
         * @brief Argument构造函数
         * 
         * @param typeId 类型Id
         * @param name 名称
         */
        Argument(const int typeId, const char *name);
        /**
         * @brief Argument析构函数
         * 
         */
        ~Argument();
        /**
         * @brief 获取Type Id
         * 
         * @return 类型Id
         */
        const int GetTypeId();
        /**
         * @brief 获取Name
         * 
         * @return 名称
         */
        const char *GetName();
    };

    /**
     * @brief IR基本块Builder
     * 
     */
    class IRBasicBlock : public IRSlice {
    protected:
        /**
         * @brief IR片段
         * 
         */
        IRFragment *frag;
        /**
         * @brief 偏移
         * 
         */
        const int offset;
        /**
         * @brief 基本块参数表
         * 
         */
        Argument **args;
        /**
         * @brief IRBasicBlock构造函数
         * 
         * @param frag 片段
         * @param offset 偏移
         * @param argList 参数列表
         */
        IRBasicBlock(IRFragment *frag, const int offset, std::vector<Argument *> argList);
    public:
        /**
         * @brief IRBasicBlock析构函数
         * 
         */
        virtual ~IRBasicBlock();
        /**
         * @brief 获取Ins Num
         * 
         * @return 指令数量
         */
        virtual const int GetInsNum() override;
        /**
         * @brief 获取Ins
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual const Ins *GetIns(int sub) override;
        /**
         * @brief 获取Arg
         * 
         * @param sub 下标
         * @return 参数
         */
        virtual const Argument *GetArg(int sub);
        /**
         * @brief 获取Offset
         * 
         * @return 偏移
         */
        virtual const int GetOffset();
        friend class IRBasicBlockBuilder;
    };

    /**
     * @brief IR基本块Builder
     * 
     */
    class IRBasicBlockBuilder {
    protected:
        /**
         * @brief 片段
         * 
         */
        IRFragmentBuilder frag;
        /**
         * @brief 参数
         * 
         */
        std::vector<Argument*> args;
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
         * @brief 获取Ins Num
         * 
         * @return 指令数量
         */
        virtual int GetInsNum();
        /**
         * @brief 获取Ins
         * 
         * @param sub 下标
         * @return 指令
         */
        virtual Ins *GetIns(int sub);
        /**
         * @brief 替换Ins
         * 
         * @param sub 下标
         * @param ins 指令
         * @return Builder
         */
        virtual IRBasicBlockBuilder &ReplaceIns(int sub, Ins *ins);
        /**
         * @brief 追加Ins
         * 
         * @param ins 指令
         * @return Builder
         */
        virtual IRBasicBlockBuilder &AppendIns(Ins *ins);
        /**
         * @brief 获取Arg
         * 
         * @param sub 下标
         * @return 参数
         */
        virtual Argument *GetArg(int sub);
        /**
         * @brief 替换Arg
         * 
         * @param sub 下标
         * @param arg 参数
         * @return Builder
         */
        virtual IRBasicBlockBuilder &ReplaceArg(int sub, Argument *arg);
        /**
         * @brief 追加参数
         * 
         * @param arg 参数
         * @return Builder
         */
        virtual IRBasicBlockBuilder &AppendArg(Argument *arg);
        /**
         * @brief 构建IR基本块
         * 
         * @param offset 偏移
         * @return IR基本块
         */
        virtual IRBasicBlock *build(int offset);
    };

    /**
     * @brief IR函数
     * 
     */
    class IRFunction : public IRSlice {
    };

    /**
     * @brief IR函数声明表
     * 
     */
    class IRFuncDeclTab {
    };

    /**
     * @brief IR程序
     * 
     */
    class IRProgram : public IRSlice {
    };
}
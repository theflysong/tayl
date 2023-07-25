/**
 * @file ins.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 指令
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <ir/operand.h>
#include <vector>

namespace tayir {
    /**
     * @brief 指令类型
     * @see Ins
     * 
     */
    enum class InsType {
        /** 空 */
        NOP = 0,
        /** 加 */
        ADD = 1,
        /** 减 */
        SUB = 2,
        /** 乘 */
        MUL = 3,
        /** 除 */
        DIV = 4,
        /** 取余 */
        REM = 5,
        /** 返回 */
        RET = 6,
        /** 调用 */
        CALL = 7,
        /** 分配 */
        ALLOC = 8,
        /** 加载 */
        LOAD = 9,
        /** 存储 */
        STORE = 10,
        /** 分支 */
        BR = 11,
        /** 跳转 */
        GOTO = 12,
        /** 等于 */
        EQU = 13,
        /** 不等于 */
        NEQ = 14,
        /** 大于 */
        GT = 15,
        /** 小于 */
        LT = 16,
        /** 大于等于 */
        GTE = 17,
        /** 小于等于 */
        LTE = 18,
        /** 取非 */
        NOT = 19,
        /** 取负 */
        NEG = 20,
        /** 取反 */
        INV = 21
    };

    /**
     * @brief 指令类型转字符串
     * 
     * @param insType 指令类型
     * @return 字符串
     */
    const char *ToString(InsType insType);

    /**
     * @brief 指令
     * 
     * IR程序执行/存储/翻译的基本单位
     * 
     * 形式为
     * 
     * destOp = ins src1Op, src2Op
     * 
     * 特殊形式为
     * 
     * br cond, if, else
     * 
     * SSA 不可重复赋值
     * 
     */
    class Ins {
    protected:
        /** 指令类型 */
        InsType type;
        /** 目的数 & 条件 */
        int destOp;
        /** 操作数1 & 如果 */
        int src1Op;
        /** 操作数2 & 否则 */
        int src2Op;
    public:
        /**
         * @brief Ins构造函数
         * 
         * 构造NOP指令
         * 
         */
        Ins();
        /**
         * @brief Ins构造函数
         * 
         * @param type 指令类型
         * @param destOp 目的数 & 条件
         * @param srcOp 操作数1 & 跳转
         */
        Ins(const InsType type, int destOp, int srcOp);
        /**
         * @brief Ins构造函数
         * 
         * @param type 指令类型
         * @param destOp 目的数 & 条件
         * @param src1Op 操作数1 & 如果
         * @param src2Op 操作数2 & 否则
         */
        Ins(const InsType type, int destOp, int src1Op, int src2Op);
        /**
         * @brief 获取指令类型
         * 
         * @return 指令类型
         */
        const InsType GetInsType() const;
        /**
         * @brief 获取目的数
         * 
         * @return 目的数
         */
        const int GetDestOp() const;
        /**
         * @brief 获取操作数1
         * 
         * @return 操作数1
         */
        const int GetSrc1Op() const;
        /**
         * @brief 获取操作数2
         * 
         * @return 操作数2
         */
        const int GetSrc2Op() const;
        /**
         * @brief 获取如果
         * 
         * @return 如果
         */
        const int GetCondOp() const;
        /**
         * @brief 获取如果
         * 
         * @return 如果
         */
        const int GetIfOp() const;
        /**
         * @brief 获取否则
         * 
         * @return 否则
         */
        const int GetElseOp() const;
        /**
         * @brief 打印
         * 
         * @param pool 参数池
         * @param outs 输出流 
         */
        void PrintRawString(OperandPool &pool, std::ostream &outs) const;
    };
}
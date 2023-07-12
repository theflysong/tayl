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
        RET = 6
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
     * destOp = type src1Op, src2Op
     * 
     * SSA 不可重复赋值
     * 
     */
    class Ins {
    protected:
        /**
         * @brief 指令类型
         * 
         */
        InsType type;
        /**
         * @brief 目的数
         * 
         */
        Operand destOp;
        /**
         * @brief 操作数1
         * 
         */
        Operand src1Op;
        /**
         * @brief 操作数2
         * 
         */
        Operand src2Op;
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
         * @param destOp 目的数
         * @param src1Op 操作数1
         * @param src2Op 操作数2
         */
        Ins(const InsType type, Operand destOp, Operand src1Op, Operand src2Op);
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
        const Operand GetDestOp() const;
        /**
         * @brief 获取操作数1
         * 
         * @return 操作数1
         */
        const Operand GetSrc1Op() const;
        /**
         * @brief 获取操作数2
         * 
         * @return 操作数2
         */
        const Operand GetSrc2Op() const;
    };
}
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
     * @see tayir::Ins
     * 
     */
    enum class InsType {
        /** 加 */
        ADD = 0,
        /** 减 */
        SUB,
        /** 乘 */
        MUL,
        /** 除 */
        DIV,
        /** 取余 */
        REM,
        /** 返回 */
        RET
    };

    /**
     * @brief 指令
     * 
     */
    class Ins {
    protected:
        /**
         * @brief 指令类型
         * 
         */
        const InsType type;
        /**
         * @brief 目的数
         * 
         */
        const Operand destOp;
        /**
         * @brief 操作数1
         * 
         */
        const Operand src1Op;
        /**
         * @brief 操作数2
         * 
         */
        const Operand src2Op;
    public:
        /**
         * @brief Ins构造函数
         * 
         * @param type 指令类型
         * @param destOp 目的数
         * @param src1Op 操作数1
         * @param src2Op 操作数2
         */
        Ins(const InsType type, Operand&& destOp, Operand&& src1Op, Operand&& src2Op);
        /**
         * @brief Ins析构函数
         * 
         */
        virtual ~Ins();
        /**
         * @brief 获取Ins Type
         * 
         * @return Ins Type
         */
        const InsType GetInsType();
    };
}
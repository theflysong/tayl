/**
 * @file operand.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 操作数
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <string>

namespace tayir {
    /**
     * @enum tayir::OperandType
     * @brief 操作数类型
     * @see tayir::Operand
     * 
     */
    enum class OperandType {
        /** SSA值 */
        SSA_VALUE = 0,
        /** 符号 */
        LABEL     = 1,
        /** 常量 */
        CONSTANT  = 2,
        /** 空 */
        EMPTY = 3
    };    
    
    /**
     * @brief 操作数位置
     * @see tayir::Operand
     * 
     */
    enum class OperandPos {
        /** 目的 */
        DEST = 0,
        /** 源1 */
        SRC1 = 1,
        /** 源2 */
        SRC2 = 2,
        /** 长度指示 */
        SIZE = 3
    };

    /**
     * @brief 操作数
     * @see tayir::Ins
     * 
     */
    class Operand {
    protected:
        /** 操作数类型 */
        const OperandType type;
        /** 操作数位置 */
        const OperandPos pos;
        /** 操作数值*/
        std::string value;
    public:
        /**
         * @brief Operand构造函数
         * 
         * @param type 操作数类型
         * @param pos 操作数位置
         * @param value 操作数值
         */
        Operand(const OperandType type, const OperandPos pos, std::string value);
        /**
         * @brief 获取Operand Type
         * 
         * @return Operand Type
         */
        const OperandType GetOperandType();
        /**
         * @brief 获取Operand Pos
         * 
         * @return Operand Pos
         */
        const OperandPos GetOperandPos();
        /**
         * @brief 获取Operand Value
         * 
         * @return Operand Value
         */
        std::string GetOperandValue();
    };
}
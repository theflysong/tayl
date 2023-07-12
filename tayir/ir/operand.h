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
     * @brief 操作数类型
     * @see Operand
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
     * @see Operand
     * 
     */
    enum class OperandPos {
        /** 目的 */
        DEST = 0,
        /** 源1 */
        SRC1 = 1,
        /** 源2 */
        SRC2 = 2,
        /** 参数 */
        ARGUMENT = 3
    };

    /**
     * @brief 操作数
     * @see Ins
     * 
     */
    class Operand {
    protected:
        /** 操作数类型 */
        OperandType type;
        /** 操作数位置 */
        OperandPos pos;
        /** 操作数值*/
        std::string value;
    public:
        /**
         * @brief Operand构造函数
         * 
         * 空Operand
         * 
         */
        Operand(const OperandPos pos);
        /**
         * @brief Operand构造函数
         * 
         * @param type 操作数类型
         * @param pos 操作数位置
         * @param value 操作数值
         */
        Operand(const OperandType type, const OperandPos pos, std::string value);
        /**
         * @brief 获取操作数类型
         * 
         * @return 操作数类型
         */
        const OperandType GetOperandType() const;
        /**
         * @brief 获取操作数位置
         * 
         * @return 操作数位置
         */
        const OperandPos GetOperandPos() const;
        /**
         * @brief 获取操作数值
         * 
         * @return 操作数值
         */
        std::string GetOperandValue() const;
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
        int typeId;
        /** 名称 */
        std::string name;
    public:
        /**
         * @brief Argument构造函数
         * 
         * 空Argument
         * 
         */
        Argument();
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
}
/**
 * @file operand.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <ir/operand.h>
#include <cstring>

namespace tayir {
    /**
     * @brief Operand构造函数
     * 
     * @param type 操作数类型
     * @param pos 操作数位置
     * @param value 操作数值
     */
    Operand::Operand(const OperandType type, const OperandPos pos, std::string value) 
        : type(type), pos(pos), value(value)
    {
        if (type == OperandType::EMPTY) {
            this->value = "";
        }
    }

    /**
     * @brief 获取Operand Type
     * 
     * @return Operand Type
     */
    const OperandType Operand::GetOperandType() {
        return type;
    }

    /**
     * @brief 获取Operand Pos
     * 
     * @return Operand Pos
     */
    const OperandPos Operand::GetOperandPos() {
        return pos;
    }

    /**
     * @brief 获取Operand Value
     * 
     * @return Operand Value
     */
    std::string Operand::GetOperandValue() {
        return value;
    }
}
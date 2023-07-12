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
     * @brief 获取操作数类型
     * 
     * @return 操作数类型
     */
    const OperandType Operand::GetOperandType() {
        return type;
    }

    /**
     * @brief 获取操作数位置
     * 
     * @return 操作数位置
     */
    const OperandPos Operand::GetOperandPos() {
        return pos;
    }

    /**
     * @brief 获取操作数值
     * 
     * @return 操作数值
     */
    std::string Operand::GetOperandValue() {
        return value;
    }
}
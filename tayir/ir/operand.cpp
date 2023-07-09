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
     * @param op 操作数左值
     */
    Operand::Operand(Operand &op) 
        : type(op.type), pos(op.pos)
    {
        if (op.type == OperandType::EMPTY) {
            this->value = NULL;
            return;
        }

        this->value = new char[strlen(op.value) + 1];
        strcpy(this->value, op.value);
    }

    /**
     * @brief Operand构造函数
     * 
     * @param op 操作数右值
     */
    Operand::Operand(Operand &&op)
        : type(op.type), pos(op.pos)
    {
        this->value = op.value;
        op.value = NULL;
    }   

    /**
     * @brief Operand构造函数
     * 
     * @param type 操作数类型
     * @param pos 操作数位置
     * @param value 操作数值
     */
    Operand::Operand(const OperandType type, const OperandPos pos, const char *value) 
        : type(type), pos(pos)
    {
        if (type == OperandType::EMPTY) {
            this->value = NULL;
            return;
        }

        this->value = new char[strlen(value) + 1];
        strcpy(this->value, value);
    }

    /**
     * @brief Operand析构函数
     * 
     */
    Operand::~Operand() {
        if (value != NULL) {
            delete[] value;
            value = NULL;
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
    const char *Operand::GetOperandValue() {
        return value;
    }
}
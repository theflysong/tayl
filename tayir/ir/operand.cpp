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
//---------------------------------------------------------
//|                                                       |
//|                        operand                        |
//|                                                       |
//---------------------------------------------------------
    /**
     * @brief Operand构造函数
     * 
     * @param type 操作数类型
     * @param pos 操作数位置
     */
    OperandBase::OperandBase(const OperandType type, const OperandPos pos) 
        : type(type), pos(pos)
    {
    }

    /**
     * @brief 获取操作数类型
     * 
     * @return 操作数类型
     */
    const OperandType OperandBase::GetOperandType() const {
        return type;
    }

    /**
     * @brief 获取操作数位置
     * 
     * @return 操作数位置
     */
    const OperandPos OperandBase::GetOperandPos() const {
        return pos;
    }

    /**
     * @brief 空操作数构造函数
     * 
     * @param pos 操作数位置
     * 
     */
    EmptyOperand::EmptyOperand(const OperandPos pos)
        : OperandBase(OperandType::EMPTY, pos) 
    {
    }

    /**
     * @brief 操作数转字符串
     * 
     * @return 字符串
     */
    std::string EmptyOperand::ToString() const {
        return "";
    }

    /**
     * @brief 零操作数构造函数
     * 
     * @param pos 操作数位置
     * 
     */
    ZeroOperand::ZeroOperand(const OperandPos pos)
        : OperandBase(OperandType::IMMEDIATE, pos) 
    {
    }

    /**
     * @brief 操作数转字符串
     * 
     * @return 字符串
     */
    std::string ZeroOperand::ToString() const {
        return "0";
    }

    /**
     * @brief 一操作数构造函数
     * 
     * @param pos 操作数位置
     * 
     */
    OneOperand::OneOperand(const OperandPos pos)
        : OperandBase(OperandType::IMMEDIATE, pos) 
    {
    }

    /**
     * @brief 操作数转字符串
     * 
     * @return 字符串
     */
    std::string OneOperand::ToString() const {
        return "1";
    }

    /**
     * @brief 空指针操作数构造函数
     * 
     * @param pos 操作数位置
     * 
     */
    NullOperand::NullOperand(const OperandPos pos)
        : OperandBase(OperandType::IMMEDIATE, pos) 
    {
    }

    /**
     * @brief 操作数转字符串
     * 
     * @return 字符串
     */
    std::string NullOperand::ToString() const {
        return "null";
    }

    /**
     * @brief 立即数操作数构造函数
     * 
     * @param pos 操作数位置
     * @param type 立即数类型
     * @param value 立即数值
     * 
     */
    ImmediateOperand::ImmediateOperand(const OperandPos pos, const imm::itype type, const ImmediateValue value) 
        : OperandBase(OperandType::IMMEDIATE, pos), type(type), value(value)
    {
    }

    /**
     * @brief 获取立即数值
     * 
     * @return 立即数值
     */
    const ImmediateValue ImmediateOperand::GetValue() const {
        return value;
    }
    /**
     * @brief 获取立即数类型
     * 
     * @return 立即数类型
     */
    const imm::itype ImmediateOperand::GetType() const {
        return type;
    }
    /**
     * @brief 操作数转字符串
     * 
     * @return 字符串
     */
    std::string ImmediateOperand::ToString() const {
        std::stringstream ss;
        switch(type) {
        case imm::itype::I8: {
            // 字符
            ss << "'" << (char)value.i8Val << "'";
            return ss.str();
        }
        case imm::itype::I16: {
            // 有符号16位数
            ss << (short)value.i16Val;
            return ss.str();
        }
        case imm::itype::I32: {
            // 有符号32位数
            ss << (int)value.i32Val;
            return ss.str();
        }
        case imm::itype::I64: {
            // 有符号64位数
            ss << (long long)value.i64Val;
            return ss.str();
        }
        case imm::itype::UI8:
        case imm::itype::UI16:
        case imm::itype::UI32: 
        case imm::itype::UI64: {
            // 无符号数
            ss << (unsigned long long)value.ui64Val;
            return ss.str();
        }
        case imm::itype::P16:
        case imm::itype::P32:
        case imm::itype::P64: {
            // 指针
            ss << (void *)value.p64Val;
            return ss.str();
        }
        case imm::itype::FLOAT: {
            // 单精度浮点数
            ss << (float)value.floatVal << "f";
            return ss.str();
        }
        case imm::itype::DOUBLE: {
            // 单精度浮点数
            ss << (double)value.doubleVal;
            return ss.str();
        }
        case imm::itype::BOOL: {
            // 单精度浮点数
            ss << (value.boolVal ? "true" : "false");
            return ss.str();
        }
        }
        return "error!";
    }

//---------------------------------------------------------
//|                                                       |
//|                       argument                        |
//|                                                       |
//---------------------------------------------------------
    /**
     * @brief Argument构造函数
     * 
     * 空Argument
     * 
     */
    Argument::Argument()
        : typeId(-1), name("")
    {
    }

    /**
     * @brief Argument构造函数
     * 
     * @param typeId 类型ID
     * @param name 名称
     */
    Argument::Argument(const int typeId, std::string name) 
        : typeId(typeId), name(name)
    {
    }
    
    /**
     * @brief 获取类型ID
     * 
     * @return 类型ID
     */
    const int Argument::GetTypeId() const {
        return typeId;
    }
    /**
     * @brief 获取名称
     * 
     * @return 名称
     */
    std::string Argument::GetName() const {
        return name;
    }
}
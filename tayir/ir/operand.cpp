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
     */
    OperandBase::OperandBase(const OperandType type) 
        : type(type)
    {
    }

    /**
     * @brief 操作数析构函数
     * 
     */
    OperandBase::~OperandBase() {
    }

    /**
     * @brief 获取操作数类型
     * 
     * @return 操作数类型
     */
    const OperandType OperandBase::GetOperandType() const {
        return type;
    }

//----------------------

    /**
     * @brief 空操作数构造函数
     * 
     * @param pos 操作数位置
     * 
     */
    EmptyOperand::EmptyOperand()
        : OperandBase(OperandType::EMPTY) 
    {
    }

    /**
     * @brief 操作数转字符串
     * 
     * @param pool 操作数池
     * 
     * @return 字符串
     */
    std::string EmptyOperand::ToString(OperandPool &pool) const {
        return "";
    }

//----------------------

    /**
     * @brief 立即数操作数构造函数
     * 
     * @param type 立即数类型
     * @param value 立即数值
     * 
     */
    ImmediateOperand::ImmediateOperand(const imm::itype type, const ImmediateValue value) 
        : OperandBase(OperandType::IMMEDIATE), type(type), value(value)
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
     * @param pool 操作数池
     * 
     * @return 字符串
     */
    std::string ImmediateOperand::ToString(OperandPool &pool) const {
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
        case imm::itype::UI8: {
            // 无符号数
            ss << (unsigned long long)(value.ui64Val & 0xFF);
            return ss.str();
        }
        case imm::itype::UI16: {
            // 无符号数
            ss << (unsigned long long)(value.ui64Val & 0xFFFF);
            return ss.str();
        }
        case imm::itype::UI32:  {
            // 无符号数
            ss << (unsigned long long)(value.ui64Val & 0xFFFFFFFF);
            return ss.str();
        }
        case imm::itype::UI64: {
            // 无符号数
            ss << (unsigned long long)(value.ui64Val);
            return ss.str();
        }
        case imm::itype::P16:
        case imm::itype::P32:
        case imm::itype::P64: {
            // 指针
            if ((void *)value.p64Val == NULL) {
                ss << "null";
            }
            else {
                ss << (void *)value.p64Val;
            }
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

//----------------------

    /**
     * @brief 符号操作数构造函数
     * 
     * @param scope 符号范围
     * @param name 符号名称
     */
    SymbolOperand::SymbolOperand(const SymbolScope scope, std::string name)
        : OperandBase(OperandType::SYMBOL), scope(scope), name(name)
    {
    }

    /**
     * @brief 获取符号范围
     * 
     * @return 符号范围
     */
    const SymbolScope SymbolOperand::GetScope() const {
        return scope;
    }

    /**
     * @brief 获取符号名称
     * 
     * @return 符号名称
     */
    const std::string SymbolOperand::GetName() const {
        return name;
    }

    /**
     * @brief 操作数转字符串
     * 
     * @param pool 操作数池
     * 
     * @return 字符串
     */
    std::string SymbolOperand::ToString(OperandPool &pool) const {
        std::string str;
        if (scope == SymbolScope::GLOBAL) {
            str = "@";
        }
        else {
            str = "%";
        }
        return str + name;
    }

//----------------------

    /**
     * @brief 标号操作数构造函数
     * 
     * @param name 标号名称
     */
    LabelOperand::LabelOperand(std::string name)
        : OperandBase(OperandType::LABEL), name(name)
    {
    }

    /**
     * @brief 获取标号名称
     * 
     * @return 标号名称
     */
    const std::string LabelOperand::GetName() const {
        return name;
    }

    /**
     * @brief 操作数转字符串
     * 
     * @param pool 操作数池
     * 
     * @return 字符串
     */
    std::string LabelOperand::ToString(OperandPool &pool) const {
        return name;
    }

//----------------------

    /**
     * @brief 参数列表操作数构造函数
     * 
     * @param name 标号名称
     */
    ArgListOperand::ArgListOperand(std::vector<int> argList)
        : OperandBase(OperandType::ARGLIST), argList(argList)
    {
    }

    /**
     * @brief 获取标号名称
     * 
     * @return 标号名称
     */
    const std::vector<int> ArgListOperand::GetArgList() {
        return argList;
    }

    /**
     * @brief 操作数转字符串
     * 
     * @param pool 操作数池
     * 
     * @return 字符串
     */
    std::string ArgListOperand::ToString(OperandPool &pool) const {
        std::stringstream ss;
        ss << "[";
        if (argList.size() >= 1) {
            ss << pool.GetOperand(argList.at(0))->ToString(pool);
            for (int i = 1 ; i < (int)argList.size() ; i ++) {
                ss << ", " << pool.GetOperand(argList.at(i))->ToString(pool);
            }
        }
        ss << "]";
        return ss.str();
    }

//----------------------

    /**
     * @brief 操作数池构造函数
     * 
     */
    OperandPool::OperandPool() {
    }

    /**
     * @brief 操作数池析构函数
     * 
     */
    OperandPool::~OperandPool() {
        for (auto op : operands) {
            delete op;
        }
        operands.clear();
    }

    /**
     * @brief 获取操作数
     * 
     * @param id 操作数ID
     * @return 操作数
     */
    OperandBase *OperandPool::GetOperand(int id) {
        return operands.at(id);
    }
    
    /**
     * @brief 追加操作数
     * 
     * @param operand 操作数
     * @return 操作数ID
     */
    int OperandPool::AppendOperand(OperandBase *operand) {
        int id = operands.size();
        operands.push_back(operand);
        return id;
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
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
     * 空Operand
     * 
     */
    Operand::Operand(const OperandPos pos)
        : type(OperandType::EMPTY), pos(pos), value("")
    {
    }

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
    const OperandType Operand::GetOperandType() const {
        return type;
    }

    /**
     * @brief 获取操作数位置
     * 
     * @return 操作数位置
     */
    const OperandPos Operand::GetOperandPos() const {
        return pos;
    }

    /**
     * @brief 获取操作数值
     * 
     * @return 操作数值
     */
    std::string Operand::GetOperandValue() const {
        return value;
    }

//---------------------------------------------------------
//|                                                       |
//|                       argument                        |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief 参数池构造函数
     * 
     */
    ArgOpPool::ArgOpPool() {
    }

    /**
     * @brief 获取参数
     * 
     * @param id 参数ID
     * @return 参数
     */
    std::vector<Operand> ArgOpPool::GetArg(int id) {
        if (id < 0 || id >= (int)args.size()) {
            //TODO: throw an exception instead of const char *
            throw "Out of boundary!";
        }
        return args.at(id);
    }

    /**
     * @brief 追加参数
     * 
     * @param arg 参数
     * @return 参数ID
     */
    int ArgOpPool::AppendArg(std::vector<Operand> arg) {
        args.push_back(arg);
        return args.size() - 1;
    }

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
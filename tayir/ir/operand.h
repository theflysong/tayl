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
#include <sstream>
#include <vector>

#include <ir/type.h>

namespace tayir {
    /**
     * @brief 操作数类型
     * @see Operand
     * 
     */
    enum class OperandType {
        /** 空 */
        EMPTY = 0,
        /** SSA值 */
        SSA_VALUE = 1,
        /** 符号 */
        LABEL     = 2,
        /** 常量 */
        IMMEDIATE  = 3,
        /** 类型 */
        TYPE  = 4
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
        /** 源3 */
        SRC3 = 3
    };

    /**
     * @brief 操作数基类
     * @see Ins
     * 
     */
    class OperandBase {
    protected:
        /** 操作数类型 */
        const OperandType type;
        /** 操作数位置 */
        const OperandPos pos;
    public:
        /**
         * @brief Operand构造函数
         * 
         * @param type 操作数类型
         * @param pos 操作数位置
         */
        OperandBase(const OperandType type, const OperandPos pos);
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
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const = 0;
    };

    /**
     * @brief 空操作数
     * @see OperandBase
     * 
     */
    class EmptyOperand : public OperandBase{
    public:
        /**
         * @brief 空操作数构造函数
         * 
         * @param pos 操作数位置
         * 
         */
        EmptyOperand(const OperandPos pos);
        /**
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const override final;
    };

    /**
     * @brief 零操作数
     * @see OperandBase
     * 
     */
    class ZeroOperand : public OperandBase{
    public:
        /**
         * @brief 零操作数构造函数
         * 
         * @param pos 操作数位置
         * 
         */
        ZeroOperand(const OperandPos pos);
        /**
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const override final;
    };

    /**
     * @brief 一操作数
     * @see OperandBase
     * 
     */
    class OneOperand : public OperandBase{
    public:
        /**
         * @brief 一操作数构造函数
         * 
         * @param pos 操作数位置
         * 
         */
        OneOperand(const OperandPos pos);
        /**
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const override final;
    };
    
    /**
     * @brief 空指针操作数
     * @see OperandBase
     * 
     */
    class NullOperand : public OperandBase{
    public:
        /**
         * @brief 空指针操作数构造函数
         * 
         * @param pos 操作数位置
         * 
         */
        NullOperand(const OperandPos pos);
        /**
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const override final;
    };

    /**
     * @brief 立即数
     * @see ImmediateOperand
     * 
     */
    union ImmediateValue {
        /** i8 value */
        imm::i8_t i8Val;
        /** i16 value */
        imm::i16_t i16Val;
        /** i32 value */
        imm::i32_t i32Val;
        /** i64 value */
        imm::i64_t i64Val;

        /** ui8 value */
        imm::ui8_t ui8Val;
        /** ui16 value */
        imm::ui16_t ui16Val;
        /** ui32 value */
        imm::ui32_t ui32Val;
        /** ui64 value */
        imm::ui64_t ui64Val;

        /** p16 value */
        imm::p16_t p16Val;
        /** p32 value */
        imm::p32_t p32Val;
        /** p64 value */
        imm::p64_t p64Val;

        /** float value */
        imm::float_t floatVal;
        /** double value */
        imm::double_t doubleVal;
        /** bool value */
        imm::bool_t boolVal;
    };

    /**
     * @brief 立即数操作数
     * @see OperandBase
     * 
     */
    class ImmediateOperand : public OperandBase {
    protected:
        /** 立即数类型 */
        imm::itype type;
        /** 立即数值 */
        ImmediateValue value;
    public:
        /**
         * @brief 立即数操作数构造函数
         * 
         * @param pos 操作数位置
         * @param type 立即数类型
         * @param value 立即数值
         * 
         */
        ImmediateOperand(const OperandPos pos, const imm::itype type, const ImmediateValue value);
        /**
         * @brief 获取立即数值
         * 
         * @return 立即数值
         */
        const ImmediateValue GetValue() const;
        /**
         * @brief 获取立即数类型
         * 
         * @return 立即数类型
         */
        const imm::itype GetType() const;
        /**
         * @brief 操作数转字符串
         * 
         * @return 字符串
         */
        virtual std::string ToString() const override final;
    };

    /**
     * @brief 操作数池
     * 
     */
    class OperandPool {
    protected:
        /** 操作数列表 */
        std::vector<OperandBase *> operands;
    public:
        /**
         * @brief 操作数池构造函数
         * 
         */
        OperandPool();
        /**
         * @brief 获取操作数
         * 
         * @param id 操作数ID
         * @return 操作数
         */
        OperandBase * GetOperand(int id);
        /**
         * @brief 追加操作数
         * 
         * @param operand 操作数
         * @return 操作数ID
         */
        int AppendOperand(OperandBase *operand);
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
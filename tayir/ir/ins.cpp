/**
 * @file ins.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief cpp
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <ir/ins.h>

#include <cstring>

namespace tayir {
    /**
     * @brief 指令类型转字符串
     * 
     * @param insType 指令类型
     * @return 字符串
     */
    const char *ToString(InsType insType) {
        switch(insType) {
        case InsType::NOP:   return "nop";
        case InsType::ADD:   return "add";
        case InsType::SUB:   return "sub";
        case InsType::MUL:   return "mul";
        case InsType::DIV:   return "div";
        case InsType::REM:   return "rem";
        case InsType::RET:   return "ret";
        case InsType::CALL:  return "call";
        case InsType::ALLOC: return "alloc";
        case InsType::LOAD:  return "load";
        case InsType::STORE: return "store";
        case InsType::BR:    return "br";
        case InsType::GOTO:  return "goto";
        case InsType::GT:    return "gt";
        case InsType::LT:    return "lt";
        case InsType::GTE:   return "gte";
        case InsType::LTE:   return "lte";
        case InsType::NOT:   return "not";
        case InsType::NEG:   return "neg";
        case InsType::INV:   return "inv";
        default: return "error!";
        }
    }

    /**
     * @brief Ins构造函数
     * 
     * 构造NOP指令
     * 
     */
    Ins::Ins()
        : type(InsType::NOP), destOp(-1), src1Op(-1), src2Op(-1)
    {
    }

    /**
     * @brief Ins构造函数
     * 
     * @param type 指令类型
     * @param destOp 目的数 & 条件
     * @param srcOp 操作数1 & 跳转
     */
    Ins::Ins(const InsType type, int destOp, int srcOp)
        : type(type), destOp(destOp), src1Op(srcOp), src2Op(-1)
    {
    }

    /**
     * @brief Ins构造函数
     * 
     * @param type 指令类型
     * @param destOp 目的数 & 条件
     * @param src1Op 操作数1 & 如果
     * @param src2Op 操作数2 & 否则
     */
    Ins::Ins(const InsType type, int destOp, int src1Op, int src2Op)
        : type(type), destOp(destOp), src1Op(src1Op), src2Op(src2Op)
    {
    }

    /**
     * @brief 获取指令类型
     * 
     * @return 指令类型
     */
    const InsType Ins::GetInsType() const {
        return type;
    }

    /**
     * @brief 获取目的数
     * 
     * @return 目的数
     */
    const int Ins::GetDestOp() const {
        return destOp;
    }

    /**
     * @brief 获取操作数1
     * 
     * @return 操作数1
     */
    const int Ins::GetSrc1Op() const {
        return src1Op;
    }

    /**
     * @brief 获取操作数2
     * 
     * @return 操作数2
     */
    const int Ins::GetSrc2Op() const {
        return src2Op;
    }

    /**
     * @brief 获取如果
     * 
     * @return 如果
     */
    const int Ins::GetCondOp() const {
        return destOp;
    }

    /**
     * @brief 获取如果
     * 
     * @return 如果
     */
    const int Ins::GetIfOp() const {
        return src1Op;
    }

    /**
     * @brief 获取否则
     * 
     * @return 否则
     */
    const int Ins::GetElseOp() const {
        return src2Op;
    }

    /**
     * @brief 打印
     * 
     * @param pool 参数池
     * @param outs 输出流 
     */
    void Ins::PrintRawString(OperandPool &pool, std::ostream &outs) const {
        // 特殊: BR指令
        if (type == InsType::BR) {
            outs << ToString(type);
            if (destOp != -1) {
                outs << " " << pool.GetOperand(destOp)->ToString(pool);
            }
            if (src1Op != -1) {
                outs << ", " << pool.GetOperand(src1Op)->ToString(pool);
            }
            if (src2Op != -1) {
                outs << ", " << pool.GetOperand(src2Op)->ToString(pool);
            }
        }
        else {
            if (destOp != -1) {
                outs << pool.GetOperand(destOp)->ToString(pool) << " = ";
            }
            outs << ToString(type);
            if (src1Op != -1) {
                outs << " " << pool.GetOperand(src1Op)->ToString(pool);
            }
            if (src2Op != -1) {
                outs << ", " << pool.GetOperand(src2Op)->ToString(pool);
            }
        }
    }
}
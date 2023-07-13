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
        : type(InsType::NOP), destOp(OperandPos::DEST), src1Op(OperandPos::SRC1), src2Op(OperandPos::SRC2), argOpId(-1)
    {
    }

    /**
     * @brief Ins构造函数
     * 
     * @param type 指令类型
     * @param destOp 目的数
     * @param src1Op 操作数1
     * @param src2Op 操作数2
     */
    Ins::Ins(const InsType type, Operand destOp, Operand src1Op, Operand src2Op, int argOpId) 
        : type(type), destOp(destOp), src1Op(src1Op), src2Op(src2Op), argOpId(argOpId)
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
    const Operand Ins::GetDestOp() const {
        return destOp;
    }

    /**
     * @brief 获取操作数1
     * 
     * @return 操作数1
     */
    const Operand Ins::GetSrc1Op() const {
        return src1Op;
    }
    
    /**
     * @brief 获取操作数2
     * 
     * @return 操作数2
     */
    const Operand Ins::GetSrc2Op() const {
        return src2Op;
    }

    /**
     * @brief 打印
     * 
     * @param pool 参数池
     * @param outs 输出流 
     */
    void Ins::PrintRawString(ArgOpPool &pool, std::ostream &outs) const {
        if (destOp.GetOperandType() != OperandType::EMPTY) {
            outs << destOp.GetOperandValue() << " = ";
        }
        outs << tayir::ToString(type) << " ";
        if (src1Op.GetOperandType() != OperandType::EMPTY) {
            outs << src1Op.GetOperandValue();
        }
        if (src2Op.GetOperandType() != OperandType::EMPTY) {
            outs << ", " << src2Op.GetOperandValue();
        }

        if (argOpId != -1) {
            std::vector<Operand> args = pool.GetArg(argOpId);
            Operand firstArg = args.at(0);
            outs << ", [" << firstArg.GetOperandValue();
            for (int i = 1 ; i < (int)args.size() ; i ++) {
                outs << ", " << args.at(i).GetOperandValue();
            }
            outs << "]";
        }
    }
}
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
        case InsType::NOP: return "nop";
        case InsType::ADD: return "add";
        case InsType::SUB: return "sub";
        case InsType::MUL: return "mul";
        case InsType::DIV: return "div";
        case InsType::REM: return "rem";
        case InsType::RET: return "ret";
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
        : type(InsType::NOP), destOp(OperandPos::DEST), src1Op(OperandPos::SRC1), src2Op(OperandPos::SRC2)
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
    Ins::Ins(const InsType type, Operand destOp, Operand src1Op, Operand src2Op) 
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
}
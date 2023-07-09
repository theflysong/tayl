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
     * @brief Ins构造函数
     * 
     * @param type 指令类型
     * @param destOp 目的数
     * @param src1Op 操作数1
     * @param src2Op 操作数2
     */
    Ins::Ins(const InsType type, Operand&& destOp, Operand&& src1Op, Operand&& src2Op) 
        : type(type), destOp(destOp), src1Op(src1Op), src2Op(src2Op)
    {
    }

    /**
     * @brief Ins析构函数
     * 
     */
    Ins::~Ins() {
    }

    /**
     * @brief 获取Ins Type
     * 
     * @return Ins Type
     */
    const InsType Ins::GetInsType() {
        return type;
    }
}
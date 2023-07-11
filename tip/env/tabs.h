/**
 * @file tabs.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 表
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <ins/ins.h>
#include <map>

namespace tayir {
    /**
     * @brief 寄存器表
     * 
     */
    class RegisterTab {
    protected:
        /** 寄存器数量 */
        const int regNum;
        /** 寄存器名称 */
        const char **nameTab;
        /** 占用表 */
        int *userTab;
    public:
        /**
         * @brief Register Tab构造函数
         * 
         * @param regNum 寄存器数
         * @param nameTab 名称表
         */
        RegisterTab(const int regNum, const char **nameTab);
        /**
         * @brief Register Tab析构函数
         * 
         */
        virtual ~RegisterTab();
        /**
         * @brief 获取Reg Name
         * 
         * @param regno 寄存器编号
         * @return 寄存器名
         */
        const char *getRegName(int regno) const;
        /** 
         * @brief 获取Reg No
         * 
         * @param regName 寄存器名
         * @return 寄存器编号
         */
        const int getRegno(const char *regName) const;
        /**
         * @brief 获取寄存器使用者
         * 
         * @param regno 寄存器编号
         * @return 寄存器使用者
         */
        const int getRegUser(int regno) const;
        /**
         * @brief 设置Reg为Busy
         * 
         * @param regno 寄存器编号
         * @param valno 值编号
         */
        void setRegBusy(int regno, int valno);
        /**
         * @brief 设置Reg为Free
         * 
         * @param regno 寄存器编号
         */
        void setRegFree(int regno);
    };

    /**
     * @brief x86_64寄存器表
     * 
     */
    class RegisterTabX86_64 : public RegisterTab {
    public:
        /**
         * @brief Register Tab X86_64构造函数
         * 
         */
        RegisterTabX86_64();
        /**
         * @brief Register Tab X86_64析构函数
         * 
         */
        virtual ~RegisterTabX86_64();
    };
}
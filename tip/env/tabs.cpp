/**
 * @file tabs.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 表
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <env/tabs.h>

#include <cstring>

namespace tayir {
//-------------------------------------------------
//|                                               |
//|             Register Tab Section              |
//|                                               |
//-------------------------------------------------

    /**
     * @brief Register Tab构造函数
     * 
     * @param regNum 寄存器数
     * @param nameTab 名称表
     */
    RegisterTab::RegisterTab(const int regNum, const char **nameTab) 
        : regNum(regNum), nameTab(nameTab), userTab(new int[regNum])
    {
        memset(userTab, 0, sizeof(int) * regNum);
    }

    /**
     * @brief Register Tab析构函数
     * 
     */
    RegisterTab::~RegisterTab() {
        if (userTab != NULL) {
            delete[] userTab;
            userTab = NULL;
        }
    }

    /**
     * @brief 获取Reg Name
     * 
     * @param regno 寄存器编号
     * @return 寄存器名
     */
    const char *RegisterTab::getRegName(int regno) {
        if (regno >= regNum || regno < 0) {
            // TODO: throw exception
            return 0;
        }
        return nameTab[regno];
    }
        
    /** 
     * @brief 获取Reg No
     * 
     * @param regName 寄存器名
     * @return 寄存器编号
     */
    int RegisterTab::getRegno(const char *regName) {
        for (int i = 0 ; i < regNum ; i ++) {
            if (strcmp(regName, nameTab[i]) == 0) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief 获取寄存器使用者
     * 
     * @param regno 寄存器编号
     * @return 寄存器使用者
     */
    int RegisterTab::getRegUser(int regno) {
        if (regno >= regNum || regno < 0) {
            // TODO: throw exception
            return false;
        }
        return userTab[regno];
    }

    /**
     * @brief 设置Reg为Busy
     * 
     * @param regno 寄存器编号
     * @param valno 值编号
     */
    void RegisterTab::setRegBusy(int regno, int valno) {
    if (regno >= regNum || regno < 0) {
            // TODO: throw exception
            return;
        }
        userTab[regno] = valno;
    }

    /**
     * @brief 设置Reg为Free
     * 
     * @param regno 寄存器编号
     */
    void RegisterTab::setRegFree(int regno) {
        if (regno >= regNum || regno < 0) {
            // TODO: throw exception
            return;
        }
        userTab[regno] = -1;
    }

//-------------------------------------------------
//|                                               |
//|         Register Tab(x86_64) Section          |
//|                                               |
//-------------------------------------------------

    /** x86_64寄存器数 */
    static const int x86_64RegisterNum = 12;
    /** x86_64寄存器表 */
    static const char *x86_64RegisterTab[x86_64RegisterNum] = {
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "r8",
        "r9",
        "r10",
        "r11",
        "r12",
        "r13",
        "r14",
        "r15"
    };

    /**
     * @brief Register Tab X86_64构造函数
     * 
     */
    RegisterTabX86_64::RegisterTabX86_64() 
        : RegisterTab(x86_64RegisterNum, x86_64RegisterTab)
    {
    }

    /**
     * @brief Register Tab X86_64析构函数
     * 
     */
    RegisterTabX86_64::~RegisterTabX86_64() {
    }
}
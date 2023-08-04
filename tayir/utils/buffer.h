/**
 * @file buffer.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 缓存
 * @version alpha-1.0.0
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <utils/types.h>
#include <cstddef>

namespace tayir {
    /**
     * @brief 缓存
     * 
     * @tparam UnitType 单元类型
     */
    template<typename UnitType> class Buffer {
    protected:
        /** 读指针 */
        int readPos;
        /** 读指针 */
        int writePos;
        /** 大小 */
        int size;
        /** 缓存 */
        UnitType *buffer;
    public:
        /**
         * @brief Buffer构造函数
         * 
         * @param size Buffer大小
         */
        Buffer(int size)
            : readPos(0), writePos(0), size(size), buffer(new UnitType[size])
        {
        }
        /**
         * @brief Buffer析构函数
         * 
         */
        virtual ~Buffer() {
            if (buffer != NULL) {
                delete buffer;
                buffer = NULL;
            }
        }
        /**
         * @brief 写
         * 
         * @param unit 要写的值
         */
        void Write(UnitType unit) {
            if (writePos >= size || writePos < 0) {
                //TODO
                throw "exception";
            }
            buffer[writePos] = unit;
            writePos ++;
        }
        /**
         * @brief 读
         * 
         * @return 读到的值
         */
        UnitType Read(void) {
            if (readPos >= writePos || readPos < 0) {
                //TODO
                throw "exception";
            }
            readPos ++;
            return buffer[readPos - 1];
        }
        /**
         * @brief 重置
         * 
         */
        void Reset() {
            readPos = writePos = 0;
        }
    };

    /**
     * @brief 字节Buffer
     * 
     */
    class ByteBuffer : public Buffer<byte> {
        /**
         * @brief 大端序
         * 
         */
        bool bigOrder;
    public:
        /**
         * @brief Byte Buffer构造函数
         * 
         * @param size 大小
         * @param bigOrder 大端序
         */
        ByteBuffer(int size, bool bigOrder);
        /**
         * @brief 写字节
         * 
         * @param val 字节
         */
        void WriteByte(byte val);
        /**
         * @brief 写字
         * 
         * @param val 字
         */
        void WriteWord(word val);
        /**
         * @brief 写双字
         * 
         * @param val 双字
         */
        void WriteDword(dword val);
        /**
         * @brief 写四字
         * 
         * @param val 四字
         */
        void WriteQword(qword val);
        /**
         * @brief 写字符
         * 
         * @param val 字符
         */
        void WriteChar(char val);
        /**
         * @brief 写短整型
         * 
         * @param val 短整型
         */
        void WriteShort(short val);
        /**
         * @brief 写整型
         * 
         * @param val 整型
         */
        void WriteInt(int val);
        /**
         * @brief 写超长整型
         * 
         * @param val 超长整型
         */
        void WriteLongLong(long long val);
        /**
         * @brief 读字节
         * 
         * @return 字节
         */
        byte ReadByte();
        /**
         * @brief 读字
         * 
         * @return 字
         */
        word ReadWord();
        /**
         * @brief 读双字
         * 
         * @return 双字
         */
        dword ReadDword();
        /**
         * @brief 读四字
         * 
         * @return 四字
         */
        qword ReadQword();
        /**
         * @brief 读字符
         * 
         * @return 字符
         */
        char ReadChar();
        /**
         * @brief 读短整型
         * 
         * @return 短整型
         */
        short ReadShort();
        /**
         * @brief 读整型
         * 
         * @return 整型
         */
        int ReadInt();
        /**
         * @brief 读超长整型
         * 
         * @return 超长整型
         */
        long long ReadLongLong();
    };
}
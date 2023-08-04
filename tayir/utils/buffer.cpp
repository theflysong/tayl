/**
 * @file buffer.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 缓存
 * @version alpha-1.0.0
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <utils/buffer.h>

namespace tayir {
    /**
     * @brief Byte Buffer构造函数
     * 
     * @param size 大小
     * @param bigOrder 大端序
     */
    ByteBuffer::ByteBuffer(int size, bool bigOrder) 
        : Buffer(size), bigOrder(bigOrder)
    {
    }

    /**
     * @brief 写字节
     * 
     * @param val 字节
     */
    void ByteBuffer::WriteByte(byte val) {
        Write(val);
    }

    /**
     * @brief 写字
     * 
     * @param val 字
     */
    void ByteBuffer::WriteWord(word val) {
        if (bigOrder) {
            Write((val >> 8) & 0xFF);
            Write(val & 0xFF);
        }
        else {
            Write(val & 0xFF);
            Write((val >> 8) & 0xFF);
        }
    }

    /**
     * @brief 写双字
     * 
     * @param val 双字
     */
    void ByteBuffer::WriteDword(dword val) {
        if (bigOrder) {
            Write((val >> 24) & 0xFF);
            Write((val >> 16) & 0xFF);
            Write((val >> 8) & 0xFF);
            Write(val & 0xFF);
        }
        else {
            Write(val & 0xFF);
            Write((val >> 8) & 0xFF);
            Write((val >> 16) & 0xFF);
            Write((val >> 24) & 0xFF);
        }
    }

    /**
     * @brief 写四字
     * 
     * @param val 四字
     */
    void ByteBuffer::WriteQword(qword val) {
        if (bigOrder) {
            Write((val >> 56) & 0xFF);
            Write((val >> 48) & 0xFF);
            Write((val >> 40) & 0xFF);
            Write((val >> 32) & 0xFF);
            Write((val >> 24) & 0xFF);
            Write((val >> 16) & 0xFF);
            Write((val >> 8) & 0xFF);
            Write(val & 0xFF);
        }
        else {
            Write(val & 0xFF);
            Write((val >> 8) & 0xFF);
            Write((val >> 16) & 0xFF);
            Write((val >> 24) & 0xFF);
            Write((val >> 32) & 0xFF);
            Write((val >> 40) & 0xFF);
            Write((val >> 48) & 0xFF);
            Write((val >> 56) & 0xFF);
        }
    }

    /**
     * @brief 写字符
     * 
     * @param val 字符
     */
    void ByteBuffer::WriteChar(char val) {
        WriteByte(val);
    }

    /**
     * @brief 写短整型
     * 
     * @param val 短整型
     */
    void ByteBuffer::WriteShort(short val) {
        WriteWord(*(word *)&val);
    }

    /**
     * @brief 写整型
     * 
     * @param val 整型
     */
    void ByteBuffer::WriteInt(int val) {
        WriteDword(*(dword *)&val);
    }

    /**
     * @brief 写超长整型
     * 
     * @param val 超长整型
     */
    void ByteBuffer::WriteLongLong(long long val) {
        WriteQword(*(qword *)&val);
    }

    /**
     * @brief 读字节
     * 
     * @return 字节
     */
    byte ByteBuffer::ReadByte() {
        return Read();
    }

    /**
     * @brief 读字
     * 
     * @return 字
     */
    word ByteBuffer::ReadWord() {
        word byte1 = Read() & 0xFF;
        word byte2 = Read() & 0xFF;
        if (bigOrder) {
            return ((byte2 << 8) | byte1);
        }
        return ((byte1 << 8) | byte2);
    }
    
    /**
     * @brief 读双字
     * 
     * @return 双字
     */
    dword ByteBuffer::ReadDword() {
        dword byte1 = Read() & 0xFF;
        dword byte2 = Read() & 0xFF;
        dword byte3 = Read() & 0xFF;
        dword byte4 = Read() & 0xFF;
        if (bigOrder) {
            return ((byte4 << 24) |(byte3 << 16) | (byte2 << 8) | byte1);
        }
        return ((byte1 << 24) |(byte2 << 16) | (byte3 << 8) | byte4);
    }

    /**
     * @brief 读四字
     * 
     * @return 四字
     */
    qword ByteBuffer::ReadQword(){
        qword byte1 = Read() & 0xFF;
        qword byte2 = Read() & 0xFF;
        qword byte3 = Read() & 0xFF;
        qword byte4 = Read() & 0xFF;
        qword byte5 = Read() & 0xFF;
        qword byte6 = Read() & 0xFF;
        qword byte7 = Read() & 0xFF;
        qword byte8 = Read() & 0xFF;
        if (bigOrder) {
            return ((byte8 << 56) | (byte7 << 48) | (byte6 << 40) | (byte5 << 32) | (byte4 << 24) |(byte3 << 16) | (byte2 << 8) | byte1);
        }
        return ((byte1 << 56) | (byte2 << 48) | (byte3 << 40) | (byte4 << 32) | (byte5 << 24) |(byte6 << 16) | (byte7 << 8) | byte8);
    }

    /**
     * @brief 读字符
     * 
     * @return 字符
     */
    char ByteBuffer::ReadChar() {
        byte res = ReadByte();
        return *(char *)(&res);
    }

    /**
     * @brief 读短整型
     * 
     * @return 短整型
     */
    short ByteBuffer::ReadShort() {
        word res = ReadWord();
        return *(short *)(&res);
    }

    /**
     * @brief 读整型
     * 
     * @return 整型
     */
    int ByteBuffer::ReadInt() {
        dword res = ReadDword();
        return *(int *)(&res);
    }

    /**
     * @brief 读超长整型
     * 
     * @return 超长整型
     */
    long long ByteBuffer::ReadLongLong() {
        qword res = ReadQword();
        return *(long long *)(&res);
    }
}
/**
 * @file type.cpp
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 类型
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#include <ir/type.h>
#include <cstring>

namespace tayir {
//---------------------------------------------------------
//|                                                       |
//|                  primitive types                      |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief Prim Type Prototype构造函数
     * 
     * @param size 大小
     * @param name 名称
     */
    PrimTypePrototype::PrimTypePrototype(int size, const char *name) 
        : size(size), name(name)
    {
    }

    namespace ptypes {
        /** i8 */
        PrimTypePrototype     I8(1, "i8");
        /** i16 */
        PrimTypePrototype    I16(2, "i16");
        /** i32 */
        PrimTypePrototype    I32(4, "i32");
        /** i64 */
        PrimTypePrototype    I64(8, "i64");
        /** ui8 */
        PrimTypePrototype    UI8(1, "ui8");
        /** ui16 */
        PrimTypePrototype   UI16(2, "ui16");
        /** ui32 */
        PrimTypePrototype   UI32(4, "ui32");
        /** ui64 */
        PrimTypePrototype   UI64(8, "ui64");
        /** p16 */
        PrimTypePrototype    P16(2, "p16");
        /** p32 */
        PrimTypePrototype    P32(4, "p32");
        /** p64 */
        PrimTypePrototype    P64(8, "p64");
        /** float */
        PrimTypePrototype  FLOAT(4, "float");
        /** double */
        PrimTypePrototype DOUBLE(8, "double");
        /** bool */
        PrimTypePrototype   BOOL(1, "bool");
    }

//---------------------------------------------------------
//|                                                       |
//|                       types                           |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief Type构造函数
     * 
     * @param prototype 类型原型
     * @param isArray 是否为数组
     */
    Type::Type(PrimTypePrototype prototype, bool isArray)
        : size(prototype.size), isArray(isArray)
    {
        this->name = new char[strlen(prototype.name) + 1];
        strcpy(this->name, prototype.name);
    }

    /**
     * @brief Type构造函数
     * 
     * @param size 类型大小
     * @param name 类型名
     * @param isArray 是否为数组
     */
    Type::Type(int size, char *name, bool isArray)
        : size(size), isArray(isArray)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    /**
     * @brief Type析构函数
     * 
     */
    Type::~Type() {
        if (name != NULL) {
            delete[] name;
            name = NULL;
        }
    }

    /**
     * @brief 获取Size
     * 
     * @return 类型大小
     */
    const int Type::GetSize() {
        return size;
    }

    /**
     * @brief 获取Name
     * 
     * @return 类型名
     */
    const char *Type::GetName() {
        return name;
    }

    /**
     * @brief 是否为数组
     * 
     * @return 是否为数组
     */
    const bool Type::IsArray() {
        return isArray;
    }
    
//---------------------------------------------------------
//|                                                       |
//|                  complex types                        |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief Complex Type构造函数
     * 
     * @param typeList 类型列表
     * @param size 类型大小
     * @param name 类型名
     * @param isArray 是否为数组
     */
    ComplexType::ComplexType(std::vector<int> typeList, int size, char *name, bool isArray) 
        : Type(size, name, isArray), types(new int[typeList.size()]), typeNum(typeList.size())
    {
        for (int i = 0 ; i < typeNum ; i ++) {
            types[i] = typeList.at(i);
        }
    }

    /**
     * @brief Complex Type析构函数
     * 
     */
    ComplexType::~ComplexType() {
        if (types != NULL) {
            delete[] types;
            types = NULL;
        }
    }

    /**
     * @brief 获取Type Num
     * 
     * @return 类型数
     */
    const int ComplexType::GetTypeNum() {
        return typeNum;
    }

    /**
     * @brief 获取Member Type Id
     * 
     * @param sub 下标 
     * @return 成员类型
     */
    const int ComplexType::GetMemberTypeId(int sub) {
        if (sub < 0 || sub >= typeNum) {
            //TODO: throw exception
            return -1;
        }
        return types[sub];
    }
}
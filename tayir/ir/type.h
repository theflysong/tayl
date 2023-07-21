/**
 * @file type.h
 * @author theflysong (song_of_the_fly@163.com)
 * @brief 类型
 * @version alpha-1.0.0
 * @date 2023-07-09
 * 
 * @copyright Copyright (c) 2022 TayhuangOS Development Team
 * SPDX-License-Identifier: LGPL-2.1-only
 * 
 */

#pragma once

#include <vector>
#include <map>
#include <string>

namespace tayir {
//---------------------------------------------------------
//|                                                       |
//|                  primitive types                      |
//|                                                       |
//---------------------------------------------------------
    /**
     * @brief 基础类型原型
     * @see Type::Type
     * 
     */
    struct PrimTypePrototype {
        /**
         * @brief 基础类型大小
         * 
         */
        int size;
        /**
         * @brief 基础类型名
         * 
         */
        const char *name;
        /**
         * @brief Prim Type Prototype构造函数
         * 
         * @param size 大小
         * @param name 名称
         */
        PrimTypePrototype(const int size, const char *name);
    };

    namespace imm {
        /**
         * @brief 立即数类型
         * 
         */
        enum class itype {
            /** i8 */
            I8,
            /** i16 */
            I16,
            /** i32 */
            I32,
            /** i64 */
            I64,
            /** ui8 */
            UI8,
            /** ui16 */
            UI16,
            /** ui32 */
            UI32,
            /** ui64 */
            UI64,
            /** p16 */
            P16,
            /** p32 */
            P32,
            /** p64 */
            P64,
            /** float */
            FLOAT,
            /** double */
            DOUBLE,
            /** bool */
            BOOL
        };
        /** i8 */
        typedef char i8_t;
        /** i16 */
        typedef short i16_t;
        /** i32 */
        typedef int i32_t;
        /** i64 */
        typedef long long i64_t;
        /** ui8 */
        typedef unsigned char ui8_t;
        /** ui16 */
        typedef unsigned short ui16_t;
        /** ui32 */
        typedef unsigned int ui32_t;
        /** ui64 */
        typedef unsigned long long ui64_t;
        /** p16 */
        typedef unsigned short p16_t;
        /** p32 */
        typedef unsigned int p32_t;
        /** p64 */
        typedef unsigned long long p64_t;
        /** float */
        typedef float float_t;
        /** double */
        typedef double double_t;
        /** bool */
        typedef bool bool_t;
        /** i8 */
        extern PrimTypePrototype I8;
        /** i16 */
        extern PrimTypePrototype I16;
        /** i32 */
        extern PrimTypePrototype I32;
        /** i64 */
        extern PrimTypePrototype I64;
        /** ui8 */
        extern PrimTypePrototype UI8;
        /** ui16 */
        extern PrimTypePrototype UI16;
        /** ui32 */
        extern PrimTypePrototype UI32;
        /** ui64 */
        extern PrimTypePrototype UI64;
        /** p16 */
        extern PrimTypePrototype P16;
        /** p32 */
        extern PrimTypePrototype P32;
        /** p64 */
        extern PrimTypePrototype P64;
        /** float */
        extern PrimTypePrototype FLOAT;
        /** double */
        extern PrimTypePrototype DOUBLE;
        /** bool */
        extern PrimTypePrototype BOOL;
    }
    
//---------------------------------------------------------
//|                                                       |
//|                       types                           |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief 类型
     * 
     */
    class Type {
    protected:
        /** 类型大小 */
        const int size;
        /** 类型名 */
        std::string name;
        /** TypeId */
        int typeId;
    public:
        /**
         * @brief Type构造函数
         * 
         * @param prototype 类型原型
         */
        Type(PrimTypePrototype prototype);
        /**
         * @brief Type构造函数
         * 
         * @param size 类型大小
         * @param name 类型名
         */
        Type(const int size, std::string name);
        /**
         * @brief Type析构函数
         * 
         */
        virtual ~Type();
        /**
         * @brief 获取类型大小
         * 
         * @return 类型大小
         */
        const int GetSize() const;
        /**
         * @brief 获取类型名
         * 
         * @return 类型名
         */
        std::string GetName() const;
        /**
         * @brief 是否为数组
         * 
         * @return 是否为数组
         */
        const bool IsArray();
        friend class TypeManager;
    };
    
//---------------------------------------------------------
//|                                                       |
//|                   type manager                        |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief 类型管理器
     * 
     */
    class TypeManager {
    protected:
        /** 类型表 */
        std::vector<Type *> types;
        /** i8 ID */
        int idI8;
        /** i16 ID */
        int idI16;
        /** i32 ID */
        int idI32;
        /** i64 ID */
        int idI64;
        /** ui8 ID */
        int idUI8;
        /** ui16 ID */
        int idUI16;
        /** ui32 ID */
        int idUI32;
        /** ui64 ID */
        int idUI64;
        /** p8 ID */
        int idP8;
        /** p16 ID */
        int idP16;
        /** p32 ID */
        int idP32;
        /** p64 ID */
        int idP64;
        /** float ID */
        int idFloat;
        /** double ID */
        int idDouble;
        /** bool ID */
        int idBool;
    public:
        /**
         * @brief Type Manager构造函数
         * 
         */
        TypeManager();
        /**
         * @brief Type Manager析构函数
         * 
         */
        ~TypeManager();
        /** 
         * @brief 获取类型
         * 
         * @param typeId 类型ID
         * @return 类型
         */
        const Type *GetType(int typeId) const;
        /**
         * @brief 追加类型
         * 
         * @param type 类型
         * @return 类型ID
         */
        const int AppendType(Type *type);
        /**
         * @brief 获取Type Id
         * 
         * @param name 类型名
         * @return 类型ID
         */
        const int GetTypeId(std::string name) const;
        /**
         * @brief 获取 'i8' ID
         * 
         * @return 类型 'i8' ID
         */
        const int GetI8Id() const;
        /**
         * @brief 获取 'i16' ID
         * 
         * @return 类型 'i16' ID
         */
        const int GetI16Id() const;
        /**
         * @brief 获取 'i32' ID
         * 
         * @return 类型 'i32' ID
         */
        const int GetI32Id() const;
        /**
         * @brief 获取 'i64' ID
         * 
         * @return 类型 'i64' ID
         */
        const int GetI64Id() const;
        /**
         * @brief 获取 'ui8' ID
         * 
         * @return 类型 'ui8' ID
         */
        const int GetUI8Id() const;
        /**
         * @brief 获取 'ui16' ID
         * 
         * @return 类型 'ui16' ID
         */
        const int GetUI16Id() const;
        /**
         * @brief 获取 'ui32' ID
         * 
         * @return 类型 'ui32' ID
         */
        const int GetUI32Id() const;
        /**
         * @brief 获取 'ui64' ID
         * 
         * @return 类型 'ui64' ID
         */
        const int GetUI64Id() const;
        /**
         * @brief 获取 'p16' ID
         * 
         * @return 类型 'p16' ID
         */
        const int GetP16Id() const;
        /**
         * @brief 获取 'p32' ID
         * 
         * @return 类型 'p32' ID
         */
        const int GetP32Id() const;
        /**
         * @brief 获取 'p64' ID
         * 
         * @return 类型 'p64' ID
         */
        const int GetP64Id() const;
        /**
         * @brief 获取 'float' ID
         * 
         * @return 类型 'float' ID
         */
        const int GetFloatId() const;
        /**
         * @brief 获取 'double' ID
         * 
         * @return 类型 'double' ID
         */
        const int GetDoubleId() const;
        /**
         * @brief 获取 'bool' ID
         * 
         * @return 类型 'bool' ID
         */
        const int GetBoolId() const;
    };

//---------------------------------------------------------
//|                                                       |
//|                  complex types                        |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief 复合类型
     * 
     */
    class ComplexType : public Type {
    protected:
        /** 类型数 */
        const int typeNum;
        /** 类型列表 */
        int *types;
        /** 成员偏移 */
        int *offsets;
        /** 对齐(2^align) */
        const int align;
        /**
         * @brief Complex Type构造函数
         * 
         * @param typeList 类型列表
         * @param offsetList 成员偏移
         * @param size 类型大小
         * @param align 对齐(2^align)
         * @param name 类型名
         */
        ComplexType(std::vector<int> typeList, std::vector<int> offsetList, const int size, const int align, std::string name);
    public:
        /**
         * @brief Complex Type析构函数
         * 
         */
        virtual ~ComplexType();
        /**
         * @brief 获取类型数
         * 
         * @return 类型数
         */
        const int GetTypeNum() const;
        /**
         * @brief 获取对齐
         * 
         * @return 对齐
         */
        const int GetAlign() const;
        /**
         * @brief 获取成员类型ID
         * 
         * @param sub 下标 
         * @return 成员类型
         */
        const int GetMemberTypeId(int sub) const;
        /**
         * @brief 获取成员偏移
         * 
         * @param sub 下标 
         * @return 成员偏移
         */
        const int GetMemberOffset(int sub) const;
        friend class ComplexTypeBuilder;
    };

    /**
     * @brief 复合类型Builder
     * @see ComplexType
     * 
     */
    class ComplexTypeBuilder {
    protected:
        /** 类型列表 */
        std::vector<int> types;
    public:
        /**
         * @brief Complex Type Builder构造函数
         * 
         */
        ComplexTypeBuilder();
        /**
         * @brief Complex Type Builder析构函数
         * 
         */
        ~ComplexTypeBuilder();
        /**
         * @brief 获取类型数
         * 
         * @return 类型数
         */
        const int GetTypeNum() const;
        /**
         * @brief 获取成员类型ID
         * 
         * @param sub 下标 
         * @return 成员类型ID
         */
        int &GetMemberTypeId(int sub);
        /**
         * @brief 追加类型
         * 
         * @param typeId 类型
         * @return Builder
         */
        ComplexTypeBuilder &AppendType(int typeId);
        /**
         * @brief 构建ComplexType
         * 
         * @param name 类型名
         * @param align 对齐(2^align)
         * @param manager 类型管理器
         * @return ComplexType
         */
        ComplexType *Build(std::string name, int align, TypeManager &manager);
    };
}
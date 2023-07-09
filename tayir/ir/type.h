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

namespace tayir {
    /**
     * @brief 基础类型原型
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
        PrimTypePrototype(int size, const char *name);
    };

    namespace ptypes {
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

    /**
     * @brief 类型
     * 
     */
    class Type {
    protected:
        /** 类型大小 */
        const int size;
        /** 类型名 */
        char *name;
        /** 是否为数组 */
        bool isArray;
    public:
        /**
         * @brief Type构造函数
         * 
         * @param prototype 类型原型
         */
        Type(PrimTypePrototype prototype, bool isArray);
        /**
         * @brief Type构造函数
         * 
         * @param size 类型大小
         * @param name 类型名
         */
        Type(int size, char *name, bool isArray);
        /**
         * @brief Type析构函数
         * 
         */
        virtual ~Type();
        /**
         * @brief 获取Size
         * 
         * @return 类型大小
         */
        const int GetSize();
        /**
         * @brief 获取Name
         * 
         * @return 类型名
         */
        const char *GetName();
        /**
         * @brief 是否为数组
         * 
         * @return 是否为数组
         */
        const bool IsArray();
    };

    /**
     * @brief 复合类型
     * 
     */
    class ComplexType : public Type {
    protected:
        /** 类型列表 */
        int *types;
        /**
         * @brief Complex Type构造函数
         * 
         * @param typeList 类型列表
         */
        ComplexType(std::vector<int> typeList);
    public:
        /**
         * @brief Complex Type析构函数
         * 
         */
        virtual ~ComplexType();
        /**
         * @brief 获取Member Type Id
         * 
         * @param sub 下标 
         * @return 成员类型
         */
        const int GetMemberTypeId(int sub);
    };

    /**
     * @brief 复合类型
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
         * @brief 获取Member Type Id
         * 
         * @param sub 下标 
         * @return 成员类型ID
         */
        const int GetMemberTypeId(int sub);
        /**
         * @brief 替换Type
         * 
         * @param sub 下标
         * @param typeId 类型
         * @return Builder
         */
        virtual ComplexTypeBuilder &ReplaceType(int sub, int typeId);
        /**
         * @brief 追加Type
         * 
         * @param typeId 类型
         * @return Builder
         */
        virtual ComplexTypeBuilder &AppendType(int typeId);
    };

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
         * @brief 获取Type
         * 
         * @param typeId 类型ID
         * @return 类型
         */
        Type *GetType(int typeId);
        /**
         * @brief 追加类型
         * 
         * @param type 类型
         * @return 类型ID
         */
        int AppendType(Type *type);
        /**
         * @brief 获取Type Id
         * 
         * @param name 类型名
         * @return 类型ID
         */
        int GetTypeId(const char *name);
        /**
         * @brief 获取 'i8' ID
         * 
         * @return 类型 'i8' ID
         */
        const int GetI8Id();
        /**
         * @brief 获取 'i16' ID
         * 
         * @return 类型 'i16' ID
         */
        const int GetI16Id();
        /**
         * @brief 获取 'i32' ID
         * 
         * @return 类型 'i32' ID
         */
        const int GetI32Id();
        /**
         * @brief 获取 'i64' ID
         * 
         * @return 类型 'i64' ID
         */
        const int GetI64Id();
        /**
         * @brief 获取 'ui8' ID
         * 
         * @return 类型 'ui8' ID
         */
        const int GetUI8Id();
        /**
         * @brief 获取 'ui16' ID
         * 
         * @return 类型 'ui16' ID
         */
        const int GetUI16Id();
        /**
         * @brief 获取 'ui32' ID
         * 
         * @return 类型 'ui32' ID
         */
        const int GetUI32Id();
        /**
         * @brief 获取 'ui64' ID
         * 
         * @return 类型 'ui64' ID
         */
        const int GetUI64Id();
        /**
         * @brief 获取 'p16' ID
         * 
         * @return 类型 'p16' ID
         */
        const int GetP16Id();
        /**
         * @brief 获取 'p32' ID
         * 
         * @return 类型 'p32' ID
         */
        const int GetP32Id();
        /**
         * @brief 获取 'p64' ID
         * 
         * @return 类型 'p64' ID
         */
        const int GetP64Id();
        /**
         * @brief 获取 'float' ID
         * 
         * @return 类型 'float' ID
         */
        const int GetFloatId();
        /**
         * @brief 获取 'double' ID
         * 
         * @return 类型 'double' ID
         */
        const int GetDoubleId();
        /**
         * @brief 获取 'bool' ID
         * 
         * @return 类型 'bool' ID
         */
        const int GetBoolId();
    };
}
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
    PrimTypePrototype::PrimTypePrototype(const int size, const char *name) 
        : size(size), name(name)
    {
    }

    namespace imm {
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
     */
    Type::Type(PrimTypePrototype prototype)
        : size(prototype.size), name(prototype.name)
    {
    }

    /**
     * @brief Type构造函数
     * 
     * @param size 类型大小
     * @param name 类型名
     */
    Type::Type(const int size, std::string name)
        : size(size), name(name)
    {
    }

    /**
     * @brief Type析构函数
     * 
     */
    Type::~Type() {
    }

    /**
     * @brief 获取类型大小
     * 
     * @return 类型大小
     */
    const int Type::GetSize() const {
        return size;
    }

    /**
     * @brief 获取类型名
     * 
     * @return 类型名
     */
    std::string Type::GetName() const {
        return name;
    }

//---------------------------------------------------------
//|                                                       |
//|                   type manager                        |
//|                                                       |
//---------------------------------------------------------

    /**
     * @brief Type Manager构造函数
     * 
     */
    TypeManager::TypeManager() {
        idI8  = AppendType(new Type(imm::I8));
        idI16 = AppendType(new Type(imm::I16));
        idI32 = AppendType(new Type(imm::I32));
        idI64 = AppendType(new Type(imm::I64));

        idUI8  = AppendType(new Type(imm::UI8));
        idUI16 = AppendType(new Type(imm::UI16));
        idUI32 = AppendType(new Type(imm::UI32));
        idUI64 = AppendType(new Type(imm::UI64));
        
        idP16 = AppendType(new Type(imm::P16));
        idP32 = AppendType(new Type(imm::P32));
        idP64 = AppendType(new Type(imm::P64));

        idFloat  = AppendType(new Type(imm::FLOAT));
        idDouble = AppendType(new Type(imm::DOUBLE));
        idBool   = AppendType(new Type(imm::BOOL));
    }

    /**
     * @brief Type Manager析构函数
     * 
     */
    TypeManager::~TypeManager() {
        for (Type *type : types) {
            delete type;
        }
        types.clear();
    }

    /** 
     * @brief 获取类型
     * 
     * @param typeId 类型ID
     * @return 类型
     */
    const Type *TypeManager::GetType(int typeId) const {
        if (typeId < 0 || typeId >= (int)types.size()) {
            //TODO: throw an exception
            return NULL;
        }
        return types.at(typeId);
    }

    /**
     * @brief 追加类型
     * 
     * @param type 类型
     * @return 类型ID
     */
    const int TypeManager::AppendType(Type *type) {
        type->typeId = types.size();
        types.push_back(type);
        return type->typeId;
    }

    /**
     * @brief 获取Type Id
     * 
     * @param name 类型名
     * @return 类型ID
     */
    const int TypeManager::GetTypeId(std::string name) const {
        for (Type *type : types) {
            if (type->name == name) {
                return type->typeId;
            }
        }
        return -1;
    }

    /**
     * @brief 获取 'i8' ID
     * 
     * @return 类型 'i8' ID
     */
    const int TypeManager::GetI8Id() const {
        return idI8;
    }

    /**
     * @brief 获取 'i16' ID
     * 
     * @return 类型 'i16' ID
     */
    const int TypeManager::GetI16Id() const {
        return idI16;
    }
    /**
     * @brief 获取 'i32' ID
     * 
     * @return 类型 'i32' ID
     */
    const int TypeManager::GetI32Id() const {
        return idI32;
    }
    /**
     * @brief 获取 'i64' ID
     * 
     * @return 类型 'i64' ID
     */
    const int TypeManager::GetI64Id() const {
        return idI64;
    }
    /**
     * @brief 获取 'ui8' ID
     * 
     * @return 类型 'ui8' ID
     */
    const int TypeManager::GetUI8Id() const {
        return idUI8;
    }
    /**
     * @brief 获取 'ui16' ID
     * 
     * @return 类型 'ui16' ID
     */
    const int TypeManager::GetUI16Id() const {
        return idUI16;
    }
    /**
     * @brief 获取 'ui32' ID
     * 
     * @return 类型 'ui32' ID
     */
    const int TypeManager::GetUI32Id() const {
        return idUI32;
    }
    /**
     * @brief 获取 'ui64' ID
     * 
     * @return 类型 'ui64' ID
     */
    const int TypeManager::GetUI64Id() const {
        return idUI64;
    }
    /**
     * @brief 获取 'p16' ID
     * 
     * @return 类型 'p16' ID
     */
    const int TypeManager::GetP16Id() const {
        return idP16;
    }
    /**
     * @brief 获取 'p32' ID
     * 
     * @return 类型 'p32' ID
     */
    const int TypeManager::GetP32Id() const {
        return idP32;
    }
    /**
     * @brief 获取 'p64' ID
     * 
     * @return 类型 'p64' ID
     */
    const int TypeManager::GetP64Id() const {
        return idP64;
    }
    /**
     * @brief 获取 'float' ID
     * 
     * @return 类型 'float' ID
     */
    const int TypeManager::GetFloatId() const {
        return idFloat;
    }
    /**
     * @brief 获取 'double' ID
     * 
     * @return 类型 'double' ID
     */
    const int TypeManager::GetDoubleId() const {
        return idDouble;
    }
    /**
     * @brief 获取 'bool' ID
     * 
     * @return 类型 'bool' ID
     */
    const int TypeManager::GetBoolId() const {
        return idBool;
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
     * @param offsetList 成员偏移
     * @param size 类型大小
     * @param align 对齐(2^align)
     * @param name 类型名
     */
    ComplexType::ComplexType(std::vector<int> typeList, std::vector<int> offsetList, const int size, const int align, std::string name)
        : Type(size, name), typeNum(typeList.size()), types(new int[typeNum]), offsets(new int[typeNum]), align(align)
    {
        for (int i = 0 ; i < typeNum ; i ++) {
            types[i] = typeList.at(i);
        }
        for (int i = 0 ; i < typeNum ; i ++) {
            offsets[i] = offsetList.at(i);
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
     * @brief 获取类型数
     * 
     * @return 类型数
     */
    const int ComplexType::GetTypeNum() const {
        return typeNum;
    }

    /**
     * @brief 获取成员类型ID
     * 
     * @param sub 下标 
     * @return 成员类型
     */
    const int ComplexType::GetMemberTypeId(int sub) const {
        if (sub < 0 || sub >= typeNum) {
            //TODO: throw an exception
            return -1;
        }
        return types[sub];
    }

    /**
     * @brief 获取成员偏移
     * 
     * @param sub 下标 
     * @return 成员偏移
     */
    const int ComplexType::GetMemberOffset(int sub) const {
        if (sub < 0 || sub >= typeNum) {
            //TODO: throw an exception
            return -1;
        }
        return offsets[sub];
    }
    
        
    /**
     * @brief Complex Type Builder构造函数
     * 
     */
    ComplexTypeBuilder::ComplexTypeBuilder() {
    }

    /**
     * @brief Complex Type Builder析构函数
     * 
     */
    ComplexTypeBuilder::~ComplexTypeBuilder() {
        types.clear();
    }

    /**
     * @brief 获取类型数
     * 
     * @return 类型数
     */
    const int ComplexTypeBuilder::GetTypeNum() const {
        return types.size();
    }

    /**
     * @brief 获取成员类型ID
     * 
     * @param sub 下标 
     * @return 成员类型ID
     */
    int &ComplexTypeBuilder::GetMemberTypeId(int sub) {
        if (sub < 0 || sub >= (int)types.size()) {
            //TODO: throw an exception rather than const char *
            throw "Out of bound!";
        }
        return types.at(sub);
    }

    /**
     * @brief 追加类型
     * 
     * @param typeId 类型
     * @return Builder
     */
    ComplexTypeBuilder &ComplexTypeBuilder::AppendType(int typeId) {
        types.push_back(typeId);
        return *this;
    }

    /**
     * @brief 对齐
     * 
     * @param offset 偏移 
     * @param alignBytes 对齐字节数
     * @return 对齐后偏移
     */
    static int AlignOffset(const int offset, int alignBytes) {
        if (offset % alignBytes == 0) {
            return offset;
        }
        return ((offset / alignBytes) + 1) * alignBytes;
    }

    /**
     * @brief 构建ComplexType
     * 
     * @param name 类型名
     * @param align 对齐(2^align)
     * @param manager 类型管理器
     * @return ComplexType
     */
    ComplexType *ComplexTypeBuilder::Build(std::string name, const int align, TypeManager &manager) {
        std::vector<int> offsets;

        int curOffset = 0;
        int maxMemberSize = 0;

        for (int type : types) {
            int memberSize = manager.GetType(type)->GetSize();
            maxMemberSize = memberSize > maxMemberSize ? memberSize : maxMemberSize;
            
            // get align
            int curAlign = memberSize > (1 << align) ? (1 << align) : memberSize;
            // align the offset
            curOffset = AlignOffset(curOffset, curAlign);
            offsets.push_back(curOffset);

            curOffset += memberSize;
        }
        // get align
        int curAlign = maxMemberSize > (1 << align) ? (1 << align) : maxMemberSize;
        // align the offset
        curOffset = AlignOffset(curOffset, curAlign);

        return new ComplexType(types, offsets, curOffset, align, name);
    }
}
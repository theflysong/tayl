#include <ir/ins.h>
#include <ir/slice.h>
#include <iostream>

struct myType {
    unsigned char ui8_1;
    int i32_2;
    unsigned int ui32_3;
    long long i64_4; 
    unsigned char ui8_5;
    int i32_6;
    unsigned char ui8_7;
    int i32_8;
    unsigned long long ui64_9;
    bool bool_10;
} __attribute__((aligned(8)));

int main(int argc, const char **argv) {
    using namespace tayir;
    TypeManager manager;
    std::cout << manager.GetType(manager.GetI8Id())->GetSize() << std::endl;
    int myTypeId = manager.AppendType(
        ComplexTypeBuilder()
            .AppendType(manager.GetUI8Id())
            .AppendType(manager.GetI32Id())
            .AppendType(manager.GetUI32Id())
            .AppendType(manager.GetI64Id())
            .AppendType(manager.GetUI8Id())
            .AppendType(manager.GetI32Id())
            .AppendType(manager.GetUI8Id())
            .AppendType(manager.GetI32Id())
            .AppendType(manager.GetUI64Id())
            .AppendType(manager.GetBoolId())
            .Build("myType", 3, manager)
    );
    const ComplexType *myTypeType = dynamic_cast<const ComplexType*>(manager.GetType(myTypeId));
    std::cout << "member offsets:" << std::endl;
    std::cout << offsetof(myType, ui8_1) << ":" << myTypeType->GetMemberOffset(0) << std::endl;
    std::cout << offsetof(myType, i32_2) << ":" << myTypeType->GetMemberOffset(1) << std::endl;
    std::cout << offsetof(myType, ui32_3) << ":" << myTypeType->GetMemberOffset(2) << std::endl;
    std::cout << offsetof(myType, i64_4) << ":" << myTypeType->GetMemberOffset(3) << std::endl;
    std::cout << offsetof(myType, ui8_5) << ":" << myTypeType->GetMemberOffset(4) << std::endl;
    std::cout << offsetof(myType, i32_6) << ":" << myTypeType->GetMemberOffset(5) << std::endl;
    std::cout << offsetof(myType, ui8_7) << ":" << myTypeType->GetMemberOffset(6) << std::endl;
    std::cout << offsetof(myType, i32_8) << ":" << myTypeType->GetMemberOffset(7) << std::endl;
    std::cout << offsetof(myType, ui64_9) << ":" << myTypeType->GetMemberOffset(8) << std::endl;
    std::cout << offsetof(myType, bool_10) << ":" << myTypeType->GetMemberOffset(9) << std::endl;
    std::cout << "total size:" << std::endl;
    std::cout << sizeof(myType) << ":" << myTypeType->GetSize() << std::endl;
    return 0;
}
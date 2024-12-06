#include "type_signature.hpp"
#include "test_types.hpp"
#include <iostream>

template <typename T>
void print_type_signature(const char* name)
{
    using namespace type_signature;
    constexpr auto sig = TypeSignature<T>::calculate();
    std::cout << name << ": ";
    sig.print();
    std::cout << '\n';
}

int main()
{
    std::cout << "Type signatures with size and alignment information:\n";

    print_type_signature<int32_t>("int32_t");
    print_type_signature<float>("float");
    print_type_signature<test::Point>("Point");
    print_type_signature<test::Rectangle>("Rectangle");
    print_type_signature<test::TestType>("TestType");
    print_type_signature<test::TestType2>("TestType2");
    print_type_signature<type_signature::XVector<int32_t>>("Vector<int32_t>");
    print_type_signature<type_signature::XMap<type_signature::XString, int32_t>>("Map<XString, int32_t>");
    print_type_signature<char[type_signature::ANY_SIZE]>("char[ANY_SIZE]");
    print_type_signature<void*>("void*");
    print_type_signature<type_signature::XAny>("XAny");
    print_type_signature<type_signature::DynamicStruct>("DynamicStruct");

    return 0;
}
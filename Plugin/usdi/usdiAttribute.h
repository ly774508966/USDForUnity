#pragma once

namespace usdi {

class Attribute
{
public:
    Attribute(Schema *parent, UsdAttribute usdattr);
    virtual ~Attribute();

    const char* getName() const;
    const char* getTypeName() const;
    bool isArray() const;
    bool hasValue() const;

    virtual AttributeType getType() const = 0;
    virtual size_t getSize(Time t) const = 0; // always 1 if not array

    // if attribute is array, get()/set() assume data is VtArray<T>*.
    // if you want to pass raw pointer, you can use getBuffered()/setBuffered().
    virtual bool get(void *dst, Time t) const = 0;
    virtual bool set(const void *src, Time t) = 0;

    virtual bool getBuffered(void *dst, size_t size, Time t) const = 0;
    virtual bool setBuffered(const void *src, size_t size, Time t) = 0;

protected:
    Schema *m_parent;
    UsdAttribute m_usdattr;
};

Attribute* WrapExistingAttribute(Schema *parent, UsdAttribute usd);
Attribute* WrapExistingAttribute(Schema *parent, const char *name);
Attribute* CreateNewAttribute(Schema *parent, const char *name, AttributeType type);

#define EachAttributeTypeAndEnum(Body)\
    Body(int, AttributeType::Int, SdfValueTypeNames->Int)\
    Body(uint, AttributeType::UInt, SdfValueTypeNames->UInt)\
    Body(float, AttributeType::Float, SdfValueTypeNames->Float)\
    Body(GfVec2f, AttributeType::Float2, SdfValueTypeNames->Float2)\
    Body(GfVec3f, AttributeType::Float3, SdfValueTypeNames->Float3)\
    Body(GfVec4f, AttributeType::Float4, SdfValueTypeNames->Float4)\
    Body(GfQuatf, AttributeType::Quaternion, SdfValueTypeNames->Quatf)\
    Body(TfToken, AttributeType::Token, SdfValueTypeNames->Token)\
    Body(VtArray<int>, AttributeType::IntArray, SdfValueTypeNames->IntArray)\
    Body(VtArray<uint>, AttributeType::UIntArray, SdfValueTypeNames->UIntArray)\
    Body(VtArray<float>, AttributeType::FloatArray, SdfValueTypeNames->FloatArray)\
    Body(VtArray<GfVec2f>, AttributeType::Float2Array, SdfValueTypeNames->Float2Array)\
    Body(VtArray<GfVec3f>, AttributeType::Float3Array, SdfValueTypeNames->Float3Array)\
    Body(VtArray<GfVec4f>, AttributeType::Float4Array, SdfValueTypeNames->Float4Array)\
    Body(VtArray<GfQuatf>, AttributeType::QuaternionArray, SdfValueTypeNames->QuatfArray)\
    Body(VtArray<TfToken>, AttributeType::TokenArray, SdfValueTypeNames->TokenArray)

} // namespace usdi

#include "object.h"

std::string Object::Name() const
{
    return name;
}
unsigned int Object::ID() const
{
    return id;
}
void Object::SetName(const std::string& name)
{
    this->name = name;
}
void Object::SetID(unsigned int id)
{
    this->id = id;
}
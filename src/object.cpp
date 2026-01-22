#include "object.h"

std::string Object::Name() const
{
    return name;
}
unsigned int Object::ID() const
{
    return id;
}
void Object::SetName(const std::string &name)
{
    this->name = name;
}
void Object::SetID(unsigned int id)
{
    this->id = id;
}

#ifdef IMGUI

bool Object::DrawGUI()
{
    bool changed = false;

    char buffer[256];
    strcpy(buffer, name.c_str());
    if (ImGui::InputText("Name", buffer, 256))
    {
        changed = true;
        name = buffer;
    }

    return changed;
}
#endif
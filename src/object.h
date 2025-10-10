#ifndef OBJECT_H
#define OBJECT_H
#include <string>
class Object
{
private:

    std::string name;
    unsigned int id;
    
public:

    std::string Name() const;
    unsigned int ID() const;
    void SetName(const std::string& name);
    void SetID(unsigned int id);
};
#endif
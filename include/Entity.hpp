#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>

class Entity
{
public:
    static void registerClass();
    Entity(int);
    int getID();
private:
    int m_id;
    std::string m_name;
};

#endif

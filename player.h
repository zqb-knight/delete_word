#ifndef PLAYER_H
#define PLAYER_H
#include "person.h"


class Player : public Person
{
public:
    Player();
private:
    int stage;   //关卡
    int exp;     //经验

};

#endif // PLAYER_H

#ifndef QUESTIONER_H
#define QUESTIONER_H
#include "person.h"


class Questioner : public Person
{
public:
    Questioner();
    int question_number;    //出题数


};

#endif // QUESTIONER_H

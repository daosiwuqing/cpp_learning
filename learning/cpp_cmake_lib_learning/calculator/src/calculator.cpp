#include "calculator.h"
#include "add.h"
#include "sub.h"



int Calculator::calc_add(int x, int y)
{
    return add(x, y);
};

int Calculator::calc_sub(int x, int y)
{
    return sub(x, y);
};



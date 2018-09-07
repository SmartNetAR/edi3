/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

class Function
{
    public:
        typedef std::unordered_map<std::string, double> funcParamType;

        virtual ~Function(){}
        virtual std::list<std::string> getParameterList() = 0;
        virtual double evaluate(funcParamType parameters, double x) = 0;
};

#endif // FUNCTION_H

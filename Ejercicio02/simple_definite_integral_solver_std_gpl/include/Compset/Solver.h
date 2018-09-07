/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef SOLVER_H
#define SOLVER_H

#include <Compset/Component.h>
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class Solver
{
    public:
        typedef std::unordered_map<std::string, std::string> solverParamType;
        typedef std::list<std::string> solverParamListType;

        virtual ~Solver(){}
        virtual solverParamListType getParameterList() = 0;
        virtual void setFunction(Component* functionComponent) = 0;
        virtual double solve(solverParamType parameters) = 0;
};

#endif // SOLVER_H

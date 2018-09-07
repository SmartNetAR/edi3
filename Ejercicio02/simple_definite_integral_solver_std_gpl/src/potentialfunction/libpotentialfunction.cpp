/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved.
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <Compset/Component.h>
#include <Compset/Function.h>
#include <iostream>
#include <cmath>

#include <unordered_map>
#include <list>
#include <string>

class PotentialFunction : public Function, public Component
{
    public:
        PotentialFunction();
        virtual ~PotentialFunction();
        std::list<std::string> getParameterList();
        double evaluate(funcParamType parameters, double x);

        //Component
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        std::list<std::string> m_parametersList;
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

PotentialFunction::PotentialFunction() : m_referenceCounter(0)
{
    m_parametersList.push_back("a");
    m_parametersList.push_back("n");
}

PotentialFunction::~PotentialFunction(){}

std::list<std::string> PotentialFunction::getParameterList()
{
    return m_parametersList;
}

double PotentialFunction::evaluate(funcParamType parameters, double x)
{
    return parameters["a"] * pow(x, parameters["n"]) ;
}

//Component
bool PotentialFunction::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Function") ?
        m_implemented = true
            : m_implemented = false;
}

void* PotentialFunction::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void PotentialFunction::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new PotentialFunction;
}

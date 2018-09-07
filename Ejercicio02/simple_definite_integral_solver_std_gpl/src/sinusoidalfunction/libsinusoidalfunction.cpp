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

class SinusoidalFunction : public Function, public Component
{
    public:
        SinusoidalFunction();
        virtual ~SinusoidalFunction();
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

SinusoidalFunction::SinusoidalFunction() : m_referenceCounter(0)
{
    m_parametersList.push_back("a");
    m_parametersList.push_back("k");
}

SinusoidalFunction::~SinusoidalFunction(){}

std::list<std::string> SinusoidalFunction::getParameterList()
{
    return m_parametersList;
}

double SinusoidalFunction::evaluate(funcParamType parameters, double x)
{
    return parameters["a"] * sin(parameters["k"] * x) ;
}

//Component
bool SinusoidalFunction::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Function") ?
        m_implemented = true
            : m_implemented = false;
}

void* SinusoidalFunction::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void SinusoidalFunction::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new SinusoidalFunction;
}

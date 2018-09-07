/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <cmath>

#include <unordered_map>
#include <list>
#include <string>

#include <Compset/Solver.h>
#include <Compset/Component.h>
#include <Compset/Function.h>

class TrapezoidSolver : public Solver, public Component
{
    public:
        TrapezoidSolver();
        virtual ~TrapezoidSolver();
        std::list<std::string> getParameterList();
        void setFunction(Component* functionComponent);
        double solve(std::unordered_map<std::string, std::string> parameters);

        //Component
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        std::list<std::string> m_parametersList;
        Component* m_functionComponent;
        Function* m_functionObject;
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

TrapezoidSolver::TrapezoidSolver() : m_referenceCounter(0)
{
    m_parametersList.push_back("x0");
    m_parametersList.push_back("x1");
    m_parametersList.push_back("intervals");
}

TrapezoidSolver::~TrapezoidSolver()
{
    m_functionComponent->release();
}

std::list<std::string> TrapezoidSolver::getParameterList()
{
    return m_parametersList;
}

void TrapezoidSolver::setFunction(Component* functionComponent)
{
    m_functionComponent = functionComponent;

    if(m_functionComponent->implements("Function"))
    {
        m_functionObject = (Function*) m_functionComponent->getInstance();
    }
    else
    {
        std::cout << "Error: The component doesn't implement the Function interface!" << std::endl;
        exit(-1);
    }
}

double TrapezoidSolver::solve(std::unordered_map<std::string, std::string> parameters)
{
    /*PARAMETERS*/
    /*:Declared variables*/
    std::list<std::string> functionParameterList;
    std::list<std::string> solverParameterList;
    std::unordered_map<std::string, double> functionParameters;
    std::unordered_map<std::string, double> solverParameters;
    /*:Declared variables*/

    /*Obtain Solver Input Parameters:*/
    solverParameterList = getParameterList();
    for (std::list<std::string>::iterator it = solverParameterList.begin(); it != solverParameterList.end(); ++it)
    {
        solverParameters[*it] = std::stod(parameters[*it]);
    }
    /*:Obtain Solver Input Parameters*/

    /*Obtain Function Input Parameters:*/
    functionParameterList = m_functionObject->getParameterList();
    for (std::list<std::string>::iterator it = functionParameterList.begin(); it != functionParameterList.end(); ++it)
    {
        functionParameters[*it] = std::stod(parameters[*it]);
    }
    /*:Obtain Function Input Parameters*/
    /*PARAMETERS*/

    /**************************************************************************************************/

    /*Trapezoid Method*/
    int i;
    double dx;
    double x;
    double result = 0;

    /*dx*/
    dx = (solverParameters["x1"] - solverParameters["x0"]) / solverParameters["intervals"];

    for (i = 0; i < solverParameters["intervals"]; ++i)
    {
        x = solverParameters["x0"] + i * dx;
        result += std::abs(0.5 * ( m_functionObject->evaluate(functionParameters, x+dx) + m_functionObject->evaluate(functionParameters, x) ) * dx);
    }
    /*Trapezoid Method*/

    return result;
}

//Component
bool TrapezoidSolver::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Solver") ?
        m_implemented = true
            : m_implemented = false;
}

void* TrapezoidSolver::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void TrapezoidSolver::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new TrapezoidSolver;
}

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

#include <Compset/Application.h>
#include <Compset/RequestHandler.h>
#include <Compset/Solver.h>
#include <Compset/Component.h>
#include <Compset/Function.h>
#include <Compset/ComponentFactory.h>

class ApplicationLib : public Application, public Component
{
    public:
        ApplicationLib();
        virtual ~ApplicationLib();
        int run();

        //Component
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

ApplicationLib::ApplicationLib() : m_referenceCounter(0)
{
}

ApplicationLib::~ApplicationLib(){}

int ApplicationLib::run()
{
    /*CREATION OF COMPONENT FACTORY*/
    ComponentFactory* componentFactoryObject = new ComponentFactory();

/********************************************************************************************/

/*REQUEST ANALIZER COMPONENT SECTION*/
    componentFactoryObject->setType("RequestHandler");
    Component* requestHandlerComponent = componentFactoryObject->createFrom("./lib/librequesthandler");
    
    /*INSTANCE*/
    RequestHandler* requestHandlerObject = ( (RequestHandler*) requestHandlerComponent->getInstance() );

    /*USE COMPONENT*/
    std::unordered_map<std::string, std::string> requestMap = requestHandlerObject->getRequestMap();
/*REQUEST ANALIZER COMPONENT SECTION*/

/********************************************************************************************/ 

/********************************************************************************************/

/*SOLVER COMPONENT SECTION*/
    componentFactoryObject->setType("Solver");

    Component* solverComponent = componentFactoryObject->createFrom("./lib/lib" + requestMap["solver_name"] + "solver");
    
    Solver* solverObject = ( (Solver*) solverComponent->getInstance() );

    /*COMPOSITION OF SOLVER COMPONENT SECTION*/
    componentFactoryObject->setType("Function");
    Component* functionComponent = componentFactoryObject->createFrom("./lib/lib" + requestMap["function_name"]);
    solverObject->setFunction(functionComponent);
    /*COMPOSITION OF SOLVER COMPONENT SECTION*/
/*SOLVER COMPONENT SECTION*/

/********************************************************************************************/    



/********************************************************************************************/
    /*DELETION OF COMPONENT FACTORY*/
    delete componentFactoryObject;
/********************************************************************************************/

    /*Declared variables:*/
    double result;

    /*Use solver:*/
    result = solverObject->solve(requestMap);
    /*:Use solver*/

    /*Result*/
    std::string strResult = std::to_string(result);
    std::string jsonOut;
    jsonOut = "Content-type: application/json; charset=utf-8\n\n";
    jsonOut += "{\"result\": \""+strResult+"\"}";

    std::cout << jsonOut << std::endl;

    /*Release Components*/
    solverComponent->release();
    requestHandlerComponent->release();

    return 0;
}

//Component
bool ApplicationLib::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Application") ?
        m_implemented = true
            : m_implemented = false;
}

void* ApplicationLib::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void ApplicationLib::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new ApplicationLib;
}

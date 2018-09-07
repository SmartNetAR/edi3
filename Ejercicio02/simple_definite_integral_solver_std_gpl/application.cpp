/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <cstdlib> 
#include <string>

#include <Compset/ComponentFactory.h>
#include <Compset/Component.h>
#include <Compset/Application.h>

int main(int argc, char* argv[])
{
    if (1 < argc )
    {
        setenv("TERMINAL_QUERY_STRING", argv[1], 0);
    }

    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setType("Application");
    Component* applicationComponent = componentFactoryObject->createFrom("./lib/libapplication");
    delete componentFactoryObject;

    Application* applicationObject = ( (Application*) applicationComponent->getInstance() );
    applicationObject->run();
    applicationComponent->release();
    return 0;
}

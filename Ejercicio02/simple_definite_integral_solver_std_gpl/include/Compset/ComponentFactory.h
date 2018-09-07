/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <Compset/LibraryLoader.h>
#include <Compset/Component.h>

class ComponentFactory
{
    public:
        ComponentFactory();
        ComponentFactory(std::string interfaceName);
 		void setType(std::string interfaceName);
        virtual ~ComponentFactory();
        Component* createFrom(std::string path);

    private:
    	std::string m_interfaceName;
};

ComponentFactory::ComponentFactory()
{
    //ctor
    m_interfaceName = "";
}

ComponentFactory::~ComponentFactory()
{
    //dtor
}

ComponentFactory::ComponentFactory(std::string interfaceName)
{
    m_interfaceName = interfaceName;
}

void ComponentFactory::setType(std::string interfaceName)
{
    m_interfaceName = interfaceName;
}

Component* ComponentFactory::createFrom(std::string path)
{
    Component* componentObject = NULL;
    bool notNullFactory; 

    //THE LOADER:
    LibraryLoader* loaderObject = LibraryLoader::getInstance();

    //LOAD
    void* load = loaderObject->loadLibrary(path);

    if(load)
    {
        typedef Component* ( *ComponentFactory ) ();
        ComponentFactory factory = ( ComponentFactory ) loaderObject->getExternalFunction( "create" );

        if ( factory )
        {
            Component* createdComponent;
            notNullFactory = (createdComponent = factory());

            if ( notNullFactory )            
            {
                if(m_interfaceName != "")
                {
                    if(createdComponent->implements(m_interfaceName))
                    {
                        componentObject = createdComponent;
                    }
                    else
                    {
                        std::cout << "Error: The component doesn't implement the "+m_interfaceName+" interface!" << std::endl;
                        exit(-1);
                    }
                }
                else
                {
                    std::cout << "Error: The component requires an interface!" << std::endl;
                    exit(-1);
                }
            }
            else
            {
                loaderObject->freeLibrary();
                std::cout << "Error:  Failed creating a component from "
                        << path << ", null component." << std::endl;
                exit(-1);
            }

        }
        else
        {
            loaderObject->freeLibrary();
            std::cout << "Error:  Failed creating a component from "
                    << path << ", there is no external function \"create(void)\"." << std::endl;
            exit(-1);
        }
    }
    else
    {
        std::cout << "Error: Failed to load the library: " << path << std::endl;
        exit(-1);
    }

    return componentObject;
}

#endif // COMPONENTFACTORY_H

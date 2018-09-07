/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <Compset/Component.h>
#include <Compset/ResponseHandler.h>
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class HttpResponseHandler : public ResponseHandler, public Component
{
    public:
        HttpResponseHandler();
        virtual ~HttpResponseHandler();

        //ResponseHandler
        void response(std::string type);

        //Component
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

HttpResponseHandler::HttpResponseHandler() : m_referenceCounter(0) {}

HttpResponseHandler::~HttpResponseHandler() {}


void HttpResponseHandler::response(std::string type)
{

}

//Component
bool HttpResponseHandler::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "ResponseHandler") ?
        m_implemented = true
            : m_implemented = false;
}

void* HttpResponseHandler::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void HttpResponseHandler::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new HttpResponseHandler;
}

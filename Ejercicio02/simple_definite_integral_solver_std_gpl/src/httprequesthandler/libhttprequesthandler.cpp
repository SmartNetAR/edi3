/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <Compset/Component.h>
#include <Compset/RequestHandler.h>
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>//FOR QUERY_STRING VALIDATION
#include <sstream>//FOR M_EXPLODE()

class HttpRequestHandler : public RequestHandler, public Component
{
    public:
        HttpRequestHandler();
        virtual ~HttpRequestHandler();

        //RequestHandler
        std::unordered_map<std::string, std::string> getRequestMap();

        //Component
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        std::string m_decode(std::string &input);
        std::vector<std::string> m_explode(std::string const &input, char delimiter);
        std::string m_getRequestParameters();

        //Component
        int m_referenceCounter;
        bool m_implemented;
};

HttpRequestHandler::HttpRequestHandler() : m_referenceCounter(0) {}

HttpRequestHandler::~HttpRequestHandler() {}

//Thanks Tominko...
std::string HttpRequestHandler::m_decode(std::string &input)
{
    std::string ret;
    char ch;
    unsigned int i;
    unsigned int ii;
    
    for (i=0; i<input.length(); i++)
    {
        if (int(input[i])==37)
        {
            sscanf(input.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=input[i];
        }
    }
    return (ret);
}

std::vector<std::string> HttpRequestHandler::m_explode(std::string const &input, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(input);

    for (std::string token; getline(iss, token, delimiter); )
    {
        result.push_back(move(token));
    }

    return result;
}

std::string HttpRequestHandler::m_getRequestParameters()
{
    std::string requestParameters = "";

    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") == NULL)
    {
        std::cout << "The request method is null" << std::endl;
        exit(-1);
    }    
    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") != NULL)
    {
        std::string input = std::string(getenv("TERMINAL_QUERY_STRING"));
        bool isAQueryString = std::regex_match (input , std::regex("^([^=]+=[^=]+&)+[^=]+(=[^=]+)?$"));
        
        if (isAQueryString)
        {
            requestParameters = input;
        }
        else
        {
            std::cout << "The request is not a QUERY_STRING" << std::endl;
            exit(-1);
        } 
    }
    else
    {
        std::string requestMethod = std::string(getenv("REQUEST_METHOD"));

        if(requestMethod == "GET") { requestParameters = std::string(getenv("QUERY_STRING")); }

        if(requestMethod == "POST") { std::cin >> requestParameters; }
    }

    return requestParameters;
}

std::unordered_map<std::string, std::string> HttpRequestHandler::getRequestMap()
{
    std::string requestParameters = m_getRequestParameters();
    std::vector<std::string> keysWithValues = m_explode( m_decode(requestParameters), '&' );
    std::vector<std::string> keysAndValues;
    std::vector<std::string>::iterator i;

    int aux = 0;
    std::unordered_map<std::string, std::string> requestMap;

    for(i = keysWithValues.begin(); i != keysWithValues.end(); i++)
    {
        keysAndValues = m_explode( keysWithValues[aux], '=' );
        requestMap[keysAndValues[0]] = keysAndValues[1];
        aux++;
    }

    return requestMap;
}

//Component
bool HttpRequestHandler::implements(std::string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "RequestHandler") ?
        m_implemented = true
            : m_implemented = false;
}

void* HttpRequestHandler::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void HttpRequestHandler::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new HttpRequestHandler;
}

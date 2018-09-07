/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <unordered_map>
#include <string>
#include <iostream>

class RequestHandler
{
    public:
        virtual ~RequestHandler() {}
    	virtual std::unordered_map<std::string, std::string> getRequestMap() = 0;
};

#endif // REQUESTHANDLER_H

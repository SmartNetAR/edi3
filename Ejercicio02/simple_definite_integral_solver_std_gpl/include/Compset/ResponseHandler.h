/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include <string>
#include <iostream>

class ResponseHandler
{
    public:
        virtual ~ResponseHandler() {}
    	virtual void response(std::string type) = 0;
};

#endif // RESPONSEHANDLER_H

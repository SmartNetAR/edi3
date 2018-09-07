/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

class Application
{
    public:
    	virtual ~Application(){}
		virtual int run() = 0;
};

#endif // APPLICATION_H

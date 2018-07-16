#include <iostream>
#include <string>
#include <MessengerInterface.h>
#include <ComponentInterface.h>

class MessengerSpanish : public MessengerInterface, public ComponentInterface {
    public:
        MessengerSpanish();
        virtual ~MessengerSpanish();
        virtual std::string say();

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();
    private:
        std::string message;

        int referenceCounter;
        bool implemented;

};

MessengerSpanish::MessengerSpanish() :message ( "hola desde biblioteca MessengerSpanish" ) {}

MessengerSpanish::~MessengerSpanish() {}

std::string MessengerSpanish::say() {
    return message;
}

//ComponentInterface:
bool MessengerSpanish::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "MessengerInterface") ?
        implemented = true
            : implemented = false;
}

void* MessengerSpanish::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void MessengerSpanish::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new MessengerSpanish();
}

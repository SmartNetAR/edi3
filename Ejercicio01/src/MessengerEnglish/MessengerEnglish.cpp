#include <iostream>
#include <string>
#include <MessengerInterface.h>
#include <ComponentInterface.h>

class MessengerEnglish : public MessengerInterface, public ComponentInterface {
    public:
        MessengerEnglish();
        virtual ~MessengerEnglish();
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

MessengerEnglish::MessengerEnglish() :message ( "hello from MessengerEnglish library" ) {}

MessengerEnglish::~MessengerEnglish() {}

std::string MessengerEnglish::say() {
    return message;
}

//ComponentInterface:
bool MessengerEnglish::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "MessengerInterface") ?
        implemented = true
            : implemented = false;
}

void* MessengerEnglish::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void MessengerEnglish::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new MessengerEnglish();
}

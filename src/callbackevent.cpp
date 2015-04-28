#include "callbackevent.h"

CallbackEvent::CallbackEvent(std::function< void() > callbackFunction) : callback(callbackFunction)
{

}

void CallbackEvent::trigger()
{
	callback();
}

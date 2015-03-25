#include "goal.h"

using namespace std;

void Goal::trigger()
{
	if (check() && _callback) {
		_callback();
	}
}

void Goal::setCallback(function<void()> callback)
{
	_callback = callback;
}

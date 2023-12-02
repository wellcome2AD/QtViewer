#include "ConnResetEvent.h"

ConnResetEvent::ConnResetEvent(size_t con_num)
    : _con_num(con_num)
{}

eventType ConnResetEvent::GetEventType() const
{
    return connReset;
}

size_t ConnResetEvent::GetNumber() const
{
    return _con_num;
}

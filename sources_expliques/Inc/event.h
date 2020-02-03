#ifndef __EVENT_H__
#define __EVENT_H__
//-----------------------------------------------------------------------------
typedef unsigned char event;

void event_init( event *e );
void event_trigger( event *e );
int  event_check( event *e );

#endif

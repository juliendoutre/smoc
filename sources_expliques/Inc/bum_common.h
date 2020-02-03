#ifndef __BUMPER_PROTOCOL_H__
#define __BUMPER_PROTOCOL_H__

#include "main.h"
#include "event.h"

// ===========================================================================
// COMMON

// Debug buffer
#define RADIO_LOG_SIZE 5000
extern uint8_t radio_log[];

//-----------------------------------------------------------------------------
// Steps :
#define BUM_STEP_REGISTERED 0x00  // param: 0 = internal error, 1 = OK, 2 = OK but already registered, 3 = NO, too many players, 4 = NO, game already started
#define BUM_STEP_START      0x01  // param: always 0
#define BUM_STEP_RESULT     0x02  // param: id of winner
#define BUM_STEP_END        0x03  // param: always 0


// To be called when a char is received on the radio UART
void bum_notify_recv( uint8_t c );

// To be called each 10 ms
void bum_process( int ms );

#endif

#include <bum_common.h>
#include <xbee.h>

#include <bum_private.h>

uint8_t radio_log[ RADIO_LOG_SIZE ];

void bum_notify_recv( uint8_t c )
{
  xbee_notify_recv( c );
}

void bum_process( int ms )
{
	xbee_process( ms );
}

#include "accelerometer_handler.h"

void set_accelerometer_values(int8_t buffer[])
{
	acc_x = buffer[0];
	acc_y = buffer[1];
}

/*
 * fsdata_custom.c
 *
 *  Created on: 17 déc. 2019
 *      Author: julien
 */

#include "lwip/apps/fs.h"
#include <string.h>
#include "accelerometer_handler.h"
#include "web/includes/favicon.h"
#include "web/includes/index.h"
#include "web/includes/engine.h"
#include "bum_player.h"
#include "xbee.h"

#define FS_ROOT 0

const char ok[] = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/></head><body><p>OK</p></body></html>";
const char undefined_route_error[] = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/></head><body><p>Error 404</p></body></html>";
const char json_nil[] = "{}";
char buffer[100];

extern char json_orders[];
extern WebInterface wi;

int fs_open_custom(struct fs_file *file, const char *name)
{
	int len = 0;
	file->flags = 0;

	if (strcmp(name, "/favicon.ico") == 0)
	{
		len = img_favicon_size;
		file->data = (const char *)img_favicon;
	}
	else if (strcmp(name, "/orange.html") == 0)
	{
		HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
		file->data = ok;
		len = strlen(ok);
	}
	else if (strcmp(name, "/green.html") == 0)
	{
		HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
		file->data = ok;
		len = strlen(ok);
	}
	else if (strcmp(name, "/red.html") == 0)
	{
		HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
		file->data = ok;
		len = strlen(ok);
	}
	else if (strcmp(name, "/blue.html") == 0)
	{
		HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
		file->data = ok;
		len = strlen(ok);
	}
	else if (strcmp(name, "/index.html") == 0)
	{
		len = page_index_length;
		file->data = (char *)malloc(len + 1);
		strcpy((char *)file->data, page_index);
	}
	else if (strcmp(name, "/engine.js") == 0)
	{
		len = page_engine_length;
		file->data = (char *)malloc(len + 1);
		strcpy((char *)file->data, page_engine);
	}
	else if (strcmp(name, "/accelerometer.html") == 0)
	{
		char str[2000];
		sprintf(str, "x: %d, y: %d", acc_x, acc_y);
		file->data = str;
		len = strlen(str);
	}
	else if (strcmp(name, "/xbee_switch_to_api.html") == 0)
	{
		int r = xbee_AT_configure_API1();

		file->data = buffer;
		if (r == 0)
			len = sprintf(buffer, "SUCCESS");
		else
			len = sprintf(buffer, "ERROR %d", r);
	}
	else if (strcmp(name, "/xbee_log.html") == 0)
	{
		file->data = xbee_log_get();
		len = xbee_log_len();
	}
	else if (strncmp(name, "/register_player", 16) == 0)
	{
		file->data = ok;
		len = strlen(ok);

		wi.button_register_player = 1;
		event_trigger(&wi.evt);
	}
	else if (strcmp(name, "/!!") == 0)
	{
		len = strlen(json_orders);

		if (len > 6)
		{
			strcat(json_orders, "{}]}");
			len += 4;

			file->data = (char *)malloc(len + 1);
			file->flags |= 0x04; // Must be deleted later

			strcpy((char *)file->data, json_orders);

			strcpy(json_orders, "{\"L\":[");
		}
		else
		{
			file->data = json_nil;
			len = strlen(json_nil);
		}
	}
	else
	{
		file->data = undefined_route_error;
		len = strlen(undefined_route_error);
	}

	file->len = len;
	file->index = len;
	file->pextension = 0;
	// file->flags |= 0x04;

	return len;
}

/*-----------------------------------------------------------------------------*/
void fs_close_custom(struct fs_file *file)
{
	if (file->flags & 0x04)
	{
		free((char *)file->data);
	}

	file->data = 0;
	file->len = 0;
}

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

#define FS_ROOT 0

const char ok[] = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/></head><body><p>OK</p></body></html>";
const char undefined_route_error[] = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"/></head><body><p>Error 404</p></body></html>";

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
	else
	{
		file->data = undefined_route_error;
		len = strlen(undefined_route_error);
	}

	file->len = len;
	file->index = len;
	file->pextension = 0;
	file->flags |= 0x04;

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

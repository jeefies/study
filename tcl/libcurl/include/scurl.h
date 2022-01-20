#ifndef _SCURL_C_H_
#define _SCURL_C_H_
#include "buffer.h"
#include <curl/curl.h>
void scurl_init();
void scurl_quit();
char * scurl_err();
void scurl_set_err(const char * errmsg);
int scurl_err_l();

Buffer * get(const char * url);
#endif

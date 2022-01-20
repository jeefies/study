#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "buffer.h"

static int _scurl_inited = 0;
static CURL * gCurl = NULL;

char * _scurl_errMsg = NULL;

char * scurl_err() {
	return _scurl_errMsg;
}

int scurl_err_l() {
	return strlen(_scurl_errMsg);
}

void scurl_set_err(const char * errmsg) {
	static char * pre = "Get Error: ";
	static int prelength = 11;
	if (_scurl_errMsg != NULL) {
		free(_scurl_errMsg);
	}

	int length = strlen(errmsg);
	_scurl_errMsg = (char *)malloc(sizeof(char) * (length + 1 + prelength));
	memcpy(_scurl_errMsg, pre, prelength);
	memcpy(_scurl_errMsg + prelength, errmsg, length + 1);
}

void scurl_init() {
	curl_global_init(CURL_GLOBAL_ALL);
	gCurl = curl_easy_init();
}

void scurl_quit() {
	curl_easy_cleanup(gCurl);
	curl_global_cleanup();
}

size_t dataProcess(void *buffer, size_t chunkSize, size_t chunkNum, void * userData) {
	// if we don't use curl_easy_cleanup(.., CURLOPT_WRITEDATA, ..)
	// userData should be a null ptr
	Buffer *buf = (Buffer *)userData;
	int data_size = buffer_write(buf, (char *)buffer, chunkSize * chunkNum);
	return data_size;
}

Buffer * get(const char * url) {
	if (_scurl_inited == 0) {
		scurl_init();
		_scurl_inited = 1;
	}
	Buffer *buf = buffer_create(500);

	curl_easy_setopt(gCurl, CURLOPT_URL, url);
	curl_easy_setopt(gCurl, CURLOPT_WRITEFUNCTION, &dataProcess);
	curl_easy_setopt(gCurl, CURLOPT_WRITEDATA, buf);

	CURLcode res;
	res = curl_easy_perform(gCurl);
	if (res != CURLE_OK) {
		scurl_set_err(curl_easy_strerror(res));
		return NULL;
	}

	return buf;
}

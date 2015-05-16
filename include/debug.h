#ifndef DEBUG_H
#define DEBUG_H

#include "stdio.h"
#include "string.h"
#define LOG_BUF_SIZE 1024
void __error__(const char *s);
void __warning__(const char *s);
void __syslog__(const char *s);

void on_error(void (*callback)(const char *));
void on_warning(void (*callback)(const char *));
void on_syslog(void (*callback)(const char *));

char error_str[LOG_BUF_SIZE];
char error_buf[LOG_BUF_SIZE];
char warning_str[LOG_BUF_SIZE];
char warning_buf[LOG_BUF_SIZE];
char syslog_str[LOG_BUF_SIZE];
char syslog_buf[LOG_BUF_SIZE];
#define error(str, ...) {						\
	sprintf(error_str, "<ERROR> [%s:%s:%i] ", __FILE__, __func__, __LINE__); \
	sprintf(error_buf, str, ##__VA_ARGS__); strcat(error_str, error_buf); \
	__error__(error_str); }
#define warning(str, ...) { \
	sprintf(warning_str, "<WARNING> [%s:%s:%i] ", __FILE__, __func__, __LINE__); \
	sprintf(warning_buf, str, ##__VA_ARGS__); strcat(warning_str, warning_buf); \
	__warning__(warning_str); }
#define syslog(str, ...) { \
	sprintf(syslog_str, "<LOG> [%s:%s:%i] ", __FILE__, __func__, __LINE__); \
	sprintf(syslog_buf, str, ##__VA_ARGS__); strcat(syslog_str, syslog_buf); \
	__syslog__(syslog_str); }
#define memchk(DATA) { \
	if((DATA) == NULL) \
		error("Could not allocate memory"); }
#endif

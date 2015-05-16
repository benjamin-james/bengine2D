#include "debug.h"

typedef void (*error_callback)(const char *);
typedef void (*warning_callback)(const char *);
typedef void (*syslog_callback)(const char *);

#define MAX_CALLBACKS 30
static error_callback error_funcs[MAX_CALLBACKS];
static warning_callback warning_funcs[MAX_CALLBACKS];
static syslog_callback syslog_funcs[MAX_CALLBACKS];

static int n_error_funcs = 0;
static int n_warning_funcs = 0;
static int n_syslog_funcs = 0;

void on_error(error_callback a)
{
	if (n_error_funcs == MAX_CALLBACKS) {
		warning("Too many error functions! Please go back and clean up your darn code!");
		return;
	}
	error_funcs[n_error_funcs++] = a;
}
void on_warning(warning_callback a)
{
	if (n_warning_funcs == MAX_CALLBACKS) {
		warning("Cannot add another warning callback");
		return;
	}
	warning_funcs[n_warning_funcs++] = a;
}
void on_syslog(syslog_callback a)
{
	if (n_syslog_funcs == MAX_CALLBACKS) {
		warning("Cannot add another syslog callback");
		return;
	}
	syslog_funcs[n_syslog_funcs++] = a;
}
void __error__(const char *s)
{
	int i;
	for (i = 0; i < n_error_funcs; i++)
		error_funcs[i](s);
}
void __warning__(const char *s)
{
	int i;
	for (i = 0; i < n_warning_funcs; i++)
		warning_funcs[i](s);
}
void __syslog__(const char *s)
{
	int i;
	for (i = 0; i < n_syslog_funcs; i++)
		syslog_funcs[i](s);
}

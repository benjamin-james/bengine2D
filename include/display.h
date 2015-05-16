#ifndef DISPLAY_H
#define DISPLAY_H

#include "stdbool.h"
#include "SDL2/SDL.h"

#ifndef DEFAULT_W
#define DEFAULT_W 640
#endif

#ifndef DEFAULT_H
#define DEFAULT_H 480
#endif

void display_init(const char *title, Uint32 windowflags);
void display_set_fullscreen(bool fullscreen);
void display_get_fullscreen(void);
void display_set_title(const char *title);
void display_set_size(int w, int h);
int display_height(void);
int display_width(void);
float display_ratio(void);
void display_set_position(int x, int y);
void display_set_grab_cursor(bool grabbed);
bool display_get_grab_cursor(void);
void display_swap(void);
void display_handle_window_event(SDL_WindowEvent *e);

#endif

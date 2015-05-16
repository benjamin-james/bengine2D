#include "display.h"
#include "debug.h"

#include "stdbool.h"
#include "SDL2/SDL.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static Uint32 windowflags;
static int refresh_rate;

static void display_settings(void)
{
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	syslog("Current display mode is %dx%d @ %dhz", current.w, current.h, current.refresh_rate);
	refresh_rate = current.refresh_rate;
}
void display_init(const char *title, Uint32 window_flags)
{
	int err = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if (err < 0)
		error("Cannot initialize the video subsystem!");
	display_settings();
	windowflags = window_flags;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_W, DEFAULT_H, windowflags);
	if (!window)
		error("Couldn't create a window!");
	renderer = SDL_CreateRenderer(window, -1, 0); /* gives priority to SDL_RENDERER_ACCELERATED */
	if (!renderer)
		error("Couldn't create a renderer");
}
void display_set_fullscreen(bool fullscreen)
{
	if (fullscreen)
		windowflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	else
		windowflags &= !SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_SetWindowFullscreen(window, windowflags & SDL_WINDOW_FULLSCREEN_DESKTOP);
}
void display_get_fullscreen(void)
{
	return windowflags & SDL_WINDOW_FULLSCREEN_DESKTOP;
}
void display_set_title(const char *title)
{
	SDL_SetWindowTitle(window, title);
}
void display_set_size(int w, int h)
{
	SDL_SetWindowSize(window, w, h);
}
void display_handle_window_event(SDL_WindowEvent *e)
{
	
}

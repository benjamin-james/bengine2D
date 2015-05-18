#include "SDL2/SDL_rwops.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "dirent.h"
#include "unistd.h"

#ifdef _WIN32
#include "windows.h"
#include "winbase.h"
#elif __unix__
#include "execinfo.h"
#endif

#include "io/file.h"

/*
 * Windows has its own weird filesystem,
 * so there will be alot of ifdef's to
 * ensure cross platform usability
 */
struct filename filename_create(const char *path)
{
  struct filename f;
  if (expect_not(strlen(path) >= PATH_MAX))
    error("Filepath was too long: \"%s\"", path);
  else
    strcpy(f.ptr, path);
  return f;
}
struct filename filename_absolute(struct filename file)
{
	struct filename f;
	path_absolute(f.ptr, file.ptr);
	return f;
}
struct filename filename_file(struct filename file)
{
	struct filename f;
	path_file(f.ptr, file.ptr);
	return f;
}
struct filename filename_location(struct filename file)
{
	struct filename f;
	path_location(f.ptr, file.ptr);
	return f;
}
#ifdef _WIN32
void path_absolute(const char *path, char *ptr)
{
	GetFullPathName(path, PATH_MAX, ptr, NULL);
}
#elif __unix__
void path_absolute(const char *path, char *ptr)
{
	ptr = realpath(path, ptr);
}
#endif
void path_file(const char *path, char *ptr)
{
	int i = 0;
	int ext_location = 0;
	for (i = strlen(path); i > 0; i--) {
		if (path[i] == '/' || path[i] == '\\')
			break;
		if (path[i] == '.')
			ext_location = i;
	}
	const char *file = path + i + 1;
	int len = ext_location - i - 1;
	strncpy(ptr, file, len);
	ptr[len] = '\0';
}
void path_extension(const char *path, char *ptr)
{
	int i, ext_length = 0;
	for (i = strlen(path); i >= 0; i--) {
		if (path[i] == '.')
			break;
		ext_length++;
	}
	int prev = strlen(path) - ext_length + 1;
	const char *file_ext = path + prev;
	strcpy(ptr, file_ext);
}
void path_location(const char *path, char *ptr)
{
	int i;
	for (i = strlen(path); i > 0; i--)
		if (path[i] == '/' || path[i] == '\\')
			break;
	strncpy(ptr, path, i);
	ptr[i] = '\0';
}
void path_relative(const char *path, char *ptr)
{
	char *wd, *sub;
	pwd(wd);
	sub = strstr(path, wd);
	if (sub) {
		strcpy(ptr, ".");
		strcat(ptr, path + strlen(wd));
	} else {
		strcpy(ptr, path);
	}
}
void path_forward_slashes(char *path)
{
	int i, len = strlen(path);
	for (i = 0; i < len; i++)
		if (path[i] == '\\')
			path[i] = '/';
}
void path_join(char *p1, char *p2, char *ptr)
{

}
bool path_is_file(char *path)
{
	SDL_RWops *f = SDL_RWFromFile(path, "r");
	if (f) {
		SDL_RWclose(f);
		return 1;
	}
	return 0;
}
bool path_is_dir(char *path)
{
	DIR *d = opendir(path);
	if (d) {
		closedir(d);
		return 1;
	}
	return 0;
}
void path_parent_dir(const char *path, char *ptr)
{
	int i;
	for (i = strlen(path)-1; i > 0; i--)
		if (path[i] == '/' || path[i] == '\\')
			break;
	strncpy(ptr, path, i);
	ptr[i] = '\0';
}
static char working_dir[PATH_MAX];
void pwd(char *path)
{
	char *i_hate_warnings = getcwd(working_dir, sizeof(working_dir));
	path = working_dir;
}
int set_wd(char *dir)
{
	return chdir(dir);
}

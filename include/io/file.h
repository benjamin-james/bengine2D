#ifndef FILE_H
#define FILE_H
/*
 * Purpose - to ensure full cross
 * platform file compatibility
 */

#include "limits.h"
#ifndef PATH_MAX
#define PATH_MAX 512
#endif

#include "stdbool.h"

struct filename {
	char ptr[PATH_MAX];
};

struct filename filename_create(const char *path);
struct filename filename_absolute(struct filename file);
struct filename filename_file(struct filename file);
struct filename filename_location(struct filename file);

void path_absolute(const char *path, char *ptr);
void path_file(const char *path, char *ptr);
void path_extension(const char *path, char *ptr);
void path_location(const char *path, char *ptr);
void path_relative(const char *path, char *ptr);
void path_forward_slashes(char *path);
void path_join(char *p1, char *p2, char *ptr);

bool path_is_file(char *path);
bool path_is_dir(char *path);
void path_parent_dir(const char *path, char *ptr);

void pwd(char *path);
int set_wd(char *dir);

#endif

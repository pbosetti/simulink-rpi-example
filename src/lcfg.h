#ifndef LCFG_H
#define LCFG_H

#include <unistd.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <sys/param.h>
#include <libgen.h>

#ifndef LCFG_MAX_NAME_LEN
#define LCFG_MAX_NAME_LEN 256
#endif

#ifndef LCFG_GLOBAL_NAME
#define LCFG_GLOBAL_NAME "LCFG"
#endif

#ifndef LCFG_DEFAULT_PATH
#define LCFG_DEFAULT_PATH "/etc/vodisys_cfg.lua"
#endif

extern char _THIS_EXEC_PATH[MAXPATHLEN];
#ifndef __APPLE__
#define SET_THIS_EXEC_PATH(s) strcpy(_THIS_EXEC_PATH, s); dirname(_THIS_EXEC_PATH)
#else
#define SET_THIS_EXEC_PATH(s) snprintf(_THIS_EXEC_PATH, MAXPATHLEN, "%s", dirname((char *)s))
#endif

typedef double data_t;
typedef long int number_t;

struct lcfg {
  char cfg_file[MAXPATHLEN];
  char name[LCFG_MAX_NAME_LEN];
  lua_State *lua;
  int external_lua;
};

// Initialize the configuration object with a new embedded lua
//   name: the custom description of this configuration
//   basedir: the base path of the current executable, used to find the lua library cfg_tools.lua
//   cfg_file: the path to the lua configuration file
struct lcfg *cfg_new(const char name[LCFG_MAX_NAME_LEN], const char cfg_file[MAXPATHLEN]);

// Initialize the configuration object reusing an existing lua interpreter
struct lcfg *cfg_new_in_lua(lua_State *lua, const char name[LCFG_MAX_NAME_LEN], const char cfg_file[MAXPATHLEN]);

// free resources
void cfg_free(struct lcfg *lcfg);

// get a floating point data value at given path
// return 0.0 if not found
data_t cfg_get_data(struct lcfg *lcfg, const char *path);

// get an integer value at given path
// return 0 if not found
number_t cfg_get_number(struct lcfg *lcfg, const char *path);

// get a string value at given path
// return NULL pointer if not found!
char * cfg_get_string(struct lcfg *lcfg, const char *path, char **into);

// static int set_on_stack(struct lcfg *lcfg, const char *path);
// set a floating point data value at given path
// returns EXIT_FAILURE or EXIT_SUCCESS
int cfg_set_data(struct lcfg *lcfg, const char *path, data_t data);

// set an integer value at given path
// returns EXIT_FAILURE or EXIT_SUCCESS
int cfg_set_number(struct lcfg *lcfg, const char *path, number_t num);

// set a string value at given path (makes a copy of it!)
// returns EXIT_FAILURE or EXIT_SUCCESS
int cfg_set_string(struct lcfg *lcfg, const char *path, const char *str);

// save changes to configuration file
void cfg_save(struct lcfg *cfg);

// write current cfg to the given file
void cfg_write(struct lcfg *lcfg, const char *path);

// load the configuration file
void cfg_load(struct lcfg *lcfg, const char *path);

// reload the configuration file
void cfg_reload(struct lcfg *cfg);

#endif

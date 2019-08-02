#include <string.h>
#include <assert.h>
#include <libgen.h>

#include "lcfg.h"

char _THIS_EXEC_PATH[MAXPATHLEN];

struct lcfg *cfg_new(const char name[LCFG_MAX_NAME_LEN], const char cfg_file[MAXPATHLEN]) {
  struct lcfg *cfg;
  char *lua_path;
  assert(strlen(_THIS_EXEC_PATH) > 0);
  // Lua interpreter setup
  lua_State *lua = luaL_newstate();
  luaL_openlibs(lua);

  asprintf(&lua_path, "package.path = \"%s/../lua/?.lua;\"..package.path", _THIS_EXEC_PATH);

  if (luaL_dostring(lua, lua_path) != 0) {
    fprintf(stderr, "Errors setting package.path %s\n", lua_path);
    return NULL;
  }

  cfg = cfg_new_in_lua(lua, name, cfg_file);
  cfg->external_lua = 0;
  return cfg;
}

struct lcfg *cfg_new_in_lua(lua_State *lua, const char name[LCFG_MAX_NAME_LEN], const char cfg_file[MAXPATHLEN]) {
  assert(strlen(_THIS_EXEC_PATH) > 0);
  char *cfg_this_path = NULL;
  struct lcfg *cfg;
  if (!(cfg = (struct lcfg *)malloc(sizeof(struct lcfg)))) {
    fprintf(stderr, "Could not allocate memory for lua config object\n");
    return NULL;
  }
  strncpy(cfg->cfg_file, cfg_file, strlen(cfg_file));
  strncpy(cfg->name, name, strlen(name));
  asprintf(&cfg_this_path, "%s/../lua/lcfg.lua", _THIS_EXEC_PATH);
  cfg->lua = lua;
  if (luaL_dofile(cfg->lua, cfg_this_path) == 1) {
    fprintf(stderr, "Error in lua script %s:\n%s\n", cfg_this_path, lua_tostring(cfg->lua, -1));
    return NULL;
  }
  lua_setglobal(cfg->lua, LCFG_GLOBAL_NAME);
  cfg_load(cfg, cfg_file);
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME);
  lua_pushstring(cfg->lua, name);
  lua_setfield(cfg->lua, -2, "name");
  lua_pop(cfg->lua, 2);
  cfg->external_lua = 1;
  return cfg;
}

void cfg_free(struct lcfg *cfg) {
  assert(cfg);
  // only close lua if it is embedded in LCFG
  if (cfg->external_lua == 0) {
    lua_close(cfg->lua);
  }
  free(cfg);
}

static int get_on_stack(struct lcfg *cfg, const char *path) {
  int n = lua_gettop(cfg->lua);
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME); // n + 1
  lua_getfield(cfg->lua, -1, "get"); // n + 2
  lua_pushvalue(cfg->lua, -2); // n + 3
  lua_pushstring(cfg->lua, path); // n + 4
  if (lua_pcall(cfg->lua, 2, 1, 0) != 0) { // n -3 + 1 = n + 2
    const char *s = lua_tostring(cfg->lua, -1);
    fprintf(stderr, "Lua error: %s\n", s);
    return 0;
  }
  return lua_gettop(cfg->lua) - n; // 2
}

data_t cfg_get_data(struct lcfg *cfg, const char *path) {
  data_t r = 0;
  int n = get_on_stack(cfg, path);
  if (n) { 
    r = luaL_checknumber(cfg->lua, -1);
    lua_pop(cfg->lua, n);
    return r;
  }
  else {
    return 0;
  }
}

number_t cfg_get_number(struct lcfg *cfg, const char *path) {
  number_t r = 0;
  int n = get_on_stack(cfg, path);
  if (n) {
    r = luaL_checkinteger(cfg->lua, -1);
    lua_pop(cfg->lua, n); // 0
    return r;
  }
  else {
    return 0;
  }
}

char * cfg_get_string(struct lcfg *cfg, const char *path, char **into) {
  char *r;
  int n = get_on_stack(cfg, path);
  if (n) {
    r = (char *)luaL_checkstring(cfg->lua, -1); // 2
    lua_pop(cfg->lua, n); // 0
    if (into) {
      asprintf(into, "%s", r);
    }
    return r;
  }
  else {
    return NULL;
  }
}

static int set_on_stack(struct lcfg *cfg, const char *path) {
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME); // n + 1
  lua_getfield(cfg->lua, -1, "set"); // n + 2
  lua_pushvalue(cfg->lua, -2); // n + 3
  lua_pushstring(cfg->lua, path); // n + 4
  lua_pushvalue(cfg->lua, -5); // n + 5
  if (lua_pcall(cfg->lua, 3, 1, 0) != 0) { // n - 4 + 1 = n + 2
    lua_pop(cfg->lua, 2);
    const char *s = lua_tostring(cfg->lua, -1);
    fprintf(stderr, "Lua error: %s\n", s);
    return EXIT_FAILURE;
  }
  lua_pop(cfg->lua, 2);
  return EXIT_SUCCESS;
}

int cfg_set_data(struct lcfg *cfg, const char *path, data_t data) {
  lua_pushnumber(cfg->lua, data);
  return set_on_stack(cfg, path);
}

int cfg_set_number(struct lcfg *cfg, const char *path, number_t num) {
  lua_pushinteger(cfg->lua, num);
  return set_on_stack(cfg, path);
}

int cfg_set_string(struct lcfg *cfg, const char *path, const char *str) {
  lua_pushstring(cfg->lua, str);
  return set_on_stack(cfg, path);
}

void cfg_save(struct lcfg *cfg) {
  cfg_write(cfg, cfg->cfg_file);
}

void cfg_write(struct lcfg *cfg, const char *path) {
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME); // n + 1
  lua_getfield(cfg->lua, -1, "write"); // n + 2
  lua_pushvalue(cfg->lua, -2); // n + 3
  lua_pushstring(cfg->lua, path);
  if (lua_pcall(cfg->lua, 2, 0, 0) != 0) { // n - 4 + 1 = n + 2
    const char *s = lua_tostring(cfg->lua, -1);
    fprintf(stderr, "Lua error: %s\n", s);
    exit(EXIT_FAILURE);
  }
  lua_pop(cfg->lua, 1);  
}

void cfg_load(struct lcfg *cfg, const char *path) {
  strncpy(cfg->cfg_file, path, strlen(path));
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME); // n + 1
  lua_getfield(cfg->lua, -1, "load"); // n + 2
  lua_pushvalue(cfg->lua, -2); // n + 3
  lua_pushstring(cfg->lua, path);
  if (lua_pcall(cfg->lua, 2, 0, 0) != 0) { // n - 4 + 1 = n + 2
    const char *s = lua_tostring(cfg->lua, -1);
    fprintf(stderr, "Lua error: %s\n", s);
    exit(EXIT_FAILURE);
  }
  lua_pop(cfg->lua, 1);
}

void cfg_reload(struct lcfg *cfg) {
  lua_getglobal(cfg->lua, LCFG_GLOBAL_NAME); // n + 1
  lua_getfield(cfg->lua, -1, "reload"); // n + 2
  lua_pushvalue(cfg->lua, -2); // n + 3
  if (lua_pcall(cfg->lua, 1, 0, 0) != 0) {
    const char *s = lua_tostring(cfg->lua, -1);
    fprintf(stderr, "Lua error: %s\n", s);
    exit(EXIT_FAILURE);
  }
  lua_pop(cfg->lua, 1);
}

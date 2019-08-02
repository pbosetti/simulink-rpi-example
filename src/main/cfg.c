#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "../defines.h"
#include "../lcfg.h"

#ifndef LCFG_MAX_STR_LEN
#define LCFG_MAX_STR_LEN 256
#endif

typedef union {
  char s[LCFG_MAX_STR_LEN];
  long int i;
  double f;
} var_type;

int main(int argc, char *argv[]) {
  int opt;
  char config_file[MAXPATHLEN] = LCFG_DEFAULT_PATH;
  char *cfg_path = NULL;
  struct lcfg *cfg;
  char *name;
  var_type cfg_value;
  char write = '\0';

  while ((opt = getopt(argc, argv, "c:i:f:s:?h")) != -1) {
    switch (opt) {
      case 'c':
        memset(config_file, 0, MAXPATHLEN);
        if (optarg[0] == '.') {
          strncpy(config_file, optarg, strlen(optarg));
        }
        else {
          strncat(cfg_value.s, "./", 2);
          strncat(config_file, optarg, strlen(optarg));
        }
        break;
      case 'i':
        cfg_value.i = atoi(optarg);
        write = 'i';
        break;
      case 'f':
        cfg_value.f = atof(optarg);
        write = 'f';
        break;
      case 's':
        strncpy(cfg_value.s, optarg, strlen(optarg));
        write = 's';
        break;
      case '?':
      case 'h':
        printf("%s\
        \nUsage: %s [options] {cfg_section}.{cfg_value}\
        \nOptions:\
        \n\t-c<path>  path to config file\
        \n\t-i{value} integer value to be set\
        \n\t-f{value} float value to be set\
        \n\t-s{value} string value to be set\
        \n\t-h|?:     this help\n", basename((char*)argv[0]), basename((char*)argv[0]));
        return 0;
        break;
      default:
        abort();
    }
  }

  if (argc - optind != 1) {
    fprintf(stderr, "Missing mandatory config path argument!\n");
    return EXIT_FAILURE;
  }

  cfg_path = argv[optind];

  // Create the cfg object, arguments are:
  // 1. conventional name of the cfg
  // 2. path to the directory (dirname) of the current executable
  // 3. path to the config file
  // both paths are absolute or relative to the current working directory!
  if (!(cfg = cfg_new("Test configuration file", config_file))) {
    return EXIT_FAILURE;
  }

  switch (write) {
    case 'i':
      printf("Setting %s=%ld\n", cfg_path, cfg_value.i);
      cfg_set_number(cfg, cfg_path, cfg_value.i);
      cfg_save(cfg);
      break;
    case 'f':
      printf("Setting %s=%f\n", cfg_path, cfg_value.f);
      cfg_set_data(cfg, cfg_path, cfg_value.f);
      cfg_save(cfg);
      break;
    case 's':
      printf("Setting %s='%s'\n", cfg_path, cfg_value.s);
      cfg_set_string(cfg, cfg_path, cfg_value.s);
      cfg_save(cfg);
      break;
    default:
      cfg_get_string(cfg, cfg_path, &name);
      // printf("%s = %s\n", cfg_path, name);
      printf("%s: %s\n", cfg_path, name);
      free(name);
  }

  cfg_free(cfg);
  return EXIT_SUCCESS;
}

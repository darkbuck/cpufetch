#include "udev.h"

#define _PATH_TOPO_CORE_ID    "topology/core_id"
#define _PATH_TOPO_PACKAGE_ID "topology/physical_package_id"

bool fill_core_ids_from_sys(int *core_ids, int total_cores) {
  int filelen;
  char* buf;
  char* end;
  char path[128];

  for(int i=0; i < total_cores; i++) {
    sprintf(path, "%s%s/cpu%d/%s", _PATH_SYS_SYSTEM, _PATH_SYS_CPU, i, _PATH_TOPO_CORE_ID);
    if((buf = read_file(path, &filelen)) == NULL) {
      perror("open");
      return false;
    }

    errno = 0;
    core_ids[i] = strtol(buf, &end, 10);
    if(errno != 0) {
      perror("strtol");
      return false;
    }
    free(buf);
  }

  return true;
}

bool fill_package_ids_from_sys(int* package_ids, int total_cores) {
  int filelen;
  char* buf;
  char* end;
  char path[128];

  for(int i=0; i < total_cores; i++) {
    sprintf(path, "%s%s/cpu%d/%s", _PATH_SYS_SYSTEM, _PATH_SYS_CPU, i, _PATH_TOPO_PACKAGE_ID);
    buf = read_file(path, &filelen);

    errno = 0;
    package_ids[i] = strtol(buf, &end, 10);
    if(errno != 0) {
      perror("strtol");
      return -1;
    }
    free(buf);
  }
}

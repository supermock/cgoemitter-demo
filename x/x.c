#include "x.h"

void check_err_cgoemitter_args_halloc_arg(void* value) {
  if (value == NULL) puts("Failed on cgoemitter_args_halloc_arg()");
}

void check_err_cgoemitter_args_add_arg(int code) {
  if (code == EXIT_FAILURE) puts("Failed on cgoemitter_args_add_arg()");
}

void say(char* text) {
  char message_result[256];
  sprintf(message_result, "Parameter sent to C language: %s", text);

  cgoemitter_args_t cgoemitter_args = cgoemitter_new_args(1);

	void* message_result_arg = cgoemitter_args_halloc_arg(&message_result, (strlen(message_result)+1) * sizeof(char));
  check_err_cgoemitter_args_halloc_arg(message_result_arg);
  check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &message_result_arg));

  emit("message", &cgoemitter_args);
}

void sys_info() {
  struct utsname uname_info;
  uname(&uname_info);

  struct SysInfo sys_info;
  sys_info.SysName = uname_info.sysname;
  sys_info.NodeName = uname_info.nodename;
  sys_info.Release = uname_info.release;
  sys_info.Version = uname_info.version;
  sys_info.Machine = uname_info.machine;

  cgoemitter_args_t cgoemitter_args = cgoemitter_new_args(1);

  void* sys_info_arg = cgoemitter_args_halloc_arg(&sys_info, sizeof(struct utsname));
  check_err_cgoemitter_args_halloc_arg(sys_info_arg);
  check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &sys_info_arg));

  emit("sys-info", &cgoemitter_args);
}

void raw_sys_info() {
  struct utsname uname_info;
  uname(&uname_info);

  cgoemitter_args_t cgoemitter_args = cgoemitter_new_args(1);

  void *sys_info_arg = cgoemitter_args_halloc_arg(&uname_info, sizeof(struct utsname));
  check_err_cgoemitter_args_halloc_arg(sys_info_arg);
  check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &sys_info_arg));

  emit("raw-sys-info", &cgoemitter_args);
}

void* worker_scope(void* vargp) {
  char* id = (char*)vargp;
  int count = 0;
  
  srand(time(NULL));

  for (;;) {
    sleep(1);

    int random_value = 0;

    if (++count <= 5) random_value = rand() % 100 + 1;

    cgoemitter_args_t cgoemitter_args = cgoemitter_new_args(2);

    void* id_arg = cgoemitter_args_halloc_arg(id, (strlen(id)+1) * sizeof(char));
    check_err_cgoemitter_args_halloc_arg(id_arg);
    check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &id_arg));

    void* random_value_arg = cgoemitter_args_halloc_arg(&random_value, sizeof(int));
    check_err_cgoemitter_args_halloc_arg(random_value_arg);
    check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &random_value_arg));

    emit("worker", &cgoemitter_args);

    if (count == 6) break;
  }

  free(vargp);

  return NULL;
}

void start_work(char* id) {
  pthread_t tid;
  pthread_create(&tid, NULL, worker_scope, (void*)id);
}

void unknown() {
  int value = 10;

  cgoemitter_args_t cgoemitter_args = cgoemitter_new_args(1);

	void* value_arg = cgoemitter_args_halloc_arg(&value, sizeof(int));
  check_err_cgoemitter_args_halloc_arg(value_arg);
  check_err_cgoemitter_args_add_arg(cgoemitter_args_add_arg(&cgoemitter_args, &value_arg));

  emit("unknown", &cgoemitter_args);
}
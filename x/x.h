#ifndef X_H_
#define X_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include "../../cgoemitter/cgoemitter.h"

/*
This structure was created because the structure 'struct utsname' 
follows the C pattern with the name of the properties with lowercase, 
so you can not access them in GO because they are private properties.
*/
struct SysInfo {
  char* SysName;
	char* NodeName;
	char* Release;
	char* Version;
	char* Machine;
};

void say(char* text);
void sys_info();
void start_work(char* id);
void unknown();

#endif
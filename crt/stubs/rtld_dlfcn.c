/* Copyright (C) 2025 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */


/**
 * Standard posix macros.
 **/
#define ENOENT 2
#define ENOMEM 12
#define EINVAL 22
#define ENOSYS 78

#define RTLD_NEXT    ((void*)-1)
#define RTLD_DEFAULT ((void*)-2)
#define RTLD_SELF    ((void*)-3)

#define RTLD_LAZY     0x0001
#define RTLD_NOW      0x0002
#define RTLD_MODEMASK 0x0003
#define RTLD_GLOBAL   0x0100
#define RTLD_LOCAL    0x0000
#define RTLD_TRACE    0x0200
#define RTLD_NODELETE 0x1000
#define RTLD_NOLOAD   0x2000


/**
 * Dependencies to standard libraries.
 **/
static char* (*_Strerror)(int, char*) = 0;
static void* (*calloc)(unsigned long, unsigned long) = 0;
static void (*free)(void*) = 0;
static char** (*getargv)(void) = 0;
static int (*getargc)(void) = 0;
static char** environ = 0;


/**
 * Global variables.
 **/


void*
__dlopen(const char *filename, int flags) {
return 0;
}


int
__dladdr(void *addr, void *info) {
  return 0;
}


void*
__dlsym(void *handle, const char *symbol) {

  return 0;
}


int
__dlclose(void *handle) {
return 0;
}


char*
__dlerror(void) {

  return 0;
}


void __rtld_dlfcn_setroot(void *lib) {

}


int
__rtld_dlfcn_init(void) {
  return 0;
}


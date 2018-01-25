package x

// The LDFLAGS lines below are needed to prevent linker errors
// since not all packages are present while building intermediate
// packages. The darwin build tag is used as a proxy for clang
// versus gcc because there doesn't seem to be a better way
// to detect this.

/*
#cgo darwin LDFLAGS: -Wl,-undefined -Wl,dynamic_lookup
#cgo !darwin LDFLAGS: -Wl,-unresolved-symbols=ignore-all
#include <stdlib.h>
#include "x.h"
*/
import "C"
import "unsafe"

//Run | Execute C function
func Run() {
	message := C.CString("Hello from CGOEmitter!")
	C.say(message)
	C.free(unsafe.Pointer(message))

	C.sys_info()
}

//StartWork | Starts a new job (thread)
func StartWork(id string) {
	C.start_work(C.CString(id)) //Release the string when work is done. free()
}

package main

//#include "x/x.h" //This library has been imported so that the 'C.struct_SysInfo' structure can be accessed
import "C"

import (
	"fmt"
	"sync"

	"github.com/supermock/cgoemitter"
	"github.com/supermock/cgoemitter/parser"

	"github.com/supermock/cgoemitter-demo/x"
)

//SysInfo | Representation of the structure in C
type SysInfo struct {
	SysName  string
	NodeName string
	Release  string
	Version  string
	Machine  string
}

func main() {
	var wg sync.WaitGroup
	wg.Add(5)

	//For more information look at CGOEmitter (golang package) -> README.md
	cgoemitter.On("cgoemitter-warnings", cgoemitter.NewListener(func(args cgoemitter.Arguments) {
		fmt.Println("[WARNING]", args.String(0))
		wg.Done()
	}))

	cgoemitter.On("message", cgoemitter.NewListener(func(args cgoemitter.Arguments) {
		fmt.Printf("Receveid message from Golang: %s\n", args.String(0))
		wg.Done()
	}))

	cgoemitter.On("sys-info", cgoemitter.NewListener(func(args cgoemitter.Arguments) {
		sysInfo := SysInfo{}

		if err := parser.CStructToGoStruct((*C.struct_SysInfo)(args.Arg(0)), &sysInfo); err != nil {
			fmt.Printf("Failed on parse C.struct_SysInfo to GO.struct_SysInfo. Err: %s\n", err.Error())
		}

		fmt.Printf("Receveid system information: %+v\n", sysInfo)
		wg.Done()
	}))

	cgoemitter.On("worker", cgoemitter.NewListener(func(args cgoemitter.Arguments) {
		fmt.Printf("[%s] Received from worker: %d\n", args.String(0), args.Int(1))

		if args.Int(1) == 0 {
			fmt.Println("Work completed successfully!")
			wg.Done()
		}
	}))

	x.Run()

	x.StartWork("ID01")
	x.StartWork("ID02")

	wg.Wait()
}

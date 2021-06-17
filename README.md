# On the Runtime and Energy Performance of WebAssembly
#### Checking Energy Consumption and Runtime Performance between WebAssembly, JavaScript (asm.js) and C, using 10 microbenchmarks as case study.

### What is this?

This repo contains the source code of 10 distinct benchmarks, implemented in WebAssembly, JavaScript and C. Using Emscripten as a compiler, WebAssembly and Javascript were generated from a C source code.

### How is it structured and hows does it work?

This framework follows a specific folder structure, which guarantees the correct workflow when the goal is to perform and operation for all benchmarks.
Moreover, it must be defined, for each benchmark, how to perform the operations considered.

Next, we explain the folder structure and how to specify, for each language benchmark, the execution of each operation.

#### The Structure
The main folder contains 4 elements: 
1. A `Benchmarks` sub-folder, containing a folder for each microbenchmark.
2. A `PlotsData` sub-folder, containing all the plots generated from jupyter notebook.
3. A `RAPL` sub-folder, containing the code of the energy measurement framework.
4. A `emsdk` subfolder, containing [Emscripten SDK](https://github.com/emscripten-core/emsdk).

Basically, the directories tree will look something like this:

```Java
| Benchmarks
	| <Benchmark-1>
		| Large_dataset
			| C
				| Results
					| benchmarkLARGE1.rapl
					| benchmarkLARGE1.time
					| ...
				| Makefile
				| benchmark_runLARGE
			| JS
				| Results
					| benchmarkLARGE1.rapl
					| benchmarkLARGE1.time
					| ...
				| Makefile
				| benchmark_runJS_LARGE.js
				| benchmark_runJS_LARGE.js.mem
			| WASM
				| Results
					| benchmarkLARGE1.rapl
					| benchmarkLARGE1.time
					| ...
				| Makefile
				| benchmark_runWASM_Large.js
				| benchmark_runWASM_Large.wasm
			| Makefile
			| benchmarkLARGE.csv
		| Medium_dataset
			| ...
		| Small_dataset
			| ...
		benchmark.c
		datasets.h
		inputgen.c
		Makefile
	| ...
	| <Benchmark-10>
	| ExampleFolder
| emsdk
| Plotsdata
| RAPL
| compile_all.py
| gen-input.sh

```

### Running an example.

To understand how this system works let's add and run an example.

1. Take a microbenchmark in language C, for example, `fibonacci.c`.

2. In [`ExampleFolder`](https://github.com/OnThePerformanceofWebAssembly/PerformanceOfWebAssembly/tree/main/Benchmarks/ExampleFolder) (change its name if you want to) replace `example.c` for `fibonacci.c`.

3. Deal with input. The microbenchmarks can´t receive input as an argument, so, you need to add the three differents inputs sizes in a header called `datasets.h`. For example, if you want the `Small`, `Medium` and `Large` inputs to be 1, 2 and 3, respectively, the `datasets.h` will be like this:

```Java
#ifdef SMALL_DATASET
#define INPUT 1
#endif
#ifdef LARGE_DATASET
#define INPUT 3
#endif

#ifndef SMALL_DATASET
  #ifndef LARGE_DATASET
    #ifndef MEDIUM_DATASET
      #define MEDIUM_DATASET
    #endif
  #endif
#endif

#ifdef MEDIUM_DATASET
#define INPUT 2
#endif
```

4. Now you just need to change the input that was received as an argument `argv[1]` for `Input`, like this:

	**Before:** `int n = argv[1];`
	
	**After:** `int n = INPUT;`

5. The next step is the preparation of all the Makefiles inside `ExampleFolder`. In each benchmark, you need to replace all `example.c` for the name of your benchmark, in this case, `fibonacci.c`.

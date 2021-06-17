# On the Runtime and Energy Performance of WebAssembly
#### Checking Energy Consumption and Runtime Performance between WebAssembly, JavaScript (asm.js) and C, using 10 microbenchmarks as case study.

### What is this?

This repo contains the source code of 10 distinct benchmarks, implemented in WebAssembly, JavaScript and C. Using Emscripten as a compiler, WebAssembly and Javascript were generated from a C source code.

### How is it structured and hows does it work?

This framework follows a specific folder structure, which guarantees the correct workflow when the goal is to perform and operation for all benchmarks at once.
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
| emsdk
| Plotsdata
| RAPL
| compile_all.py
| gen-input.sh

```
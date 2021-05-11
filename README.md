# On the Runtime and Energy Performance of WebAssembly
On the Runtime and Energy Performance of WebAssembly

### What is this?

This repo contains the source code of 10 distinct benchmarks, implemented in WebAssembly, JavaScript and C. Using Emscripten as a compiler, WebAssembly and Javascript were generated from a C source code.

### How is it structured and hows does it work?

This framework follows a specific folder structure, which guarantees the correct workflow when the goal is to perform and operation for all benchmarks at once.
Moreover, it must be defined, for each benchmark, how to perform the operations considered.

Next, we explain the folder structure and how to specify, for each language benchmark, the execution of each operation.

#### The Structure

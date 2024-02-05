# WebNQC README

> "Not Quite C is a simple language with a C-like syntax that can be used to program Lego's RCX programmable brick (from the MindStorms set). If you are just getting started with programming, then graphical environments such as the MindStorms RIS software or Robolab are probably better choices. If, however, you're a C programmer and prefer typing a few lines to drag and drop icon programming, then NQC might be perfect for you."

This repository is used to compile **NQC as WebAssembly bytecode (WASM)** so that we can run it in a web browser - without any installation and independent of your machine's platform (Windows, Linux, MacOS, etc).

This version of NQC has been forked from [BrickBot/nqc](https://github.com/BrickBot/nqc) which itself is based on version 3.1r6 code as found on
[BricxCC](http://bricxcc.sourceforge.net/nqc/). Several files may have been removed and functionality can be reduced (e.g. no IR tower communication).

## Build

Build the `mkdata` utility which is required by the next step:

```shell
make -f Makefile.mkdata
```

Build NQC using [Emscripten Compiler Frontend (emcc)](https://emscripten.org/docs/tools_reference/emcc.html):

```shell
emmake make CXX=emcc
```

>"Emscripten build output consists of two essential parts: 
>
>1) the low level compiled code module and
>2) the JavaScript runtime to interact with it.
>
>For example, when building with `-o out.html`, the compiled code is stored in a file `out.wasm` and the runtime lives in a file `out.js`."
>
> _(from https://emscripten.org/docs/compiling/Deploying-Pages.html)_

So, let's check the results and try to run NQC WASM locally:

```shell
$ cd bin

$ ls
nqc.html nqc.js nqc.wasm

$ node nqc.js
nqc version 3.2 r1 (built Feb  5 2024, 13:37:42)
     Copyright (C) 2005 John Hansen.  All Rights Reserved.
Usage error: try 'nqc -help' to display options
```

Looks good so far! Now, let's run it from a local web server (from folder `./bin/`, using Python):

```shell
python -m http.server 8080
```

For interaction open the HTML shell. This is done by opening http://localhost:8080/nqc.html in your favorite web browser.

> "Emscripten provides a **default HTML shell** file that serves as a launcher to run the code, simplified to get started with development. However when getting ready to release and host the content on a web site, a number of extra features and customizations are likely needed to polish the visitor experience. This guide highlights things to pay attention to when deploying sites to the public."
> 
> _(from https://emscripten.org/docs/compiling/Deploying-Pages.html)_

Currently, NQC source code from an HTML `textarea` input is used as NQC's input. NQC is used to generate a listing and the bytecode.


## TODOs and visions

- Remove unwanted features or at least their accessibility; especially bytecode download functions
- Add CI pipeline (e.g. GitHub Actions) for automatic build & semi-automatic relase
- Implement support for download of bytecode to the RCX using the [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API) for IR tower access
- Allow _real_ interaction: make NQC input file `textarea` writable and add button to re-compile the code
- Add feature to switch between different source files and keep them (locally?) for longer than a browser session
- Add feature to share projects with others
- Make the UI nice for good UX
- Add i18n support
- Add [Blockly](https://developers.google.com/blockly) support for visual programming and generate NQC code from it (should be another project which uses WebNQC behind the scenes)

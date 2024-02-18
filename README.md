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

There are some details, hidden in the `Makefile`: a custom shell file is used. What does that mean?

>"Emscripten build output consists of two essential parts: 
>
>1) the low level compiled code module and
>2) the JavaScript runtime to interact with it.
>
>For example, when building with `-o out.html`, the compiled code is stored in a file `out.wasm` and the runtime lives in a file `out.js`."
>
> _(from https://emscripten.org/docs/compiling/Deploying-Pages.html)_


> "Emscripten provides a **default HTML shell** file that serves as a launcher to run the code, simplified to get started with development. However when getting ready to release and host the content on a web site, a number of extra features and customizations are likely needed to polish the visitor experience. This guide highlights things to pay attention to when deploying sites to the public."
> 
> _(from https://emscripten.org/docs/compiling/Deploying-Pages.html)_

Due to the chosen settings, running the NQC WASM locally with node, won't show anything:

```shell
$ cd bin

$ ls
nqc.html nqc.js nqc.wasm

$ node nqc.js

$
```

Time to start a local web server using Python - from that same `./bin/` folder:

```shell
python -m http.server 8080
```

We do this because "several browsers (including Chrome, Safari, and Internet Explorer) do not support `file://` XHR requests, and can’t load extra files needed by the HTML (like a .wasm file, or packaged file data as mentioned lower down)."

For user interaction open the HTML shell: browse to  http://localhost:8080/nqc.html in your favorite web browser that is capable of working with WASM.

Enter your NQC source code in the very first textarea and hit the "Compile with NQC" button.


## TODOs and visions

- Add feature to download the compiled `.rcx` file to a LEGO Mindstorms RCX programmable brick using an IR tower. (That's another PoC I am currently working on: adding support for download of bytecode to the RCX using the [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API) for IR tower access.)
- Remove unwanted features or at least their accessibility; especially bytecode download functions
- Add CI pipeline (e.g. GitHub Actions) for automatic build & semi-automatic relase
- Add feature to share projects with others
- Make the UI nice for good UX
- Add i18n support
- Add [Blockly](https://developers.google.com/blockly) support for visual programming and generate NQC code from it (should be another project which uses WebNQC behind the scenes)
- Add syntax highlighting to the editor (`textarea`)
- Add parsing of error message, e.g. to highlight the first line (or all lines) where an error is indicated

I'll also post updates here: https://chaos.social/@maehw

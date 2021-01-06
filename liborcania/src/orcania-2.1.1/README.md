# Orcania

Potluck with different functions for different purposes that can be shared among C programs.

[![Build Status](https://travis-ci.com/babelouest/orcania.svg?branch=master)](https://travis-ci.com/babelouest/orcania)
![.github/workflows/ccpp.yml](https://github.com/babelouest/orcania/workflows/.github/workflows/ccpp.yml/badge.svg)

## Documentation

Library documentation is available in the [online documentation](https://babelouest.github.io/orcania/).

## Installation

### Distribution packages

[![Packaging status](https://repology.org/badge/vertical-allrepos/orcania.svg)](https://repology.org/metapackage/orcania)

Orcania is available in multiple distributions as official package. Check out your distribution documentation to install the package automatically.

### Pre-compiled packages

You can install Orcania with a pre-compiled package available in the [release pages](https://github.com/babelouest/orcania/releases/latest/).

### Build from source

Download Orcania source code from Github:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania
```

#### CMake - Multi architecture

[CMake](https://cmake.org/download/) minimum 3.5 is required.

Run the cmake script in a subdirectory, example:

```shell
$ git clone https://github.com/babelouest/orcania.git
$ cd orcania/
$ mkdir build
$ cd build
$ cmake ..
$ make && sudo make install
```

The available options for cmake are:
- `-DBUILD_STATIC=[on|off]` (default `off`): Build the static archive in addition to the shared library
- `-DWITH_STRSTR=[on|off]` (default `off`): Force using inline implementation of strstr
- `-DBUILD_ORCANIA_TESTING=[on|off]` (default `off`): Build unit tests
- `-DINSTALL_HEADER=[on|off]` (default `on`): Install header file `orcania.h`
- `-DBUILD_RPM=[on|off]` (default `off`): Build RPM package when running `make package`
- `-DBUILD_ORCANIA_DOCUMENTATION=[on|off]` (default `off`): Build the documentation, doxygen is required
- `-DCMAKE_BUILD_TYPE=[Debug|Release]` (default `Release`): Compile with debugging symbols or not

#### Good ol' Makefile - Linux only

Go to `src/` directory, compile and install:

```shell
$ cd src
$ make && sudo make install
```

This will install Orcania's files under `/usr/local/` DESTDIR.

If you want to force using inline implementation of `strstr`, you can append the build option `STRSTRFLAG=1`. This is useful if your systemdoesn't have an implementation of the function `strstr` but isn't listed as one in Orcania. Like FreeRTOS.

```
$ cd src
$ make STRSTRFLAG=1
```

To build and install as a static archive, use the make commands `make static*`:

```shell
$ cd src
$ make static && sudo make static-install # or make DESTDIR=/tmp static-install if you want to install in `/tmp/lib`
```

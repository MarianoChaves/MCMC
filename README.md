# nuMCMC-c++
The MCMC algorithm using C++: based on <a href=https://emcee.readthedocs.io/en/stable/ >emcee</a>

<p align="center">🚀 This library can be used to create samplings using Markov chain Monte Carlo (MCMC).</p>

<img src="https://img.shields.io/static/v1?label=version&message=v0.2&color=blue&style=for-the-badge&logo=c++"/> <img src="https://img.shields.io/static/v1?label=license&message=MIT&color=blue&style=for-the-badge&logo=none"/>

Here you can find a <a href=https://marianochaves.github.io/mcmc.html>Quick Start</a> on the nuMCMC.

### Cite as:
Mariano Esteves Chaves. (2021). The MCMC algorithm using C++ (0.2). Zenodo. https://doi.org/10.5281/zenodo.5496330

## v. 0.2
* Inclusion of the working parallelized version of the code: "run_parallel()";

## v. 0.1
* Working code;
* Save and load states;
* Save history functions;

For further information contact mchaves@ifi.unicamp.br

## Compiler options

### For Windows

Compiler MinGW-w64 in [Msys2](https://www.msys2.org/) is tested.

```
cmake ../ -DCMAKE_CXX_STANDARD=11
ninja -f build.ninja
```

*Prerequisite in Msys2*
```
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-ninja
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

### For Linux
```
cmake ../ -DCMAKE_CXX_STANDARD=11
make -j2
```
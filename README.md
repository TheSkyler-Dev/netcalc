# Netcalc


![Static Badge](https://img.shields.io/badge/License-GNU_GPL--v3.0-blue?style=flat&link=https%3A%2F%2Fwww.gnu.org%2Flicenses%2Fgpl-3.0.en.html%23license-text)
![Static Badge](https://img.shields.io/badge/Status-v0.2.0_buggy-orange?style=flat)
![Static Badge](https://img.shields.io/badge/Codebase-available-green?style=flat)


Netcalc (`netcalc`) is a simple command line utility program to calculate IPv4 network characteristics.

# Compatibility
Compatible with any terminal that supports ANSI escape codes (shell, bash, pwsh, Zsh)
## Features
- calculate all network characteristics from any IP address
- identify network type, error when given APIPA address

## Dependencies 
- [CLI11](https://github.com/CLIUtils/CLI11) by [CLIUtils](https://github.com/CLIUtils) (CMakeLists is set up to fetch this dependency on build time)
- (since v0.2.0) [fmt](https://github.com/fmtlib/fmt) by [fmtlib](https://github.com/fmtlib) (CMakeLists is set up to fetch this dependency on build time)
- bitset (std)
- a C++ 17-compatible compiler (gcc/g++, clang, MSVC etc.)
- CMake 3.16.0 or later

# Commands

Main: `netcalc`

Example usage (all platforms): 
```powershell
netcalc 192.168.10.50 --sn /24 -A
```
Important: Do not forget to use the `--sn` flag between the IP address and the CIDR subnet mask! Otherwise it won't work!
## Flags

- `-A`: calculate all network characteristics
- `-b`: only calculate broadcast address
- `-r`: calculate network range (addressable hosts + broadcast and network)
- `-n`: calculate network address
- `-a`: calculate addressabe host range only
- `-i`: identify network type
- `-s`: calculate subnet mask
- `-h`: display help/list valid flags and usage

# Contributing
If you're considering contributing to netcalc, please see [CONTRIBUTING.md](https://github.com/TheSkyler-Dev/netcalc/blob/main/CONTRIBUTING.md) for instructions and standards for contributing to this project. Thank you for contributing!

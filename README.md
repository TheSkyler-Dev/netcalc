# Netcalc


![Static Badge](https://img.shields.io/badge/License-GNU_GPL--v3.0-blue?style=flat&link=https%3A%2F%2Fwww.gnu.org%2Flicenses%2Fgpl-3.0.en.html%23license-text)
![Static Badge](https://img.shields.io/badge/Status-in%20development-yellow?style=flat)
![Static Badge](https://img.shields.io/badge/Codebase-unavailable-red?style=flat)


Netcalc (`netcalc`) is a simple command line utility program to calculate IPv4 network characteristics.

# Compatibility
Compatible with any terminal (shell, bash, pwsh, Zsh)
## Features
- calculate all network characteristics from any IP address
- identify network type, error when given APIPA address

## Dependencies 
- [CLI11](https://github.com/CLIUtils/CLI11)
- bitset (std)
- a C++ 17-compatible compiler (gcc/g++, clang, MSVC etc.)
- CMake 3.16.0 or later

# Commands

Main: `netcalc`

## Flags

- `-A` or `--All`: calculate all network characteristics
- `-b` or `--broadcast`: only calculate broadcast address
- `-r` or `--range`: calculate network range (addressable hosts + broadcast and network)
- `-n` or  `--net`: calculate network address
- `-a` or  `--addressable`: calculate addressabe host range only
- `-c` or `--cidr`: calculate CIDR address
- `-i` or `--ident`: identify network type
- `-s` or `--snm`: calculate subnet mask
- `-h` or `--help`: display help/list valid flags and usage

Flags are only allowed behind the IP address except for:
- `--broacast`, `--net`, `--cidr`

Note: only long (--) flags are allowed both in front of the address or bhind it. Short (-) flags are only allowed behind the IP address.

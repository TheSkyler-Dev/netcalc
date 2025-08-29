# Netcalc


![Static Badge](https://img.shields.io/badge/License-GNU_GPL--v3.0-blue?style=flat&link=https%3A%2F%2Fwww.gnu.org%2Flicenses%2Fgpl-3.0.en.html%23license-text)
![Static Badge](https://img.shields.io/badge/Status-v0.2.0_working-green?style=flat)
![Static Badge](https://img.shields.io/badge/Next_version-in_development-orange?style=flat)


Netcalc (`netcalc`) - a safe, fast command line utility program to calculate IPv4/IPv6 network characteristics without touching any system or network configurations.

# Compatibility
Compatible with any terminal that supports ANSI escape codes (shell, bash, pwsh, Zsh)

For Windows native PowerShell, you may need to enable ANSI escape code support.
## Features
- calculate all network characteristics from any IP address
- identify network type, error when given APIPA address

## Dependencies 
- [CLI11](https://github.com/CLIUtils/CLI11) by [CLIUtils](https://github.com/CLIUtils) (CMakeLists is set up to fetch this dependency on build time)
- (for v0.2.0) [fmt](https://github.com/fmtlib/fmt) by [fmtlib](https://github.com/fmtlib) (CMakeLists is set up to fetch this dependency on build time)
- bitset (std)
- a C++ 17-compatible compiler (gcc/g++, clang, MSVC etc.)
- CMake 3.16.0 or later

### ⚠️ Note: Dependency changes due to changes in the source code
Starting with `netcalc` 0.3.0, more recent C++ features will be used, prompting a change to the `CMakeLIsts.txt` in the code base (Latest in main branch). These changes are:
- ~CMake 3.16.0 or later~ **CMake 3.25.0 or later**
- ~a C++ 17-compatible compiler~ **a C++ 20-compatible compiler (see [Compiler Support for C++ 20](https://en.cppreference.com/w/cpp/compiler_support/20) for compatible compilers)**
- ~[fmt](https://github.com/fmtlib/fmt) by [fmtlib](https://github.com/fmtlib)~ **This dependency has been removed with `netcalc` 0.3.0.**

#### What features prompted this change?
These changes are due to the use of the `std::format` (introduced in C++ 20) from version 0.3.0 forward. That allows for a more maintainable and less verbose source code, also allowing for string interpolation and less verbose text formatting.

# Installation
## Windows manual install
1. download `netcalc.exe`
2. create a `netcalc` directory in the root directory of your C drive and place `netcalc.exe` inside of it
3. copy the path to ther parent folder of the executable and paste it into your local `PATH` environment variable to install it for your account only. To install globally, add the directory to the global `PATH` variable.
4. Verify installation:
```powershell
netcalc -h
or
netcalc --help
```

### `.tar.gz` tarball (manual installation)
1. Download `netcalc-[version]-Linux.tar.gz`
2. extract the package with
```bash
tar -xvzf netcalc-[version]-Linux.tar.gz
```
4. navigate to the extracted package and find the binary
```bash
cd netcalc-[version]-Linux/bin
```
7. Finally move the binary to `usr/local/bin`
```bash
sudo cp netcalc /usr/local/bin
```
8. verify installation:
```bash
netcalc -h
or
netcalc --help
```
## Building from Source
1. Clone the repository
   ```bash
   git clone https://github.com/yourname/netcalc.git
   ```
2. move into the directory for your desired version of `netcalc`
   ```bash
   cd netcalc
   ```
3. make a build directory and move into it
   ```bash
   mkdir build && cd build
   ```
4. Build the project
   ```bash
   cmake ..
   make
   ```
### :warning: Note: Installers for `netcalc`
Installers are still a work in progress and do not work yet (help wanted - see Issue [#19](https://github.com/TheSkyler-Dev/netcalc/issues/19)). **It is advised to not download the installers provided in release v0.2.0!** In the meantime, binaries, .deb packages and tarballs are available.

# Example usage:
Example 1, Calculating all network characteristics
```bash
netcalc 192.168.10.50 --sn /24 -A
```
```bash
Calculating requested network characteristics for: 192.168.10.50
IP: 192.168.10.50/24
Address type: Private
Subnet Mask: 255.255.255.0
Network Address: 192.168.10.0
Network Range: 192.168.10.0 - 192.168.10.255
Addressable Host Range: 192.168.10.1 - 192.168.10.254
Number of Addressable Hosts: 254
Broadcast Address: 192.168.10.255
```
---
Example 2, Calculating the network range only
```bash
netcalc 10.0.0.0 --sn /8 -r
```
```bash
Calculating requested network characteristics for: 10.0.0.0
IP: 10.0.0.0/8
Network Range: 10.0.0.0 - 10.255.255.255
```
---
Example 3, Identifying network type
```bash
netcalc 172.16.5.100 --sn /20 -i
```
```bash
IP: 172.16.5.100/20
Address type: Private
```
# Contributing
If you're considering contributing to netcalc, please see [CONTRIBUTING.md](https://github.com/TheSkyler-Dev/netcalc/blob/main/CONTRIBUTING.md) for instructions and standards for contributing to this project. Thank you for contributing!

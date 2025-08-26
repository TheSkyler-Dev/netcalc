# Contributing to Netcalc

Thank you for considering contributing to Netcalc! We appreciate your time and effort in helping to improve this project.
Please follow these guidelines to ensure consistency and maintain high code quality.

## 🚀 Quick Start for Contributors

### High Priority Areas (Help Wanted!)
- **Installers & Packaging** 📦 - We need help with CPack, NSIS, WiX, and MSI installers
- **Package Manager Support** 📋 - Homebrew, Chocolatey, Scoop, AUR submissions
- **Cross-platform Testing** 🔄 - Testing builds on different OS/compiler combinations
- **Documentation** 📖 - Improve user guides and API documentation

## Getting Started

1. **Fork the Repository**: Start by forking the repository on GitHub.
2. **Clone Your Fork**: Clone your forked repository to your local machine.
   ```bash
   git clone https://github.com/your-username/netcalc.git
   ```
3. **Create a Branch:** Always work in a new branch to keep your changes organized.
   ```bash
   git checkout -b feature-or-bugfix-branch
   ```

## Development Setup

### Prerequisites
- CMake 3.16+ (3.25+ for v0.3.0)
- C++17 compiler (C++20 for v0.3.0)
- Git

### Building
```bash
cd netcalc/v0.2.0  # or v0.3.0
mkdir build && cd build
cmake ..
cmake --build .
```

### Testing Your Build
```bash
# Basic functionality test
./bin/netcalc 192.168.1.100 --sn /24 -A

# Expected output should show network calculations
```

## 📦 Installer & Packaging Help Needed

We're actively seeking help with:

### Windows Installers
- **NSIS**: Needs proper configuration and testing
- **WiX**: MSI installer creation and signing
- **Chocolatey**: Package creation and submission

### Linux Packages
- **Debian (.deb)**: Currently working, needs testing
- **RPM**: Red Hat/Fedora package creation
- **AUR**: Arch User Repository submission
- **Snap/Flatpak**: Universal package creation

### macOS
- **Homebrew**: Formula creation and submission
- **DMG**: Installer creation for direct distribution

### Package Manager Templates Needed
See `packaging/` directory for examples and templates.

## Code Standards

### Class Naming Conventions
- Use **PascalCase** for class names (e.g., `NetworkCalculator`, `IPAddress`)
- Class names should be descriptive and reflect their purpose

### Code Comments
- Provide clear, concise comments explaining complex code sections
- Document all public methods, classes, and modules
- Use `//` for single line comments or `/*...*/` for multi-line comments

### Variable Initialization
**Always initialize variables with default values** to prevent undefined behavior:
```cpp
int count = 0;           // Not: int count;
std::string name = "";   // Not: std::string name;
double value = 0.0;      // Not: double value;
```

## Pull Request Process

1. **Open a Pull Request (PR)**: Submit against the appropriate version branch
2. **Describe Your Changes**: Include clear description of enhancements/fixes
3. **Link Issues**: Reference related issues (e.g., "Closes #123", "Helps with #19")
4. **Review Process**: All PRs undergo maintainer review
5. **Testing**: Ensure all tests pass and add new tests for new features

## Style Guidelines
- **Indentation**: 4 spaces
- **Line Length**: 80 characters where possible
- **Naming**: Descriptive and consistent names
- **No Warnings**: Ensure clean compilation

## 🏷️ Issue Labels Guide

When creating issues or PRs, use these labels:
- `help wanted` - Community help needed
- `good first issue` - Great for new contributors  
- `installer` - Related to packaging/installation
- `documentation` - Documentation improvements
- `enhancement` - New features
- `bug` - Bug fixes

## Recognition

Contributors will be:
- Listed in AUTHORS.md
- Mentioned in release notes
- Given credit in documentation

## Getting Help

- Comment on existing issues
- Join our discussions tab
- Tag maintainers (@TheSkyler-Dev) for questions

---

**Priority Areas for Contributors:**
1. 📦 Windows installer fixes (Issue #19)
2. 🍺 Homebrew formula creation
3. 📋 Package manager submissions
4. 🔄 CI/CD improvements
5. 📖 Documentation enhancements

Thank you for contributing to Netcalc! Your help makes this project better for everyone.

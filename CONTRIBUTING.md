# Contributing to Multiconvert

Thank you for considering contributing to Multiconvert! We appreciate your time and effort in helping to improve this project.  
Please follow these guidelines to ensure consistency and maintain high code quality.

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
## Code Standards
To maintain code consistency and readability, please adhere to the following guidelines:

1. ### Class Naming Conventions
   - Use **PascalCase** for class names (e.g., `UnitConverter`, `TemperatureConverter`).
   - Class names should be descriptive and reflect their purpose.

2. ### Code Comments
   - Provide clear, concise comments explaining complex code sections.
   - Document all public methods, classes, and modules, including a brief description of each parameter and return value.
   - Use `//` for single line comments or `/*...*/` for multi-line comments where necessary.

3. ### Linking Issues
   - If your contribution resolves an existing issue, **link the issue in your pull request** description.
   This helps maintain a clear connection between issues and code changes.

4. ### Use of Variables
   In order to prevent potential undefined behavior, it is good practice to **allways initialize variables with default values**. Default values are expected to convey the kind of value expected by the variable, e.g. `0.0` for floating point or doube floating point varables, `"defaultValue"` for string variables or `0` for integer variables. Uninitialized Variable can cause unpredictable results, undefined behavior and bugs that are hard to diagnose. Make sure all variables have defined values before bein used in expressions or passed to functions.

## Pull Request Process
To ensure the quality of the codebase, all contributions go through a review process. Follow these steps to create a pull request:

1. **Open a Pull Request (PR)**: When you are ready to submit your changes, open a PR against the `main` branch.
2. **Describe Your Changes**: Include a clear, concise description of the changes in your PR, specifying any enhancements or bug fixes.
3. **Link to Relevant Issue**: If your PR addresses an existing issue, reference it in the PR description (e.g., "Closes #123").
4. **review Process**
   - All PRs will undergo a comprehensive review by project maintainers.
   - You may be asked to provide further clarification or modifications if needed.
   - PRs will only be merged once they pass the review and are approved by at least one maintainer.
5. **Testing**:
   - Ensure that all tests pass successfully before submitting a PR.
   - Add new tests if your contribution introduces new features or modifies existing functionality.

## Style Guidelines
- **Indentation**: Use 4 spaces for indentation.
- **Line Length**: Limit lines to 80 characters where possible to improve readability.
- **Naming**: Use descriptive and consistent names for variables and functions.
- **No Warnings**: Ensure there are no compiler or linter warnings.

Please be aware that some warnings may not be displayed consistently across all devices or environments. For example, certain compilers, IDEs, or terminal environments may not show  the same set of warnings, or they may suppress some warnings by default. Please make sure that code is properly reviewed and tested in a variety of environments to catch potential issues.

## Additional Information
Feel free to reach out to the maintainers if you have questions or need guidance.  
Thank you for helping make Multiconvert better!
- - -
Thank you for contributing to Multiconvert! Your contributions are valuable and help improve the project for everyone.
- - -
This file provides detailed instructions for contributors and emphasizes the standards and review process required for maintaining high code quality.  
Let me know if you’d like any adjustments or additional sections!

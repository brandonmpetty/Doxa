# CodeQL Configuration for Doxa

This directory contains the CodeQL configuration files for the Doxa project. CodeQL is a semantic code analysis engine that helps identify security vulnerabilities and code quality issues in your codebase.

## Configuration Files

- `cpp.yml`: Configuration for C++ analysis
- `cpp-queries.yml`: Custom queries for C++ analysis

## How It Works

The CodeQL analysis is triggered by GitHub Actions when:
- Code is pushed to the main branch
- A pull request is created against the main branch
- On a weekly schedule (Sunday at midnight)

## C++ Analysis

The C++ analysis specifically:

1. Builds the Doxa.Test project using CMake
2. Analyzes the code for security vulnerabilities and code quality issues
3. Reports findings to GitHub Security

## Custom Queries

The custom queries focus on:

- Memory safety issues (use-after-free, double-free, buffer overflows)
- Performance issues (unnecessary copies, inefficient string concatenation)
- Code quality issues (uninitialized variables, dead code)
- Algorithm correctness issues (division by zero, integer overflow)

## Viewing Results

You can view the results of the CodeQL analysis in the GitHub Security tab of your repository.

## Troubleshooting

If the CodeQL analysis fails to build the C++ project:

1. Check the GitHub Actions logs for errors
2. Verify that the CMake configuration is correct
3. Ensure all dependencies are properly installed
4. Check that the paths in the workflow file are correct 
# Contributing to Launcher Auto-Update

## Guidelines

### Code Style
- Use 4-space indentation
- Camel case for functions: `CheckForUpdates()`
- UPPER_SNAKE for constants: `MAX_RETRIES`
- Comments for logic over 5 lines

### Testing Before PR
```bash
cmake --build . --config Release
ctest  # Run all tests
```

### Commit Messages
- ✅ Good: `Fix hash verification for large files`
- ❌ Bad: `stuff` or `lol update`

### Branches
- `main` - Stable, released code only
- `develop` - Integration branch
- `feature/*` - New features
- `bugfix/*` - Bug fixes

## Release Process

1. Update version in `CMakeLists.txt`
2. Update `CHANGELOG.md`
3. Merge to `main`
4. Tag: `git tag -a v1.0.0 -m "Release 1.0.0"`
5. Create GitHub Release with binaries

## Pull Request Checklist

- [ ] Code compiles with no warnings
- [ ] All tests pass
- [ ] Commit message is descriptive
- [ ] No merge conflicts with `main`
- [ ] Updated relevant documentation

---

Thank you for contributing! 🎉

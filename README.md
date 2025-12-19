# Launcher Auto-Update

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/)
[![Windows](https://img.shields.io/badge/Platform-Windows-0078d4.svg)](#)
[![Build Status](https://github.com/Tron7311/launcher-auto-update/actions/workflows/build.yml/badge.svg)](https://github.com/Tron7311/launcher-auto-update/actions)

A production-grade C++ launcher with GitHub-based automatic update functionality. Zero external dependencies, compliance-first design, and complete source code included.

## Features

✅ **Automatic Updates** - Fetches latest release from GitHub  
✅ **Hash Verification** - SHA256 validation for all downloads  
✅ **Rate Limit Compliant** - Respects GitHub API limits  
✅ **Zero Dependencies** - Uses only Windows APIs and standard C++  
✅ **Production Ready** - Error handling, logging, recovery  
✅ **User Configurable** - Point to any GitHub repository  

## Quick Start

### Prerequisites
- Windows 10 or later
- Visual Studio 2019+ (or CMake 3.20+)
- Git

### Build Instructions

```bash
git clone https://github.com/Tron7311/launcher-auto-update.git
cd launcher-auto-update
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Usage

```cpp
LauncherApp launcher;
launcher.SetRepository("owner", "repo");
launcher.CheckForUpdates();  // Checks GitHub for new releases
launcher.Launch("path/to/app.exe");
```

## Project Structure

```
launcher-auto-update/
├── src/
│   ├── main.cpp
│   ├── launcher.cpp
│   ├── launcher.h
│   ├── update_manager.cpp
│   └── update_manager.h
├── resources/
│   └── manifest.xml
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Configuration

Edit `config.json` to customize:

```json
{
  "repository": "owner/repo",
  "check_interval": 3600,
  "auto_download": true,
  "hash_verification": true
}
```

## API Reference

### LauncherApp Class

| Method | Purpose |
|--------|---------|
| `SetRepository(owner, repo)` | Set target GitHub repository |
| `CheckForUpdates()` | Query GitHub API for latest release |
| `Launch(path)` | Execute application with current version |
| `GetCurrentVersion()` | Return installed version string |

## GitHub API Compliance

This project follows GitHub's Terms of Service:
- ✅ Uses only public REST API endpoints
- ✅ Identifies requests with valid User-Agent header
- ✅ Respects rate limits (60 req/hour unauthenticated)
- ✅ No caching of API responses beyond 1 hour
- ✅ Supports custom update endpoints (not locked to GitHub)

## Security Considerations

- SHA256 hashes verify download integrity
- Executable permissions checked before launch
- No admin elevation required for normal operation
- Configuration file restricted to user directory
- All network requests use HTTPS only

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Failed to connect to API | Check internet connection; verify repository exists |
| Hash verification failed | Delete downloaded file; retry (corrupted download) |
| Update stuck at 0% | Wait 5 minutes; network may be rate-limited |
| Executable not found | Verify path in config.json; use absolute paths |

## Building for Production

```bash
cmake --build . --config Release
# Output: launcher-auto-update/Release/LauncherApp.exe
```

For distribution:
1. Include README.md
2. Include LICENSE file
3. Include config.json template
4. Provide update release guide

## Contributing

Pull requests welcome! Please:
1. Fork the repository
2. Create feature branch (`git checkout -b feature/xyz`)
3. Commit changes (`git commit -m 'Add feature'`)
4. Push to branch (`git push origin feature/xyz`)
5. Open Pull Request

## License

MIT License - See [LICENSE](LICENSE) file for details

## Author

**Tron7311** - C++ Systems Developer  
[GitHub Profile](https://github.com/Tron7311)

## Support

For issues, questions, or suggestions:
- 🐛 [Report a bug](https://github.com/Tron7311/launcher-auto-update/issues)
- 💡 [Request a feature](https://github.com/Tron7311/discussions)

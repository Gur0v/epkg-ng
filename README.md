# epkg-ng

**A high-performance C rewrite of the popular epkg package management wrapper for Gentoo Linux**

epkg-ng provides an intuitive, apt-like interface to Gentoo's package management ecosystem, designed for both newcomers transitioning from other distributions and experienced users seeking improved performance.

## Why epkg-ng?

### Complete C Rewrite
This project represents a ground-up rewrite of the original bash-based epkg in C, delivering:

- **Superior performance** - Native C execution vs. shell script interpretation overhead
- **Minimal resource usage** - Lightweight binary with reduced memory footprint
- **Enhanced reliability** - Robust error handling, input validation, and buffer overflow protection
- **Improved maintainability** - Clean, structured C codebase with comprehensive build system

### Key Improvements Over Original epkg

| Feature | Original epkg (Bash) | epkg-ng (C) |
|---------|---------------------|-------------|
| **Performance** | Shell script interpretation | Compiled native binary |
| **Memory Usage** | ~2-5MB shell processes | ~50-100KB single process |
| **Error Handling** | Basic shell exit codes | Comprehensive error checking |
| **Security** | Shell injection vulnerabilities | Input sanitization & validation |
| **Build System** | Simple script file | Professional Makefile with optimization |
| **Completions** | None | Advanced bash completion support |
| **Commands** | 15 basic commands | 18+ commands with enhanced functionality |

### New Features Not in Original

- **Enhanced command set** - Additional commands like `show`, `depends`, `uses`
- **Bash completion** - Intelligent tab completion for commands and package names
- **Optimized builds** - Support for debug, release, and native-optimized compilation
- **Better argument handling** - Robust parsing with length limits and validation
- **Professional packaging** - Complete installation system with proper paths

## Installation

### From Source

```bash
git clone https://github.com/Gur0v/epkg-ng.git
cd epkg-ng
make
sudo make install
```

### Build Options

```bash
# Standard optimized build
make

# Debug build with symbols
make debug

# Release build with LTO optimizations
make release

# Clean build
make clean && make
```

### Dependencies

**Required:**
- **portage** - Gentoo's package manager
- **gentoolkit** - Collection of Gentoo administration tools (`equery`)
- **eix** - Fast package search utility
- **gcc** - GNU Compiler Collection

**Optional:**
- **portage-utils** - For enhanced bash completion (`qlist`)

## Command Reference

### Package Management
| Command | Description | Backend Command | Args Required |
|---------|-------------|-----------------|---------------|
| `install` | Install new packages | `emerge -av` | Yes |
| `remove` | Remove packages safely | `emerge --depclean -av` | Yes |
| `forceremove` | Force remove packages (unsafe) | `emerge --unmerge -av` | Yes |
| `update` | Update package repository | `eix-sync -a` | No |
| `upgrade` | Upgrade all installed packages | `emerge -uDNva @world` | No |
| `autoremove` | Remove orphaned packages | `emerge --depclean -a` | No |

### Package Information
| Command | Description | Backend Command | Args Required |
|---------|-------------|-----------------|---------------|
| `search` | Search for packages | `eix` | Yes |
| `show` | Show detailed package information | `eix -v` | Yes |
| `listfiles` | List files installed by package | `equery files` | Yes |
| `listinstalled` | List all installed packages | `equery list '*'` | No |
| `provides` | Find package owning a file | `equery belongs` | Yes |
| `depends` | Show package dependencies | `equery depends` | Yes |
| `uses` | Show package USE flags | `equery uses` | Yes |

### System Maintenance
| Command | Description | Backend Command | Args Required |
|---------|-------------|-----------------|---------------|
| `verify` | Verify package integrity | `equery check -o` | Yes |
| `verifyall` | Verify all packages | `equery check -o '*'` | No |
| `autoclean` | Clean old source files | `eclean-dist -df` | No |
| `clean` | Clean all source files | `eclean-dist -daf` | No |
| `sysinfo` | Show system information | `emerge --info` | No |

### Easter Eggs
| Command | Description | Backend Command | Args Required |
|---------|-------------|-----------------|---------------|
| `moo` | Display emerge's cow | `emerge --moo` | No |

## Examples

```bash
# Install development tools
epkg install git vim gcc

# Search for web browsers (with tab completion)
epkg search firefox
epkg search <TAB><TAB>  # Shows available packages

# Show detailed information about a package
epkg show firefox

# List files installed by a package
epkg listfiles firefox

# Find which package owns a file
epkg provides /usr/bin/firefox

# Update repository and upgrade system
epkg update
epkg upgrade

# Clean up system after removing packages
epkg autoremove
epkg autoclean
```

## Bash Completion

epkg-ng includes intelligent bash completion that provides:

- **Command completion** - Tab completion for all epkg commands
- **Package name completion** - Context-aware package suggestions
- **File completion** - File path completion for `provides` command
- **Smart filtering** - Different package lists for install vs. remove operations

The completion system automatically detects available tools (eix, qlist, equery) and uses the fastest available method for package enumeration.

## Technical Details

### Architecture
- **Language**: C99 compliant
- **Build system**: GNU Make with dependency tracking
- **Memory management**: Static buffers with overflow protection
- **Error handling**: Comprehensive validation and reporting

### Security Features
- Input validation and sanitization
- Buffer overflow protection
- Command injection prevention
- Safe command execution via system()

### Performance Optimizations
- Native compilation with `-march=native -mtune=native`
- Link-time optimization (LTO) in release builds
- Minimal runtime dependencies
- Efficient string operations and memory usage

## Compatibility

epkg-ng is designed exclusively for:
- **Gentoo Linux** - Full feature support
- **Funtoo Linux** - Full feature support

Other distributions are not supported due to dependency on Portage ecosystem.

## Differences from Original epkg

### Removed Features
- `machinegod` easter egg command
- Interactive `clean` command with confirmation prompt
- Some redundant command aliases (`uninstall`, `dist-upgrade`)

### Enhanced Features
- Standardized `clean` command using `eclean-dist -daf`
- Added `show`, `depends`, `uses` commands
- Improved `upgrade` command with better flags
- Better error messages and validation
- Professional build and installation system

### Technical Improvements
- Complete rewrite from bash to C
- Proper argument parsing and validation
- Memory-safe operations
- Cross-platform build system
- Comprehensive error handling

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Follow C99 standards and existing code style
4. Add appropriate error handling
5. Test thoroughly on Gentoo/Funtoo
6. Submit a pull request

### Development

```bash
# Build debug version
make debug

# Run basic tests
make check

# Clean and rebuild
make rebuild
```

## Authors

- **Gurov** <gurov@atl.tools> - C rewrite and improvements
- **Jeff Horelick** <jdhore@gentoo.org> - Original epkg concept
- **Douglas Freed** <dwfreed@mtu.edu> - Original epkg contributor
- **Miramir** <gmiramir@gmail.com> - Original epkg contributor

## License

Licensed under the 2-Clause BSD License. See [LICENSE](LICENSE) for details.

---

*epkg-ng: Because package management should be fast, reliable, and familiar.*

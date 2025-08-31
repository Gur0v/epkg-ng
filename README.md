# epkg-ng

A fast, lightweight wrapper for Gentoo's package management tools, providing an intuitive interface familiar to users from other distributions.

## Features

- **Familiar syntax** - Commands inspired by apt-get, yum, and dpkg
- **High performance** - Written in C for speed and low memory usage
- **Comprehensive** - Wraps emerge, equery, eix, and eclean functionality
- **Safe operations** - Sensible defaults with confirmation prompts
- **Easy transition** - Perfect for users migrating from Debian/Ubuntu/RHEL

## Quick Start

```bash
# Search for packages
epkg search firefox

# Install packages  
epkg install firefox thunderbird

# Update repository
epkg update

# Upgrade system
epkg upgrade

# Remove packages
epkg remove old-package

# Clean up
epkg autoremove
```

## Installation

### From Source

```bash
git clone https://github.com/Gur0v/epkg-ng.git
cd epkg-ng
make
sudo make install
```

### Dependencies

- **portage** - Gentoo's package manager
- **gentoolkit** - Collection of Gentoo administration tools
- **eix** - Fast package search utility
- **gcc** - GNU Compiler Collection

## Commands

| Command       | Description                    | Equivalent Gentoo Command                     |
|---------------|--------------------------------|-----------------------------------------------|
| install       | Install packages               | `emerge -av`                                  |
| remove        | Remove packages safely         | `emerge --depclean -av`                       |
| update        | Update package repository      | `eix-sync`                                    |
| upgrade       | Upgrade all packages           | `emerge -uDNva --with-bdeps=y @world`         |
| search        | Search for packages            | `eix`                                         |
| show          | Show package details           | `eix -v`                                      |
| autoremove    | Remove orphaned packages       | `emerge --depclean -a`                        |
| autoclean     | Clean old source files         | `eclean-dist -df`                             |
| clean         | Clean all source files         | `eclean-dist -daf`                            |
| listfiles     | List files in package          | `equery files`                                |
| listinstalled | List installed packages        | `equery list '*'`                             |
| provides      | Find package owning file       | `equery belongs`                              |
| depends       | Show dependencies              | `equery depends`                              |
| uses          | Show USE flags                 | `equery uses`                                 |
| verify        | Verify package integrity       | `equery check -o`                             |
| sysinfo       | Show system information        | `emerge --info`                               |

## Examples

```bash
# Install development tools
epkg install git vim gcc

# Search for web browsers
epkg search browser

# Show detailed information about a package
epkg show firefox

# List files installed by a package
epkg listfiles firefox

# Find which package owns a file
epkg provides /usr/bin/firefox

# Clean up system after removing packages
epkg autoremove && epkg autoclean
```

## Building

### Standard Build
```bash
make
```

### Debug Build
```bash
make debug
```

### Release Build
```bash
make release
```

## Compatibility

epkg-ng is designed exclusively for:
- **Gentoo Linux**
- **Funtoo Linux**

Other distributions are not supported.

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## Authors

- **Gurov** <gurov@atl.tools> - C rewrite and improvements
- **Jeff Horelick** <jdhore@gentoo.org> - Original epkg
- **Douglas Freed** <dwfreed@mtu.edu> - Contributor
- **Miramir** <gmiramir@gmail.com> - Contributor

## License

Licensed under the 2-Clause BSD License. See [LICENSE](LICENSE) for details.

## About This Fork

This is a complete rewrite of Jeff Horelick's original epkg in C, offering:

- **Better performance** - Faster execution and lower memory usage
- **Enhanced reliability** - Improved error handling and validation
- **Extended functionality** - Additional commands and safer operations
- **Modern codebase** - Clean, maintainable C code

The goal is to provide the most efficient and user-friendly package management wrapper for Gentoo systems.

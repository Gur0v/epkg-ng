# epkg-ng

A simple package manager wrapper for Gentoo Linux that provides familiar commands for common package operations.

## Installation

```bash
git clone https://github.com/Gur0v/epkg-ng.git
cd epkg-ng
make
sudo make install
```

## Requirements

- Gentoo or Funtoo Linux
- `portage`
- `gentoolkit` 
- `eix`
- `gcc` and `make` (for building)

## Commands

### Package Management
```bash
epkg install <package>        # Install packages
epkg remove <package>         # Remove packages
epkg update                   # Update repositories
epkg upgrade                  # Upgrade system
epkg autoremove               # Remove orphaned packages
```

### Package Information
```bash
epkg search <term>           # Search for packages
epkg show <package>          # Show package details
epkg listinstalled           # List installed packages
epkg listfiles <package>     # List files in package
epkg provides <file>         # Find package owning file
epkg depends <package>       # Show dependencies
epkg uses <package>          # Show USE flags
```

### System Maintenance
```bash
epkg verify <package>        # Check package integrity
epkg verifyall               # Check all packages
epkg clean                   # Clean download cache
epkg autoclean               # Clean old downloads
epkg sysinfo                 # Show system info
epkg configure <package>     # Configure package
```

## Examples

```bash
# Install Firefox
epkg install firefox

# Search for text editors
epkg search editor

# Update system
epkg update
epkg upgrade

# Find what package owns a file
epkg provides /usr/bin/vim

# Clean up system
epkg autoremove
epkg clean
```

## Build Options

```bash
make            # Standard build
make debug      # Debug build
make release    # Optimized build
make clean      # Clean build files
```

## License

[BSD 2-Clause License](LICENSE)

## Authors

- Gurov <gurov@atl.tools> - C rewrite
- Jeff Horelick - Original epkg
- Douglas Freed - Original contributor
- Miramir - Original contributor

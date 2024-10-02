# Epkgc (Epkg Fork)

This is a fork of Jeff Horelick's "epkg", rewritten in C. It serves as a wrapper for Gentoo commands (emerge, equery, eix) to make them feel more natural to users familiar with other distributions.

The syntax is aimed to be an amalgamation of the sane command names from apt-get, dpkg and yum. Actually closer to ipkg/opkg than anything else.

## Installation

To install Epkgc, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/TuxForge/epkgc.git
   ```

2. Change to the epkgc directory:
   ```
   cd epkgc
   ```

3. Install using make:
   ```
   sudo make clean install
   ```


## Authors

* Gurov <gurov@atl.tools> (C implementation)
* Jeff Horelick <jdhore@gentoo.org> (Original epkg)
* Douglas Freed <dwfreed@mtu.edu>
* Miramir <gmiramir@gmail.com>

## Dependencies

If you would like to install epkg manually, the dependencies are as follows:

* Portage
* gentoolkit
* eix
* C compiler (e.g., GCC)

epkg is compatible only with Gentoo and Funtoo. Compatibility with other distributions will not be added.

## Licensing

This code is licensed under the 2-clause BSD License. Please see the LICENSE file for details.

## About This Fork

This version of epkg is a fork of the original project by Jeff Horelick. The main difference is that it has been completely rewritten in C, which may offer performance improvements and lower resource usage compared to the original implementation.

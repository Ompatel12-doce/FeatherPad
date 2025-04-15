# OUR WORK

This folder contains custom contributions, modifications, and enhancements made to the FeatherPad text editor in this fork. FeatherPad is a lightweight, Qt-based plain-text editor for Linux, and the work here reflects our efforts to extend or improve its functionality.

## Contents

Below is a list of files and their purposes in this folder:

- **vscrollbar.cpp**: Implements a custom vertical scrollbar with enhanced wheel event handling for smoother scrolling. Overrides Qt's `QScrollBar` to address hover bugs and provide precise scroll steps.
- **encoding.h**: Declares the `detectCharset` function for automatic character encoding detection, enabling proper text decoding for opened files.


## Purpose

The `OUR WORK` folder serves as a dedicated space for our fork’s contributions, including:

- New features or improvements to FeatherPad’s core functionality.
- Bug fixes or optimizations to existing components.
- Documentation or scripts specific to our changes.

## Contributing

To contribute to this folder:

1. **Fork and Clone**: Clone this repository and navigate to the `OUR WORK` folder.
2. **Add/Modify Files**: Place new or modified files here, ensuring they follow FeatherPad’s coding style (see the main README).
3. **Document Changes**: Update this README with a brief description of your file(s).
4. **Test Thoroughly**: Ensure your changes compile and work with FeatherPad (see INSTALL for build instructions).
5. **Submit a Pull Request**: Create a PR against this fork, detailing your changes and their purpose.

For coding guidelines, refer to FeatherPad’s original style in tsujan/FeatherPad. Use modern C++ and Qt best practices.

## License

All contributions in this folder are licensed under the GNU General Public License v3.0 or later, consistent with FeatherPad’s licensing. See the LICENSE file for details.

## Contact

For questions or collaboration, open an issue on this repository or contact the maintainers via GitHub.

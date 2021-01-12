# WIO-Terminal-Digital-Clock

A Full function Digital Clock for the WIO-Terminal

This project is compatible with the Arduino project structure and the Platform IO project structure.

While Platform IO is better and quicker as a development IDE, Arduino is the standard. Whatever you build make sure it builds in an Arduino and Platform IO IDE. For Arduino just open the .ino file in the 'src' directory (of the same name).

See the 'platformio.ini' property 'src_dir' below.

## PlatformIO Warning

### Build check

If you have problems getting the build working please make sure you can build and upload using the Arduino IDE and you have followed all of the instructions for adding libraried to the Arduino project.

For PlatformIO development you MAY need to set the **lib_extra_dirs** value in the platformio.ini file:

From:

```bash
lib_extra_dirs = ~/Arduino/libraries
```

To an absolute path. For example:

```bash
lib_extra_dirs = home/myUserId/Arduino/libraries
```

This was the only way I could get it to compile.

### platformio.ini basic

```bash
[platformio]
src_dir = Digital-Clock

[env:WIO-Terminal-Clock]
platform = atmelsam
board = seeed_wio_terminal
framework = arduino
lib_extra_dirs = ~/Arduino/libraries

platform_packages = framework-arduino-samd-seeed@https://github.com/Seeed-Studio/ArduinoCore-samd.git
lib_ldf_mode = deep
```
### C++ Code Formatting
Go to Settings and search for 'C_Cpp' and look for:
```json
C_Cpp:Clang_format_fallback style
```
Replace 'Visual Studio' with 
```json
{BasedOnStyle: Google, UseTab: Never, IndentWidth: 4, TabWidth: 4, AllowShortIfStatementsOnASingleLine: false, IndentCaseLabels: false, ColumnLimit: 0, AccessModifierOffset: -4 }
```
# The Project


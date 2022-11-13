# User manual

This manual describes how to install the application and how to use it.

[TOC]

## Installation
The application is portable, so you don't need to install the software.
Just download the application, run it, and you're good to go!

## Using the software
This section explains how to set the application up, and how to use it.

### Settings
Before you start the application, make sure your control surface is connected and powered on.
Also make sure your MOTU AVB interface is connected and powered on.

When you start up the application, you'll see the main window.

<img alt="Main window" src="main-window.png" width="505">

Select your control surface from the "MIDI input" and "MIDI output" menus.

If you've connected your MOTU AVB interface via Ethernet, you can use its IP address to figure out the URL.
If, for example, your interface's IP address is 10.0.0.5, the URL will be `http://10.0.0.5`.

If you've connected your MOTU AVB interface via USB or Thunderbolt, you can figure out your URL by going to the MOTU Pro Audio Control for that interface.

<img alt="MOTU menu in the menu bar" src="motu-menu.png" width="237">

In the browser, copy the URL without the page identifier.

<img alt="Getting the URL from the address bar" src="motu-url-address-bar.png" width="474">

Paste the URL into the URL field in the application, click the "Connect" button, and you're set!
Don't worry about remembering the URL, the application will remember it for you.

### Channel view
When you connect your control surface to the MOTU AVB interface, your control surface will show you the channel view.
This is currently the only view.

In this view you can do the following things:

- You can see the channel names on the display above every channel.
- You can use the fader bank buttons to view the next or previous set of 8 channels.
- You can solo and unsolo channels.
- You can mute and unmute channels.
<!--- - You can use the faders to control the level. -->
<!--- - You can use the rotary encoders to control the panning. -->

## Compiling from source
If you'd like to compile the software from source, this section explains how to do that.

[TOC]

### Required build tools
Make sure that you have the following software installed:

- [Git](https://git-scm.com/downloads) (probably already installed on macOS)
- [CMake](https://cmake.org/download/) (3.21 or later)
- [Doxygen](https://www.doxygen.nl/download.html) (optional, if you'd like to build this documentation)
- On macOS:
    - [Xcode commandline tools](https://developer.apple.com/download/all/)
- On Windows:
    - [Visual Studio](https://visualstudio.microsoft.com/downloads/). The "C++ desktop development" tools should be installed. You don't need the IDE, just make sure MSBuild is installed.

### Building the software
Open a terminal and clone the repository recursively.
```shell
git clone --recursive https://github.com/ixnas/Mackie-of-the-Unicorn.git
```

#### Configure using CMake
Create a new build folder and run CMake inside of it.
```shell
mkdir build
cd build
cmake <configuration options> ..
```
If you'd like to customize the build, replace `<configuration options>` with a combination of the following options:
| Option                               | Description                                                                                                              |
|--------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| `-DCMAKE_BUILD_TYPE=Release`         | Makes an optimized release build. Recommended if you're going to use the build in production.                            |
| `-DBUILD_UNIVERSAL=OFF` (macOS only) | Disables universal binaries. Use this if you're not going to run the build on different CPU architectures than your own. |
| `-DBUILD_DOC=OFF`                    | Disables building this documentation.                                                                                    |
| `-DBUILD_TESTS=OFF`                  | Disables building the unit tests.                                                                                        |

#### Build (macOS)
Use `make` to build the software and its dependencies.
Replace `<CPU count>` with the number of processor cores you have in your system.
```shell
make -j<CPU count>
```

There should now be an application bundle ready to use.

#### Build (Windows)
Use `MSBuild` to build the software and its dependencies.
The path to `MSBuild` may differ on your system.
Replace `<configuration>` with either `Release` or `Debug`, depending on whether you've configured the CMake project as a release build or not.
```shell
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" Mackie_of_the_Unicorn.sln /property:Configuration=<configuration> -maxcpucount
```

There should be an executable in either the Debug or Release folder ready to use.

#### Running unit tests
If you've configured the project to build the test suite, you can run the tests by running the `Unit_Tests` binary (or `Unit_Tests.exe` on Windows) in a command line.
Framework for mods to define variants of armors by swapping armor addons
dynamically at runtime.

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [SKSE64 SDK](https://skse.silverlock.org/)
	* Add the environment variable `SKSE64Path`
* [MCM Helper SDK](https://github.com/Exit-9B/MCM-Helper/releases)
	* Add the environment variable `MCMPath`
* [UIExtensions SDK](https://www.nexusmods.com/skyrimspecialedition/mods/17561)
	* Extract the BSA using your favorite tool (e.g.
	[Bethesda Archive Extractor](https://www.nexusmods.com/skyrimspecialedition/mods/974))
	* Add the environment variable `UIExtensionsPath`

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/Exit-9B/DynamicArmorVariants
cd DynamicArmorVariants
git submodule init
git submodule update
cmake --preset vs2022-windows
cmake --build build --config Release
```

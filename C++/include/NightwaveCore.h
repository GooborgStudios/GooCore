//
// Nightwave Core - NightwaveCore.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#ifdef _WIN32 // Windows
	#define WINDOWS 1
	#include <windows.h>
	#define APP_ICON "icons/icon.ico"
	#ifdef _WIN64 // Windows 64-bit
		#define WINDOWS_64
	#else // Windows 32-bit
		#define WINDOWS_32
	#endif
#elif __APPLE__ // macOS
	#define MACOS 1
	#define APP_ICON "icons/icon.icns"
#elif __linux__ // Linux
	#define LINUX 1
	#define APP_ICON "icons/icon_64.png"
#else // Unix, POSIX, iOS, Android...
	#warning "Unknown/unsupported compiler/operating system"
	#define APP_ICON "icons/icon_64.png"
#endif

#ifdef WINDOWS
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT 
	#define max std::max
	#define min std::min
#endif

EXPORT void setResourceBase(const char *resource_base);
EXPORT std::string getResourcePath(const char *resource_name);

EXPORT std::string to_padded_string(int value, int width);
EXPORT std::string to_padded_string(double value, int width, int precision);

// XXX Get rid of me!
EXPORT double threeway_max(double val_a, double val_b, double val_c);
EXPORT int threeway_max(int val_a, int val_b, int val_c);
EXPORT double threeway_min(double val_a, double val_b, double val_c);
EXPORT int threeway_min(int val_a, int val_b, int val_c);
EXPORT double clamp(double val, double minimum, double maximum);
EXPORT int clamp(int val, int minimum, int maximum);

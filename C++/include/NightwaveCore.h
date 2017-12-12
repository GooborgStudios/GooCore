//
// Nightwave Core - NightwaveCore.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

/**
 * @file   NightwaveCore.h
 * @brief  This file holds the basic definitions, as well as several helper functions.
 */

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
	#define NWC_max max
	#define NWC_min min
#else
	#define EXPORT 
	#define NWC_max std::max
	#define NWC_min std::min
#endif

/**
 * @brief      Sets the base resource path.
 * 
 * This function is designed for cross-platform compatibility.
 *
 * @param[in]  resource_base  The base resource path
 */
EXPORT void setResourceBase(const char *resource_base);

/**
 * @brief      Gets the path of a specified resource.
 *
 * @param[in]  resource_name  The specific resource
 *
 * @return     The full resource path.
 */
EXPORT std::string getResourcePath(const char *resource_name);

/// \overload std::string getResourcePath(const char *resource_name)
EXPORT std::string getResourcePath(std::string resource_name);

/**
 * @brief      This function takes an integer and returns a string padded with 0's.
 *
 * @param[in]  value  The integer to convert to a string
 * @param[in]  width  The width of the string
 *
 * @return     A string of the integer at the given width.
 */
EXPORT std::string to_padded_string(int value, int width);

/**
 * @brief      This function takes a double and returns a string padded with 0's.
 *
 * @param[in]  value      The double to convert to a string
 * @param[in]  width      The width of the string, excluding decimal points
 * @param[in]  precision  The precision of the decimal points
 *
 * @return     A string of the double at the given width and precision.
 */
EXPORT std::string to_padded_string(double value, int width, int precision);

/// \todo Get rid of me!
EXPORT double threeway_max(double val_a, double val_b, double val_c);
EXPORT int threeway_max(int val_a, int val_b, int val_c);
EXPORT double threeway_min(double val_a, double val_b, double val_c);
EXPORT int threeway_min(int val_a, int val_b, int val_c);
EXPORT double clamp(double val, double minimum, double maximum);
EXPORT int clamp(int val, int minimum, int maximum);

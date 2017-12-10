//
// Nightwave Core - Colors.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

/**
 * @file   Colors.h
 * @brief  This file holds the Color object class, as well as several color conversion algorithms.
 */

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "NightwaveCore.h"

class EXPORT Color {
	/**
	 * @brief   The Color object class designed to hold color data in virtually every color format.
	 */
	public:
		/**
		 * @brief  Initialization without arguments will set the color to pure black.
		 */
		Color();

		/**
		 * @brief   Initializes the Color object using RGB values.
		 *
		 * @param[in]  red    The red value.
		 * @param[in]  green  The green value.
		 * @param[in]  blue   The blue value.
		 */
		Color(int red, int green, int blue);

		/**
		 * @brief      Initializes the Color object using CMYK values.
		 *
		 * @param[in]  cyan     The cyan value.
		 * @param[in]  magenta  The magenta value.
		 * @param[in]  yellow   The yellow value.
		 * @param[in]  black    The black value.
		 */
		Color(int cyan, int magenta, int yellow, int black);

		/**
		 * @brief      Initializes the Color object using a wxColour object.
		 *
		 * @param[in]  color  The wxColour object to copy from.
		 */
		Color(wxColour color);

		void SetRGB(int red, int green, int blue); ///< Sets the Color object to specified color in RGB format.
		void SetHSL(int hue, int saturation, int luminosity); ///< Sets the Color object to specified color in HSL format.
		void SetHSV(int hue, int saturation, int velocity); ///< Sets the Color object to specified color in HSV format.
		void SetYIQ(int yluma, int inphase, int quadrature); ///< Sets the Color object to specified color in YIQ format.
		void SetXYZ(int xresponse, int yluminance, int zblue); ///< Sets the Color object to specified color in XYZ format.
		void SetLAB(int luminosity, int apoint, int bpoint); ///< Sets the Color object to specified color in LAB format.
		void SetCMYK(int cyan, int magenta, int yellow, int black); ///< Sets the Color object to specified color in CMYK format.

		int* AsRGB(); ///< Returns an int array of the Color in RGB format.
		int* AsHSL(); ///< Returns an int array of the Color in HSL format.
		int* AsHSV(); ///< Returns an int array of the Color in HSV format.
		int* AsYIQ(); ///< Returns an int array of the Color in YIQ format.
		int* AsXYZ(); ///< Returns an int array of the Color in XYZ format.
		int* AsLAB(); ///< Returns an int array of the Color in LAB format.
		int* AsCMYK(); ///< Returns an int array of the Color in CMYK format.

		operator wxColour() const; ///< Returns the Color object as a wxColour object.
	
		/**
		 * @brief      Checks to see if the two colors match using RGB comparison.
		 *
		 * @param      a     The other color to compare.
		 *
		 * @retval TRUE  Both colors are the same.
		 * @retval FALSE The colors are different.
		 */
		bool operator==(Color &a);

	private:
		int RGB[3] = {0, 0, 0};
		int HSL[3] = {0, 0, 0};
		int HSV[3] = {0, 0, 0};
		int YIQ[3] = {0, 0, 0};
		int XYZ[3] = {0, 0, 0};
		int LAB[3] = {0, 0, 0};
		int CMYK[4] = {0, 0, 0, 0};
};

/// \todo Document me!
namespace ColorConverter {
	// Color conversion helpers
	EXPORT double Hue2RGB(double cc_p, double cc_q, double cc_t);
	EXPORT double XYZ2H(double cc_q);
	EXPORT double LAB_compare_RGB(int red1, int green1, int blue1, int red2, int green2, int blue2);
	EXPORT double LAB_compare_RGB(wxColour color1, wxColour color2);

	// Base converters
	EXPORT void RGB2HSL(int red, int green, int blue, int *hue, int *saturation, int *luminosity);
	EXPORT void HSL2RGB(int hue, int saturation, int luminosity, int *red, int *green, int *blue);
	EXPORT void RGB2HSV(double red, double green, double blue, double *hue, double *saturation, double *velocity); /// \todo Convert to int (0-255)
	EXPORT void HSV2RGB(double hue, double saturation, double velocity, double *red, double *green, double *blue); /// \todo Convert to int (0-255)
	EXPORT void RGB2CMYK(double red, double green, double blue, double *cyan, double *magenta, double *yellow, double *black); /// \todo Convert to int (0-255)
	EXPORT void CMYK2RGB(double cyan, double magenta, double yellow, double black, double *red, double *green, double *blue); /// \todo Convert to int (0-255)
	EXPORT void RGB2YIQ(double red, double green, double blue, double *yluma, double *inphase, double *quadrature); /// \todo Convert to int (0-255)
	EXPORT void YIQ2RGB(double yluma, double inphase, double quadrature, double *red, double *green, double *blue); /// \todo Convert to int (0-255)
	EXPORT void RGB2XYZ(int red, int green, int blue, double *xresponse, double *yluminance, double *zblue); /// \todo Convert to int (0-255)
	EXPORT void XYZ2RGB(double xresponse, double yluminance, double zblue, int *red, int *green, int *blue); /// \todo Convert to int (0-255)
	EXPORT void XYZ2LAB(double xresponse, double yluminance, double zblue, double *luminosity, double *apoint, double *bpoint); /// \todo Convert to int (0-255)
	EXPORT void LAB2XYZ(double luminosity, double apoint, double bpoint, double *xresponse, double *yluminance, double *zblue); /// \todo Convert to int (0-255)

	// Two-step converters
	EXPORT void RGB2LAB(int red, int green, int blue, double *luminosity, double *apoint, double *bpoint); /// \todo Convert to int (0-255)
	EXPORT void LAB2RGB(double luminosity, double apoint, double bpoint, int *red, int *green, int *blue); /// \todo Convert to int (0-255)
	EXPORT void HSL2HSV(double hue, double saturation, double luminosity, double *_hue, double *_saturation, double *velocity); /// \todo Convert to int (0-255)
	EXPORT void HSV2HSL(double hue, double saturation, double velocity, double *_hue, double *_saturation, double *luminosity); /// \todo Convert to int (0-255)
	EXPORT void HSL2CMYK(double hue, double saturation, double luminosity, double *cyan, double *magenta, double *yellow, double *black); /// \todo Convert to int (0-255)
	EXPORT void CMYK2HSL(double cyan, double magenta, double yellow, double black, double *hue, double *saturation, double *luminosity); /// \todo Convert to int (0-255)
	EXPORT void HSV2CMYK(double hue, double saturation, double velocity, double *cyan, double *magenta, double *yellow, double *black); /// \todo Convert to int (0-255)
	EXPORT void CMYK2HSV(double cyan, double magenta, double yellow, double black, double *hue, double *saturation, double *velocity); /// \todo Convert to int (0-255)
	EXPORT void HSL2YIQ(double hue, double saturation, double luminosity, double *yluma, double *inphase, double *quadrature); /// \todo Convert to int (0-255)
	EXPORT void YIQ2HSL(double yluma, double inphase, double quadrature, double *hue, double *saturation, double *luminosity); /// \todo Convert to int (0-255)
	EXPORT void HSV2YIQ(double hue, double saturation, double velocity, double *yluma, double *inphase, double *quadrature); /// \todo Convert to int (0-255)
	EXPORT void YIQ2HSV(double yluma, double inphase, double quadrature, double *hue, double *saturation, double *velocity); /// \todo Convert to int (0-255)
	EXPORT void CMYK2YIQ(double cyan, double magenta, double yellow, double black, double *yluma, double *inphase, double *quadrature); /// \todo Convert to int (0-255)
	EXPORT void YIQ2CMYK(double yluma, double inphase, double quadrature, double *cyan, double *magenta, double *yellow, double *black); /// \todo Convert to int (0-255)
};

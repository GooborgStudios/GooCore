//
// GooCore - TextWrap.h
// ©2018 Gooborg Studios: Vinyl Darkscratch, Light Apacha.
// http://www.gooborg.com/
//

#pragma once

#ifdef USE_WXWIDGETS // Entire file requires wxWidgets

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "GooCore.h"

/// \todo Document me!
EXPORT void DrawWrappedText(std::string text, wxDC &canvas, wxRect box);

#endif

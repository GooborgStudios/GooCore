//
// Nightwave Core - TextWrap.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

#pragma once

#ifdef USE_WXWIDGETS // Entire file requires wxWidgets

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "NightwaveCore.h"

/// \todo Document me!
EXPORT void DrawWrappedText(std::string text, wxDC &canvas, wxRect box);

#endif

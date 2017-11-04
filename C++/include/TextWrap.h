//
// Nightwave Core - TextWrap.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "NightwaveCore.h"

EXPORT void DrawWrappedText(std::string text, wxDC &canvas, wxRect box);

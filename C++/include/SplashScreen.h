//
// Nightwave Core - SplashScreen.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

/**
 * @file   SplashScreen.h
 * @brief  This file holds the SplashScreen class, which is a modified copy of wxWidgets' wxSplashScreen class intended to allow for more than just a non-transparent image.
 */

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wx/bitmap.h"
#include "wx/eventfilter.h"
#include "wx/frame.h"

#include "NightwaveCore.h"

class EXPORT SplashScreen: public wxFrame, public wxEventFilter {
	public:
		/**
		 * @brief      This function initializes the splash screen window with a given image and other parameters.
		 *
		 * @param      parent          The parent window.
		 * @param[in]  window_id       The window identifier.
		 * @param      bitmap          The image to display as the splash screen.
		 * @param[in]  copyright       The copyright text.
		 * @param[in]  copyrightbox    The bounding box of the copyright text.
		 * @param[in]  copyrightcolor  The copyright text color.
		 * @param[in]  copyrightfont   The copyright text font.
		 * @param[in]  loadingtextbox  The progress text bounding box.
		 * @param[in]  loadingbarbox   The loading bar bounding box.
		 */
		SplashScreen(wxWindow *parent, wxWindowID window_id, wxBitmap &bitmap, wxString copyright = "", wxRect copyrightbox = wxRect(0, 0, 0, 0), wxColor copyrightcolor = *wxBLACK, wxFont copyrightfont = wxFont(), wxRect loadingtextbox = wxRect(0, 0, 0, 0), wxRect loadingbarbox = wxRect(0, 0, 0, 0));
		/// \todo Document me!
		virtual ~SplashScreen();
		/// \todo Document me!
		void OnCloseWindow(wxCloseEvent &event);
		/// \todo Document me!
		void OnNotify(wxTimerEvent &event);
		/// \todo Document me!
		void OnEraseBackground(wxEraseEvent &event);
		/// \todo Document me!
		void OnPaint(wxPaintEvent &event);
		/// \todo Document me!
		void render(wxDC &canvas);
		/// \todo Document me!
		void SetBitmap(wxBitmap &bitmap);
		/// \todo Document me!
		wxBitmap &GetBitmap();
		/// \todo Document me!
		void SetCopyright(wxString copyright);
		/// \todo Document me!
		wxString GetCopyright();
		/// \todo Document me!
		void SetCopyrightBox(wxRect copyrightbox);
		/// \todo Document me!
		wxRect GetCopyrightBox();
		/// \todo Document me!
		void SetTextColor(wxColor textcolor);
		/// \todo Document me!
		wxColor GetTextColor();
		/// \todo Document me!
		void SetTextFont(wxFont textfont);
		/// \todo Document me!
		wxFont GetTextFont();
		/// \todo Document me!
		void SetProgress(int progress);
		/// \todo Document me!
		void SetProgress(int progress, std::string progresstext);
		/// \todo Document me!
		int GetProgress();
		/// \todo Document me!
		virtual int FilterEvent(wxEvent &event);

	protected:
		wxBitmap m_bitmap;
		wxString m_copyright;
		wxRect m_copyrightbox;
		wxFont m_textfont;
		wxColor m_textcolor;
		wxRect m_loadingtextbox;
		wxRect m_loadingbarbox;
		int m_progress;
		std::string m_progresstext;

	DECLARE_EVENT_TABLE()
	wxDECLARE_NO_COPY_CLASS(SplashScreen);
};

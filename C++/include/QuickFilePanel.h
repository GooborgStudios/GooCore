//
// NightwaveCore - QuickFilePanel.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

/**
 * @file   QuickFilePanel.h
 * @brief  This file holds the quick file access panel class.
 */

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/dataview.h>
#include <wx/imaglist.h>

#ifdef LIB_MAGIC
	#include <magic.h>
#endif

#include <vector>
#include <map>

// Quick file access panel
class QuickFilePanel: public wxPanel {
	public:
		/// \todo String vector of search paths: Add and remove files/folders (to search paths), Drag-and-drop files/folders (add to search paths)
		/// \todo Dynamic refresh
		/// \todo Sticky search paths (retained after program quits)
		/// \todo Document me!
		QuickFilePanel(wxPanel *parent, wxWindowID window_id);
		/// \todo Document me!
		~QuickFilePanel();
		/// \todo Document me!
		void RefreshFileList();
		/// \todo Document me!
		void Update();
		/// \todo Document me!
		void AddPath(std::string path);
		/// \todo Document me!
		void BlacklistFileType(std::string type);
		/// \todo Document me!
		void SetFileTypeIcon(std::string type, wxIcon icon);
		/// \todo Document me!
		void SetFileTypeIcon(std::string type, std::string icon_path);
		/// \todo Document me!
		wxString GetFilePath(wxDataViewItem item);
		/// \todo Document me!
		void ChangeSelectedFile(wxDataViewEvent &event);
		//void RenameFile(wxDataViewEvent &event);
		
	private:
		/// \todo On Windows, LibMagic doesn't exist.  We're setting the file type to "*", but we should utilize the extension to determine the MIME type.  Or compile LibMagic/find a similar library for Windows.
		void ListDirectory(wxString path, wxDataViewItem *files);
		
		wxPanel *m_parent;
		wxBoxSizer *sizer;
		wxDataViewTreeCtrl *filelistbox;
		std::vector<std::string> search_paths;
		wxImageList *icon_list;
		std::map<std::string, int> file_types;
		#ifdef LIB_MAGIC
			magic_t myt;
		#endif
};

wxDECLARE_EVENT(FILE_SELECT, wxCommandEvent);

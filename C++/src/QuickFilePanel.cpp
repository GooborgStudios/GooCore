//
// NightwaveCore - QuickFilePanel.cpp
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co/
//

#include "QuickFilePanel.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/file.h>
#include <wx/dir.h>
#include <wx/dataview.h>
#include <wx/event.h>
#include <wx/imaglist.h>
#include <wx/artprov.h>
#include <wx/treebase.h>
#include <wx/validate.h>
#include <wx/file.h>

#ifdef LIB_MAGIC
	#include <magic.h>
#endif

#include "NightwaveCore.h"

wxDEFINE_EVENT(FILE_SELECT, wxCommandEvent);

// Initialize the file panel and it's elements
QuickFilePanel::QuickFilePanel(wxPanel *parent, wxWindowID window_id) : wxPanel(parent, window_id, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
	m_parent = parent;

	#ifdef LIB_MAGIC
		myt = magic_open(MAGIC_ERROR | MAGIC_MIME_TYPE);
		magic_load(myt, NULL);
	#endif

	// Initialize icons
	icon_list = new wxImageList();
	icon_list->Add(wxArtProvider::GetIcon(wxART_FOLDER, wxART_MENU));
	icon_list->Add(wxArtProvider::GetIcon(wxART_FOLDER_OPEN, wxART_MENU));
	file_types["*"] = icon_list->Add(wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_MENU));

	// Set up the file list
	wxWindowID ID_QuickFilePanel_Tree = wxWindow::NewControlId();
	filelistbox = new wxDataViewTreeCtrl(this, ID_QuickFilePanel_Tree, wxPoint(-1, -1), wxSize(-1, -1), wxDV_SINGLE | wxDV_NO_HEADER);
	filelistbox->SetImageList(icon_list);
	RefreshFileList();

	Connect(ID_QuickFilePanel_Tree, wxEVT_DATAVIEW_SELECTION_CHANGED, (wxObjectEventFunction)&QuickFilePanel::ChangeSelectedFile);

	sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(filelistbox, 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
	Update();
}

QuickFilePanel::~QuickFilePanel() {
	delete filelistbox;
	delete icon_list;
}

// List all project directories
void QuickFilePanel::RefreshFileList() {
	wxDataViewItem *root_dvi = new wxDataViewItem();
	for (std::string path : search_paths) {
		ListDirectory(wxString(path), root_dvi);
	}
//	ListDirectory(max_user_library_path, root_dvi);
//	ListDirectory(max_shared_library_path, root_dvi);
	// XXX Should also obtain user search paths.
	delete root_dvi;
}

void QuickFilePanel::Update() {
//	this->SetSizer(sizer);
	sizer->Layout();
}

void QuickFilePanel::AddPath(std::string path) {
	search_paths.push_back(path);
}

void QuickFilePanel::BlacklistFileType(std::string type) {
	if (file_types.find(type) != file_types.end() && file_types[type] >= 0) {
//		icon_list->Remove(file_types[type]);
		// XXX This may shift the indexes over!
	}
	file_types[type] = -1;
}

void QuickFilePanel::SetFileTypeIcon(std::string type, wxIcon icon) {
	if (file_types.find(type) != file_types.end() && file_types[type] >= 0) {
		icon_list->Replace(file_types[type], icon);
	} else {
		file_types[type] = icon_list->Add(icon);
	}
}

void QuickFilePanel::SetFileTypeIcon(std::string type, std::string icon_path) {
	wxIcon icon = wxIcon(getResourcePath(icon_path));
}

wxString QuickFilePanel::GetFilePath(wxDataViewItem item) {
	wxDataViewTreeStore *store = filelistbox->GetStore();
	wxString path;

	for (wxString base_path : search_paths) { // XXX Improve me!
		path = base_path + "/";

		if (!store->IsContainer(item))
			path += filelistbox->GetItemText(store->GetParent(item)) + "/";
		path += filelistbox->GetItemText(item);
		if (wxFile::Exists(path))
			break;
	}
	return path;
}

void QuickFilePanel::ChangeSelectedFile(wxDataViewEvent &event) {
	if (!filelistbox->GetStore()->IsContainer(event.GetItem())) {
		wxCommandEvent evt(FILE_SELECT);
		evt.SetEventObject(this);
		evt.SetString(GetFilePath(event.GetItem()));
		ProcessEvent(evt);
	}
}

// void QuickFilePanel::RenameFile(wxDataViewEvent &event) {
// 	std::cout << filelistbox->GetItemText(event.GetItem());
//  std::cout << " > " << event.GetValue().GetType() << std::endl;
// }

// Obtain all of the contents of a directory and add it to a specified file list
void QuickFilePanel::ListDirectory(wxString path, wxDataViewItem *files) {
	wxDataViewItem *current_file;
	wxDir dir(path);
	wxString filename;
	std::string filetype;
	bool cont;
	int icon_index;

	if (!dir.IsOpened()) {
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		return;
	}

	// List files
	cont = dir.GetFirst(&filename, "", wxDIR_FILES);
	while (cont) {
		#ifdef LIB_MAGIC
		filetype = magic_file(myt, (path + "/" + filename).c_str());
		#else
		filetype = "*"; // XXX Use file extension instead
		#endif

		if (file_types.find(filetype) == file_types.end()) {
			icon_index = file_types["*"];
		} else {
			icon_index = file_types[filetype];
		}

		if (icon_index >= 0) filelistbox->AppendItem(*files, filename, icon_index);
		cont = dir.GetNext(&filename);
	}

	// List directories
	cont = dir.GetFirst(&filename, "", wxDIR_DIRS);
	while (cont) {
		current_file = new wxDataViewItem(filelistbox->AppendContainer(*files, filename, 0, 1));
		ListDirectory(path + "/" + filename, current_file);
		// Obtain the contents of the directories by running the function in itself
		cont = dir.GetNext(&filename);
		delete current_file;
	}
}

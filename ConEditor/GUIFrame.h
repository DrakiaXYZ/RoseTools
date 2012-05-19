///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuNew 1000
#define idMenuOpen 1001
#define idMenuSave 1002
#define idMenuSaveAs 1003
#define idMenuImportLuc 1004
#define idMenuExportLuc 1005
#define idMenuQuit 1006
#define idMenuAbout 1007

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* helpMenu;
		wxStaticText* lblDialog;
		wxButton* btnDialogLeft;
		wxTextCtrl* txtDialog;
		wxStaticText* lblDialogCount;
		wxButton* btnDialogRight;
		wxStaticText* lblEntry;
		wxButton* btnEntryLeft;
		wxTextCtrl* txtEntry;
		wxStaticText* lblEntryCount;
		wxButton* btnEntryRight;
		wxStaticText* lblEntryID;
		wxTextCtrl* txtEntryId;
		wxStaticText* lblCommand;
		wxChoice* drpCommand;
		wxStaticText* lblData;
		wxTextCtrl* txtData;
		wxStaticText* lblCondFunc;
		wxTextCtrl* txtCondFunc;
		wxStaticText* lblRewdFunc;
		wxTextCtrl* txtRewdFunc;
		wxStaticText* lblStrId;
		wxTextCtrl* txtStrId;
		wxButton* btnNewDialog;
		wxButton* btnNewEntry;
		wxButton* btnExportLUC;
		wxButton* btnImportLUC;
		wxButton* btnDeleteEntry;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnNew( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOpen( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveAs( wxCommandEvent& event ){ event.Skip(); }
		virtual void ImportLUC( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void DialogLeft( wxCommandEvent& event ){ event.Skip(); }
		virtual void DialogEnter( wxCommandEvent& event ){ event.Skip(); }
		virtual void DialogRight( wxCommandEvent& event ){ event.Skip(); }
		virtual void EntryLeft( wxCommandEvent& event ){ event.Skip(); }
		virtual void EntryEnter( wxCommandEvent& event ){ event.Skip(); }
		virtual void EntryRight( wxCommandEvent& event ){ event.Skip(); }
		virtual void SaveData( wxCommandEvent& event ){ event.Skip(); }
		virtual void NewDialog( wxCommandEvent& event ){ event.Skip(); }
		virtual void NewEntry( wxCommandEvent& event ){ event.Skip(); }
		virtual void ExportLUC( wxCommandEvent& event ){ event.Skip(); }
		virtual void DeleteEntry( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CON Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,396 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIFrame();
	
};

#endif //__GUIFrame__

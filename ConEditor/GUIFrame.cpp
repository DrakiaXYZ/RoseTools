///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileNew;
	menuFileNew = new wxMenuItem( fileMenu, idMenuNew, wxString( wxT("&New") ) + wxT('\t') + wxT("Ctrl+N"), wxT("Create a new CON file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileNew );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( fileMenu, idMenuOpen, wxString( wxT("&Open") ) + wxT('\t') + wxT("Ctrl+O"), wxT("Open a CON file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileOpen );
	
	wxMenuItem* menuFileSave;
	menuFileSave = new wxMenuItem( fileMenu, idMenuSave, wxString( wxT("&Save") ) + wxT('\t') + wxT("Ctrl+S"), wxT("Save the current file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileSave );
	
	wxMenuItem* menuFileSaveAs;
	menuFileSaveAs = new wxMenuItem( fileMenu, idMenuSaveAs, wxString( wxT("Save &As") ) + wxT('\t') + wxT("Ctrl+Shift+S"), wxT("Save in a new file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileSaveAs );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuImportLuc;
	menuImportLuc = new wxMenuItem( fileMenu, idMenuImportLuc, wxString( wxT("&Import LUC") ) + wxT('\t') + wxT("Ctrl+I"), wxT("Import a compiled LUA file"), wxITEM_NORMAL );
	fileMenu->Append( menuImportLuc );
	
	wxMenuItem* MenuExportLuc;
	MenuExportLuc = new wxMenuItem( fileMenu, idMenuExportLuc, wxString( wxT("&Export LUC") ) + wxT('\t') + wxT("Ctrl+E"), wxT("Export the LUC File"), wxITEM_NORMAL );
	fileMenu->Append( MenuExportLuc );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") );
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") );
	
	this->SetMenuBar( mbar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	lblDialog = new wxStaticText( this, wxID_ANY, wxT("Dialog"), wxDefaultPosition, wxSize( 75,-1 ), 0 );
	lblDialog->Wrap( -1 );
	lblDialog->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( lblDialog, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnDialogLeft = new wxButton( this, wxID_ANY, wxT("<"), wxDefaultPosition, wxSize( 20,-1 ), 0 );
	btnDialogLeft->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( btnDialogLeft, 0, wxALL, 5 );
	
	txtDialog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER|wxSIMPLE_BORDER );
	txtDialog->SetMaxLength( 10 ); 
	bSizer5->Add( txtDialog, 0, wxALL, 5 );
	
	lblDialogCount = new wxStaticText( this, wxID_ANY, wxT("/#"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	lblDialogCount->Wrap( -1 );
	lblDialogCount->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( lblDialogCount, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnDialogRight = new wxButton( this, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( 20,-1 ), 0 );
	btnDialogRight->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( btnDialogRight, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer5, 0, wxALIGN_CENTER, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	lblEntry = new wxStaticText( this, wxID_ANY, wxT("Entry "), wxDefaultPosition, wxSize( 75,-1 ), 0 );
	lblEntry->Wrap( -1 );
	lblEntry->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer6->Add( lblEntry, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnEntryLeft = new wxButton( this, wxID_ANY, wxT("<"), wxDefaultPosition, wxSize( 20,-1 ), 0 );
	btnEntryLeft->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer6->Add( btnEntryLeft, 0, wxALL, 5 );
	
	txtEntry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER|wxSIMPLE_BORDER );
	txtEntry->SetMaxLength( 10 ); 
	bSizer6->Add( txtEntry, 0, wxALL, 5 );
	
	lblEntryCount = new wxStaticText( this, wxID_ANY, wxT("/#"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	lblEntryCount->Wrap( -1 );
	lblEntryCount->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer6->Add( lblEntryCount, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnEntryRight = new wxButton( this, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( 20,-1 ), 0 );
	btnEntryRight->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 76, 90, 90, false, wxEmptyString ) );
	
	bSizer6->Add( btnEntryRight, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer6, 0, wxALIGN_CENTER, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	lblEntryID = new wxStaticText( this, wxID_ANY, wxT("Entry ID:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblEntryID->Wrap( -1 );
	bSizer8->Add( lblEntryID, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txtEntryId = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSIMPLE_BORDER );
	txtEntryId->SetMaxLength( 10 ); 
	txtEntryId->Enable( false );
	
	bSizer8->Add( txtEntryId, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer8, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	lblCommand = new wxStaticText( this, wxID_ANY, wxT("Command:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblCommand->Wrap( -1 );
	bSizer9->Add( lblCommand, 0, wxALIGN_CENTER|wxALL, 5 );
	
	wxString drpCommandChoices[] = { wxT("Close Dialog"), wxT("Load As Menu (Don't Use)"), wxT("Load As Menu"), wxT("Load As NPC Text"), wxT("Return to NPC Text") };
	int drpCommandNChoices = sizeof( drpCommandChoices ) / sizeof( wxString );
	drpCommand = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, drpCommandNChoices, drpCommandChoices, 0 );
	drpCommand->SetSelection( 0 );
	bSizer9->Add( drpCommand, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer9, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	lblData = new wxStaticText( this, wxID_ANY, wxT("Target Dialog:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblData->Wrap( -1 );
	bSizer10->Add( lblData, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txtData = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSIMPLE_BORDER );
	txtData->SetMaxLength( 10 ); 
	bSizer10->Add( txtData, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer10, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	lblCondFunc = new wxStaticText( this, wxID_ANY, wxT("Condition Function:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblCondFunc->Wrap( -1 );
	bSizer11->Add( lblCondFunc, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txtCondFunc = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSIMPLE_BORDER );
	txtCondFunc->SetMaxLength( 32 ); 
	bSizer11->Add( txtCondFunc, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer11, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	lblRewdFunc = new wxStaticText( this, wxID_ANY, wxT("Reward Function:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblRewdFunc->Wrap( -1 );
	bSizer12->Add( lblRewdFunc, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txtRewdFunc = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSIMPLE_BORDER );
	txtRewdFunc->SetMaxLength( 32 ); 
	bSizer12->Add( txtRewdFunc, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer12, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	lblStrId = new wxStaticText( this, wxID_ANY, wxT("LTB Row:"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
	lblStrId->Wrap( -1 );
	bSizer13->Add( lblStrId, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txtStrId = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSIMPLE_BORDER );
	txtStrId->SetMaxLength( 10 ); 
	bSizer13->Add( txtStrId, 1, wxALL, 5 );
	
	bSizer4->Add( bSizer13, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	btnNewDialog = new wxButton( this, wxID_ANY, wxT("New Dialog"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( btnNewDialog, 0, wxALL, 5 );
	
	btnNewEntry = new wxButton( this, wxID_ANY, wxT("New Entry"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( btnNewEntry, 0, wxALL, 5 );
	
	btnExportLUC = new wxButton( this, wxID_ANY, wxT("Export LUC"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( btnExportLUC, 0, wxALL, 5 );
	
	btnImportLUC = new wxButton( this, wxID_ANY, wxT("Import LUC"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( btnImportLUC, 0, wxALL, 5 );
	
	bSizer4->Add( bSizer14, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer131->Add( bSizer141, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	btnDeleteEntry = new wxButton( this, wxID_ANY, wxT("Del Entry"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( btnDeleteEntry, 0, wxALL, 5 );
	
	bSizer131->Add( bSizer15, 1, 0, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer131->Add( bSizer16, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer131->Add( bSizer17, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer131, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnNew ) );
	this->Connect( menuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Connect( menuFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSave ) );
	this->Connect( menuFileSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveAs ) );
	this->Connect( menuImportLuc->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::ImportLUC ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnDialogLeft->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DialogLeft ), NULL, this );
	txtDialog->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::DialogEnter ), NULL, this );
	btnDialogRight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DialogRight ), NULL, this );
	btnEntryLeft->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::EntryLeft ), NULL, this );
	txtEntry->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::EntryEnter ), NULL, this );
	btnEntryRight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::EntryRight ), NULL, this );
	txtEntryId->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	drpCommand->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtData->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtCondFunc->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtRewdFunc->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtStrId->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	btnNewDialog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::NewDialog ), NULL, this );
	btnNewEntry->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::NewEntry ), NULL, this );
	btnExportLUC->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ExportLUC ), NULL, this );
	btnImportLUC->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ImportLUC ), NULL, this );
	btnDeleteEntry->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DeleteEntry ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnNew ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::ImportLUC ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnDialogLeft->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DialogLeft ), NULL, this );
	txtDialog->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::DialogEnter ), NULL, this );
	btnDialogRight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DialogRight ), NULL, this );
	btnEntryLeft->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::EntryLeft ), NULL, this );
	txtEntry->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::EntryEnter ), NULL, this );
	btnEntryRight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::EntryRight ), NULL, this );
	txtEntryId->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	drpCommand->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtData->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtCondFunc->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtRewdFunc->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	txtStrId->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::SaveData ), NULL, this );
	btnNewDialog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::NewDialog ), NULL, this );
	btnNewEntry->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::NewEntry ), NULL, this );
	btnExportLUC->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ExportLUC ), NULL, this );
	btnImportLUC->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ImportLUC ), NULL, this );
	btnDeleteEntry->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::DeleteEntry ), NULL, this );
}

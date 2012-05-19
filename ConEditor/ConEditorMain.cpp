/***************************************************************
 * Name:      ConEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Created:   2008-06-15
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:   GNU GPL v3 - Pretty much do whatever you want with it.
 **************************************************************/

#include "ConEditorMain.h"

ConEditorFrame::ConEditorFrame(wxFrame *frame)
    : GUIFrame(frame)
{
  //curFile = _("EM01-019.CON");
  //ConFile.LoadFile(_S(curFile));
  curFile = _("");
  curDialog = 0;
  curEntry = 0;
  change = false;
  //updateData();
  Open();
}

ConEditorFrame::~ConEditorFrame()
{
}

void ConEditorFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void ConEditorFrame::OnNew( wxCommandEvent& event ) {
  ConFile.New();
  statusBar->SetStatusText(_("Created new CON file"));
  curFile = _("");
  SetTitle(_("CON Editor - New File*"));
  curDialog = 0;
  curEntry = 0;
  updateData();
  change = true;
}

void ConEditorFrame::OnOpen( wxCommandEvent& event ) {
  Open();
}

void ConEditorFrame::Open() {
  // Open File
  wxString Msg = _("Select the CON file");
  wxString Dir = _("");
  wxString FileName = _("");
  wxString Ext = _("con");
  wxString WildCard = _("ROSE Online CON File(*.con)|*.con");
  int Flags = wxFD_OPEN | wxFD_FILE_MUST_EXIST;
  wxString File = wxFileSelector(Msg, Dir, FileName, Ext, WildCard, Flags);
  if (!File.empty()) {
    ConFile.LoadFile(_S(File));
    curFile = File;
    SetTitle(curFile.Right(30).Prepend(_("...")));
    curDialog = 0;
    curEntry = 0;
    updateData();
  } else
    statusBar->SetStatusText(_("User cancelled opening CON file."));
}

void ConEditorFrame::OnSave( wxCommandEvent& event ) {
  if (ConFile.getFilename() == "") {
    SaveAs();
    return;
  }
  if (!ConFile.IsOpen()) return;
  // Save current file
  ConFile.WriteFile(_S(curFile));
  change = false;
}

void ConEditorFrame::OnSaveAs( wxCommandEvent& event ) {
  SaveAs();
}

void ConEditorFrame::SaveAs() {
  if (!ConFile.IsOpen()) return;
  // Save as new file
  wxString Msg = _("Select the output file");
  wxString Dir = _("");
  wxString FileName = _("");
  wxString Ext = _("con");
  wxString WildCard = _("ROSE Online CON File(*.con)|*.con");
  int Flags = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
  wxString File = wxFileSelector(Msg, Dir, FileName, Ext, WildCard, Flags);
  if (!File.empty()) {
    ConFile.WriteFile(_S(File));
    curFile = File;
    SetTitle(curFile.Right(30).Prepend(_("...")));
    statusBar->SetStatusText(_("CON File Saved."));
  } else {
    statusBar->SetStatusText(_("Save CON Cancelled by user."));
  }
  change = false;
}

void ConEditorFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void ConEditorFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(_("CON Editor for ROSE Online created by Steven \"Drakia\" Scott\nSpecial thanks to ExJam and Brett19 for file formats :D"), _("About"));
}

void ConEditorFrame::DialogLeft(wxCommandEvent &event) {
    if (!ConFile.IsOpen()) return;
    curEntry = 0;
    if (curDialog <= 0) curDialog = ConFile.getDialogCount() - 1;
    else curDialog--;
    updateData();
}

void ConEditorFrame::DialogRight(wxCommandEvent &event) {
    if (!ConFile.IsOpen()) return;
    curEntry = 0;
    if (curDialog + 1 >= ConFile.getDialogCount()) curDialog = 0;
    else curDialog++;
    updateData();
}

void ConEditorFrame::EntryLeft(wxCommandEvent &event) {
    if (!ConFile.IsOpen()) return;
    if (ConFile.getEntryCount(curDialog) == 0) return;
    if (curEntry == 0) curEntry = ConFile.getEntryCount(curDialog) - 1;
    else curEntry--;
    updateData();
}

void ConEditorFrame::EntryRight(wxCommandEvent &event) {
    if (!ConFile.IsOpen()) return;
    if (ConFile.getEntryCount(curDialog) == 0) return;
    if (curEntry + 1 >= ConFile.getEntryCount(curDialog)) curEntry = 0;
    else curEntry++;
    updateData();
}

void ConEditorFrame::DialogEnter( wxCommandEvent& event ) {
    if (!ConFile.IsOpen()) return;
    long dval;
    if (!txtDialog->GetValue().ToLong(&dval))
      return;
    if (dval < 0) dval = 0;
    if (dval >= (long)ConFile.getDialogCount()) dval = ConFile.getDialogCount() - 1;
    curDialog = dval;
    if (curEntry > ConFile.getEntryCount(curDialog)) curEntry = ConFile.getEntryCount(curDialog) - 1;
    updateData();
}

void ConEditorFrame::EntryEnter( wxCommandEvent& event ) {
    if (!ConFile.IsOpen()) return;
    if (ConFile.getEntryCount(curDialog) == 0) return;
    long eval;
    if (!txtEntry->GetValue().ToLong(&eval))
      return;
    if (eval < 0) eval = 0;
    if (eval >= (long)ConFile.getEntryCount(curDialog)) eval = ConFile.getEntryCount(curDialog) - 1;
    curEntry = eval;
    updateData();
}

void ConEditorFrame::NewDialog( wxCommandEvent& event ){
    if (!ConFile.IsOpen()) return;
    curDialog = ConFile.addDialog();
    curEntry = 0;
    updateData();
    change = true;
}

void ConEditorFrame::NewEntry( wxCommandEvent& event ){
    if (!ConFile.IsOpen()) return;
    curEntry = ConFile.addEntry(curDialog);
    updateData();
    change = true;
}

void ConEditorFrame::DeleteEntry( wxCommandEvent& event ) {
    if (!ConFile.IsOpen()) return;
    curEntry = ConFile.deleteEntry(curDialog, curEntry);
    updateData();
    change = true;
}

void ConEditorFrame::ExportLUC( wxCommandEvent& event ){
  if (!ConFile.IsOpen()) return;
  wxString expMsg = _("Select the output file");
  wxString expDir = _("");
  wxString expFileName = _("");
  wxString expExt = _("luc");
  wxString expWildCard = _("Compiled LUA Script(*.luc)|*.luc");
  int expFlags = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
  wxString expFile = wxFileSelector(expMsg, expDir, expFileName, expExt, expWildCard, expFlags);
  if (!expFile.empty()) {
    if (ConFile.writeLuc(_S(expFile)))
      statusBar->SetStatusText(_("LUC Saved to file."));
    else
      statusBar->SetStatusText(_("Error saving LUC to file!"));
  } else {
    statusBar->SetStatusText(_("Save LUC Cancelled by user."));
  }
}

void ConEditorFrame::ImportLUC( wxCommandEvent& event ){
  if (!ConFile.IsOpen()) return;
  wxString impMsg = _("Select the compiled LUA script");
  wxString impDir = _("");
  wxString impFileName = _("");
  wxString impExt = _("luc");
  wxString impWildCard = _("Compiled LUA Script(*.luc)|*.luc");
  int impFlags = wxFD_OPEN | wxFD_FILE_MUST_EXIST;
  wxString impFile = wxFileSelector(impMsg, impDir, impFileName, impExt, impWildCard, impFlags);
  if (!impFile.empty()) {
    if (ConFile.loadLuc(_S(impFile)))
      statusBar->SetStatusText(_("LUC File loaded into memory."));
    else
      statusBar->SetStatusText(_("Error loading LUC File!"));
  } else {
    statusBar->SetStatusText(_("Load LUC Cancelled by user."));
  }
  change = true;
}

void ConEditorFrame::SaveData( wxCommandEvent& event ) {
  if (!ConFile.IsOpen()) return;
  if (ConFile.getEntryCount(curDialog) == 0) return;
  if (!txtEntryId->GetValue().IsNumber())
    txtEntryId->SetValue(_("0"));

  if (!txtData->GetValue().IsNumber())
    txtData->SetValue(_("0"));

  if (!txtStrId->GetValue().IsNumber())
    txtStrId->SetValue(_("0"));

  wxString EntryId = txtEntryId->GetValue();
  wxString Data = txtData->GetValue();
  wxString CondFunc = txtCondFunc->GetValue();
  wxString RewdFunc = txtRewdFunc->GetValue();
  wxString StrId = txtStrId->GetValue();

  CON::entry Entry;
  EntryId.ToULong(&Entry.entryId);
  Entry.command = drpCommand->GetSelection();
  Data.ToULong(&Entry.data);
  memset(Entry.condFunc, '\0', 0x20);
  memcpy(Entry.condFunc, _S(CondFunc).c_str(), CondFunc.length());
  memset(Entry.rewdFunc, '\0', 0x20);
  memcpy(Entry.rewdFunc, _S(RewdFunc).c_str(), RewdFunc.length());
  StrId.ToULong(&Entry.strId);

  ConFile.setEntry(curDialog, curEntry, Entry);
  change = true;
}

void ConEditorFrame::updateData() {
    if (!ConFile.IsOpen()) return;
    char buffer[512];
    sprintf(buffer, "%d", (UINT)curDialog);
    txtDialog->SetValue(_U(buffer));
    sprintf(buffer, "%d", (UINT)curEntry);
    txtEntry->SetValue(_U(buffer));

    int maxDlg = (INT)ConFile.getDialogCount();
    maxDlg--;

    int maxEnt = (INT)ConFile.getEntryCount(curDialog);
    maxEnt--;

    sprintf(buffer, "/%d", maxDlg);
    lblDialogCount->SetLabel(_U(buffer));
    sprintf(buffer, "/%d", maxEnt);
    lblEntryCount->SetLabel(_U(buffer));

    // Only fill in Entry info if there are entries to read ;)
    if (maxEnt >= 0) {
      CON::entry Entry = ConFile.getEntry(curDialog, curEntry);

      sprintf(buffer, "%ld", curEntry);
      txtEntryId->SetValue(_U(buffer));

      drpCommand->SetSelection(Entry.command);

      sprintf(buffer, "%ld", Entry.data);
      txtData->SetValue(_U(buffer));

      txtCondFunc->SetValue(_U(Entry.condFunc));

      txtRewdFunc->SetValue(_U(Entry.rewdFunc));

      sprintf(buffer, "%ld", Entry.strId);
      txtStrId->SetValue(_U(buffer));
    } else {
      txtEntryId->Clear();
      drpCommand->SetSelection(wxNOT_FOUND);
      txtData->Clear();
      txtCondFunc->Clear();
      txtRewdFunc->Clear();
      txtStrId->Clear();
    }
}


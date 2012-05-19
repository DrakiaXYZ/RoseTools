/***************************************************************
 * Name:      ConEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Created:   2008-06-15
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:
 **************************************************************/

#ifndef CONEDITORMAIN_H
#define CONEDITORMAIN_H



#include "ConEditorApp.h"


#include "GUIFrame.h"
#include "../RoseCommon/confile.h"
#include "../RoseCommon/wxCommon.h"

class ConEditorFrame: public GUIFrame
{
    public:
        ConEditorFrame(wxFrame *frame);
        ~ConEditorFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnNew( wxCommandEvent& event );
        virtual void OnOpen( wxCommandEvent& event );
        virtual void OnSave( wxCommandEvent& event );
        virtual void OnSaveAs( wxCommandEvent& event );
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void DialogLeft( wxCommandEvent& event );
        virtual void DialogEnter( wxCommandEvent& event );
        virtual void DialogRight( wxCommandEvent& event );
        virtual void EntryLeft( wxCommandEvent& event );
        virtual void EntryEnter( wxCommandEvent& event );
        virtual void EntryRight( wxCommandEvent& event );

        virtual void NewDialog( wxCommandEvent& event );
        virtual void NewEntry( wxCommandEvent& event );
        virtual void DeleteEntry( wxCommandEvent& event );
        virtual void ExportLUC( wxCommandEvent& event );
        virtual void ImportLUC( wxCommandEvent& event );
        virtual void SaveData( wxCommandEvent& event );

        void updateData();
        void Open();
        void SaveAs();

        DWORD curDialog;
        DWORD curEntry;
        CON ConFile;
        bool change;
        wxString curFile;
};

#endif // CONEDITORMAIN_H

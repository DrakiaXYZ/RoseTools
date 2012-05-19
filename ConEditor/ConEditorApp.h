/***************************************************************
 * Name:      ConEditorApp.h
 * Purpose:   Defines Application Class
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Created:   2008-06-15
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:
 **************************************************************/

#ifndef CONEDITORAPP_H
#define CONEDITORAPP_H

#include <wx/app.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

class ConEditorApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // CONEDITORAPP_H

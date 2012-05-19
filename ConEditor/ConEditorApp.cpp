/***************************************************************
 * Name:      ConEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Created:   2008-06-15
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ConEditorApp.h"
#include "ConEditorMain.h"

IMPLEMENT_APP(ConEditorApp);

bool ConEditorApp::OnInit()
{
    ConEditorFrame* frame = new ConEditorFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}

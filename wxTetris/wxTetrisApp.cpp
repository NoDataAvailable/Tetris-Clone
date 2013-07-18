/***************************************************************
 * Name:      wxTetrisApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Roberto Bortolussi (robert.bortolussi@gmail.com)
 * Created:   2011-12-23
 * Copyright: Roberto Bortolussi ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wxTetrisApp.h"

//(*AppHeaders
#include "wxTetrisMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxTetrisApp);

bool wxTetrisApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxTetrisFrame* Frame = new wxTetrisFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

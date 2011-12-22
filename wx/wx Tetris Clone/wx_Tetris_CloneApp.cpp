/***************************************************************
 * Name:      wx_Tetris_CloneApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Robert Bortolussi (robot.bobert@gmail.com)
 * Created:   2011-12-22
 * Copyright: Robert Bortolussi ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wx_Tetris_CloneApp.h"

//(*AppHeaders
#include "wx_Tetris_CloneMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wx_Tetris_CloneApp);

bool wx_Tetris_CloneApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wx_Tetris_CloneFrame* Frame = new wx_Tetris_CloneFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

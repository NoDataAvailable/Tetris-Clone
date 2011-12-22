/***************************************************************
 * Name:      wx_Tetris_CloneMain.h
 * Purpose:   Defines Application Frame
 * Author:    Robert Bortolussi (robot.bobert@gmail.com)
 * Created:   2011-12-22
 * Copyright: Robert Bortolussi ()
 * License:
 **************************************************************/

#ifndef WX_TETRIS_CLONEMAIN_H
#define WX_TETRIS_CLONEMAIN_H

//(*Headers(wx_Tetris_CloneFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class wx_Tetris_CloneFrame: public wxFrame
{
    public:

        wx_Tetris_CloneFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wx_Tetris_CloneFrame();

    private:

        //(*Handlers(wx_Tetris_CloneFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(wx_Tetris_CloneFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wx_Tetris_CloneFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WX_TETRIS_CLONEMAIN_H

/***************************************************************
 * Name:      wxTetrisMain.h
 * Purpose:   Defines Application Frame
 * Author:    Roberto Bortolussi (robert.bortolussi@gmail.com)
 * Created:   2011-12-23
 * Copyright: Roberto Bortolussi ()
 * License:
 **************************************************************/

#ifndef WXTETRISMAIN_H
#define WXTETRISMAIN_H

//(*Headers(wxTetrisFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
//*)

class wxTetrisFrame: public wxFrame
{
    public:

        wxTetrisFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxTetrisFrame();

    private:

        //(*Handlers(wxTetrisFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxTetrisFrame)
        static const long ID_STATICBITMAP1;
        static const long ID_STATICBITMAP2;
        static const long ID_STATICBITMAP3;
        static const long ID_STATICBITMAP4;
        static const long ID_STATICBITMAP5;
        static const long ID_STATICTEXT1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wxTetrisFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxStaticBitmap* StaticBitmap5;
        wxStaticText* StaticText1;
        wxStaticBitmap* StaticBitmap3;
        wxStaticBitmap* StaticBitmap1;
        wxStaticBitmap* StaticBitmap4;
        wxStaticBitmap* StaticBitmap2;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXTETRISMAIN_H

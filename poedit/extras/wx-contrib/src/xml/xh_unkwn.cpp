/////////////////////////////////////////////////////////////////////////////
// Name:        xh_unkwn.cpp
// Purpose:     XML resource for unknown widget
// Author:      Vaclav Slavik
// Created:     2000/09/09
// RCS-ID:      $Id$
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifdef __GNUG__
#pragma implementation "xh_unkwn.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/xml/xh_unkwn.h"
#include "wx/window.h"
#include "wx/log.h"


wxUnknownWidgetXmlHandler::wxUnknownWidgetXmlHandler() 
: wxXmlResourceHandler() 
{
    AddWindowStyles();
}

wxObject *wxUnknownWidgetXmlHandler::DoCreateResource()
{ 
    long id = GetLong(wxT("id"), -1);
    wxString name = GetParamValue(wxT("name"));
    
    wxWindow *wnd = NULL;
    
    if (id != -1)
        wnd = m_parentAsWindow->FindWindow(id);
    if (wnd == NULL && !name.IsEmpty())
        wnd = m_parentAsWindow->FindWindow(name);
    printf("name '%s' win %i\n", name.c_str(), wnd);
        
    if (wnd == NULL)
        wxLogError(wxT("Cannot find specified window for class 'unknown' (id=%li, name='%s')."), id, name.mb_str());
    else
    {
        if (wnd->GetParent() != m_parentAsWindow)
            wnd->Reparent(m_parentAsWindow);
        SetupWindow(wnd);
    }

    return wnd;
}

bool wxUnknownWidgetXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("unknown"));
}

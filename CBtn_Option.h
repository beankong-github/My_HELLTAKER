#pragma once
#include "CBtnUI.h"

class CUI_Dialog;

class CBtn_Option :
    public CBtnUI
{
private:
    CUI_Dialog* m_pOwnerDialog;
    UINT        m_iMyPage;

    CTexture*   m_pUnSelectImg;
    CTexture*   m_pSelectImg;

    wstring     m_wstring;
    bool        m_bAnswer;
    bool        m_bSelected;
public:
    void SetOwnerDialog(CUI_Dialog* _pDialog) 
    {
        m_pOwnerDialog = _pDialog;
    }
    void SetPage(UINT _idx) { m_iMyPage = _idx; }
    void SetAnswer() { m_bAnswer = true; }
    void Select() { m_bSelected = true; }
    void Unselect() { m_bSelected = false; }
    void SetText(wstring _text) { m_wstring = _text; }
    
    UINT GetPage() { return m_iMyPage; }
    bool IsSelected() { return m_bSelected; }

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CBtn_Option();
    virtual ~CBtn_Option();
};


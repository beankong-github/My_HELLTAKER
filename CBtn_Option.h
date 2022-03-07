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
    bool        m_bHighLighted;
public:
    void SetOwnerDialog(CUI_Dialog* _pDialog) 
    {
        m_pOwnerDialog = _pDialog;
    }
    void SetPage(UINT _idx) { m_iMyPage = _idx; }
    void SetAnswer() { m_bAnswer = true; }
    void Highlight() {m_bHighLighted = true; }
    void Unhighlight() { m_bHighLighted = false; }
    void SetText(wstring _text) { m_wstring = _text; }
    
    UINT GetPage() { return m_iMyPage; }
    bool IsHighlighted() { return m_bHighLighted; }
    bool IsAnswer() { return m_bAnswer; }

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CBtn_Option();
    virtual ~CBtn_Option();
};


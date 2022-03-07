#pragma once
#include "CObj.h"
#include "CUI.h"

struct Dialog_Page
{   
    /* Dialog Info */
    CTexture* pPortrait;
    CTexture* pBGTex;

    wstring wstrName;
    wstring wstrText;

    /* Button Info */
    wstring wstrOptionOneText;
    bool    bOptionOneIsAnswer;
    
    wstring wstrOptionTwoText;
    bool    bOptionTwoIsAnswer;
};

class CBtn_Option;

class CUI_Dialog :
    public CUI
{
private:
    CStage*     m_pCurStage;
    wstring     m_wstrID;
    UINT        m_iSize;
    UINT        m_iCurPage;

    CTexture* m_pDialogBox;
    bool      m_bBGFlow;
    
    CBtn_Option* m_pFirstOption;
    CBtn_Option* m_pSecondOption;

    //CAnimation* m_pBooper;

    vector<Dialog_Page*> m_pDialogs;

    CSound* m_pButtonConirm;
    CSound* m_pButtonHighLight;
    CSound* m_pNextPage;


    /* Position Info*/
    Vec m_vBGPos;
    Vec m_vPortaritPos;
    Vec m_vBooperPos;
    Vec m_vOptionOnePos;
    Vec m_vOptionTwoPos;

public:
    wstring GetID() { return m_wstrID; }
    UINT GetCurPage() { return m_iCurPage; }
    CBtn_Option* GetFirstOption() { return m_pFirstOption; }
    CBtn_Option* GetSecondOption() { return m_pSecondOption; }

    void SetCurPage(UINT _inum) { m_iCurPage = _inum; }
    void SetCurStage(CStage* _pstage) { m_pCurStage = _pstage; }

public:
    void Load();

public:
    void FirstOptionSelected();
    void SecondOptionSelected();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CUI_Dialog(wstring _ID);
    virtual ~CUI_Dialog();
};


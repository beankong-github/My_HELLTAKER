#pragma once
#include "CComponent.h"

class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_pCurAnim;
    bool                        m_bRepeat;
 
public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void        CreateAnimation(const wstring& _strAnimName,CTexture* _pAtlasTex, Vec _vLeftTop, Vec _vSize, Vec _vOffset, float _fxDistance, float _fDuration, UINT _iFrmCount);
    void        PlayAnimation(const wstring& _strName, bool _bRepeat = true);
    void        LoadAnimation(const wstring& _strRelativePath);
    CAnimation* FindAnimation(const wstring& _strName);

public:
    CAnimator();
    ~CAnimator();
};


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
    void        InitAnimator() { m_pCurAnim = nullptr; }

    void        CreateAnimation(const wstring& _strAnimName, const wstring& _strRelativePath, float _fDuration, UINT _iFrmCount);
    void        PlayAnimation(const wstring& _strName, bool _bRepeat = true);
    void        LoadAnimation(const wstring& _strRelativePath);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* GetCurAnimation() { return m_pCurAnim; }

public:
    CAnimator();
    ~CAnimator();
};


#pragma once
#include "CObstacle.h"

class CTexture;
class CStage_Puzzle;

class CLockBox :
    public CObstacle
{
private:
    CStage_Puzzle*      m_pCurStage;
    vector<CTexture*>   m_vecTextures;
    CTexture*           m_pCurTex;

    Vec                 m_vOriginalPos;
    float               m_fEffectTime;
    float               m_fAddTime;

public:
    void Update();
    void Render(HDC _dc);

private:
    void Shake();

public:
    CLockBox(CTile* _pTile);
    virtual ~CLockBox();
};
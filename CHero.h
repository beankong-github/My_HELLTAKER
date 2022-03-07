#pragma once
#include "CObj.h"

class CTile;

enum class EPLAYER_STATE
{
    IDLE,
    MOVE,
    KICK,
    DAMAGED,
    SUCCESS,
    DEAD
};

class CHero :
    public CObj
{
private:
    CStage_Puzzle*  m_pCurStage;
    CTexture*       m_pRedTex;

    EPLAYER_STATE   m_eState;

    CTile*          m_pCurTile;
    CTile*          m_pNextTile;
   
    EDIRECTION      m_eMovDir;
    float           m_fSpeed;

    bool            m_bKey;

    CSound*         m_pMoveSound;
    CSound*         m_pDeadSound;
    CSound*         m_pDamageSound[2];
    CSound*         m_pKeySound;
    CSound*         m_pSuccessSound;
    CSound*         m_pUnlockSound;
    CSound*         m_pBoxKickSound;

    float           m_fSuccessEffectTiming;
    float           m_fAddTime;

    bool m_iSoundPingPong;

public:
    void SetState(EPLAYER_STATE _eState)    { m_eState = _eState; }
    void SetSpeed(float _fSpeed)            { m_fSpeed = _fSpeed; }
    void SetCurTile(CTile* _pTile)          { m_pCurTile = _pTile; }

    CTile* GetCurTile() { return m_pCurTile; }

public:
    void Update();
    void Render(HDC _dc);

    void TryMove();
    void Move();
    void Kick();
    void Dead();
    void StageClear();
    void GetDamaged(int _damage, Vec _pos);

private:
    void KeyCheck();
    void CountDown(int _num = 1);

public:
    CHero();
    virtual ~CHero();
};


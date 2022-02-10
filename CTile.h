#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

public:
    Vec GetCenterPos()
    {
        return GetPos() + Vec{ TILE_SIZE/2, TILE_SIZE/2 };
    };

public:
    CTile();
    virtual ~CTile();
};


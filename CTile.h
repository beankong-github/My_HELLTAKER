#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
private:
public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

public:
    CTile();
    virtual ~CTile();
};


#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
private:
    
public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CMonster();
    ~CMonster();
};


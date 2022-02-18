#pragma once
#include "CObj.h"
class CNPC :
    public CObj
{
public:
	void Update();
	void Render(HDC _dc);

public:
	CNPC(const wstring& _strName);
	virtual ~CNPC();

};


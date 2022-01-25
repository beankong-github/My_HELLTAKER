#pragma once
class CCamera
{
	SINGLE(CCamera)

private:
	Vec m_vLookAt;
	Vec m_vDiff;		// 해상도 중앙 지점과 카메라가 보고있는 지점 차이

public:
	Vec GetDiff() { return m_vDiff; }

public:
	void Init();
	void Update();
};


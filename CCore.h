#pragma once
class CCore
{
private:
	// heap 메모리 영역 싱글톤
	// static CCore* m_pCore;

public:
	// 데이터 영역 싱글톤
	static CCore* GetInstance()
	{
		static CCore c;			// 최초 1회만 실행된다.
		return &c;
	}
	
	// heap 메모리 영역 싱글톤
	//static CCore* GetInstance()
	//{
	//	//static CCore c;			// 최초 1회만 실행된다.
	//	//return &c;

	//	if(nullptr == m_pCore)
	//	{
	//		m_pCore = new CCore;
	//	}
	//	return m_pCore;
	//}

	//static void Destroy()
	//{
	//	if (nullptr != m_pCore)
	//	{
	//		delete m_pCore;
	//		m_pCore = nullptr;
	//	}
	//}

private:
	CCore();
	~CCore();
};


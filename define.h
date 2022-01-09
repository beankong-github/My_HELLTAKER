#pragma once

#define SINGLE(type)	public:							\
							static type* GetInst()		\
							{							\
								static type mgr;		\
								return &mgr;			\
							}							\
						private:						\
							type();						\
							~type();			

#define DS	CTimeMgr::GetInst()->GetDS();

#define IS_KEY_PRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_TAP(key) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_AWAY(key) KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_NONE(key) KEY_STATE::NONE == CKeyMgr::GetInst()->GetKeyState(key)

enum class ESTAGE_TYPE
{
	START,
	PLAY_01,
	PLAY_02,
	EXIT,

	STAGE_END
};
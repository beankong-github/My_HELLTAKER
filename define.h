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

enum class EOBJ_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,

	END = 32
};

enum class EEVENT_TYPE
{
	CREATE_OBJ,		// lParam : Object Adress		wParam : Object Type
	DELETE_OBJ,		// lParam : Object Adress
	STAGE_CHANGE,	// lParam : Next Stage Enum
	END
};

enum class ECOM_TYPE
{
	COLLIDER,
	ANIMATOR,
	FSM,
	END
};
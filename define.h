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

#define DS	CTimeMgr::GetInst()->GetDS()

#define IS_KEY_PRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_TAP(key) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_AWAY(key) KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key)
#define IS_KEY_NONE(key) KEY_STATE::NONE == CKeyMgr::GetInst()->GetKeyState(key)

#define PI 3.14159289f

#define MAX_LAYER 32

#define TILE_SIZE 100

#define CLONE(type) virtual type* Clone() override { return new type(*this);}

enum class ESTAGE_TYPE
{
	TOOL,
	START,
	PUZZLE,
	END,

	STAGE_END
};

enum class ECHAPTER
{
	NONE,
	CHAP_1,		// pandemonica
	CHAP_2,		// modeus
	CHAP_3,		// cerberus
	CHAP_4,		// malina
	CHAP_5,     // zdrada
	CHAP_6,		// azazel
	CHAP_7,		// justice
	CHAP_8,		// lucy
	CHAP_9,		// door
	//CHAP_10,		// judgement
	END
};

enum class EOBJ_TYPE
{
	DEFAULT,
	BG,
	TILEMAP,
	TILE,
	NPC,
	OBSTACLE,
	ITEM,
	PLAYER,
	EFFECT,
	UI,
	DIALOG,
	TRANSITION,
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

enum class EDIRECTION
{
	NONE,
	HORIZIONTAL,
	VERTICAL,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	END
};
#pragma once
#include "Cstage.h"

enum Chapter
{
    NONE,
    CHAP_01,		// pandemonica
    CHAP_02,		// modeus
    CHAP_03,		// cerberus
    CHAP_04,		// malina
    CHAP_05,        // zdrada
    CHAP_06,		// azazel
    CHAP_07,		// justice
    CHAP_08,		// lucy
    CHAP_09,		// door
    CHAP_10,		// judgement
    END
};


class CStage_Puzzle :
    public CStage
{
private:
    Chapter     m_eChapter;
    CTexture*   m_pBGTex;

    Vec         m_vTileTable;
    UINT        m_iMoveCount;


public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;

    void Enter() override;
    void Exit() override;

public:
    CStage_Puzzle();
    ~CStage_Puzzle() override;
};


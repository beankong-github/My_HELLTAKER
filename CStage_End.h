#pragma once
#include "Cstage.h"

class CUI_Dialog;
class CSound;

class CStage_End :
    public CStage
{
    private:
        CUI_Dialog* m_pDailog;
        CSound* m_pEndBGM;

    public:
        void Init() override;
        void Update() override;
        void Render(HDC _dc) override;

        void Enter() override;
        void Exit() override;

    public:
        void DialogTermination() override;


    public:
        CStage_End();
        ~CStage_End();

};


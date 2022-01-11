#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    // 텍스처의 가로 세로 해상도(픽셀 개수)
    UINT m_iWidth;
    UINT m_iHeight;

    HBITMAP m_hBit;
    HDC     m_hDC;

public:
    HDC GetDC() { return m_hDC; }

private:
    int Load(const wstring& _strFullPath) override;
    
public:
    CTexture();
    ~CTexture();

};


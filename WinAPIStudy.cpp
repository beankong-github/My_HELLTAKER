// WinAPIStudy.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPIStudy.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;            // 현재 인스턴스입니다. (프로그램 시작 주소)
HWND g_hWnd;                  // Main Window Handle

                                                                // 이 코드 모듈에 포함된 함수의 전방 선언:
ATOM                MyRegisterClass(HINSTANCE hInstance);       // 창의 속성 설정하고(윈도우 설정하는 구조체 설정) 해당 창의 클래스를  메모리에 등록한다 (ATOM - Access to Memory)
BOOL                InitInstance(HINSTANCE, int);               // 창 초기화 및 창 보이기
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);        // 창의 메세지 처리 (CALLBACK - _stdcall // 함수a   호출 규약)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);          // 

int APIENTRY wWinMain( HINSTANCE hInstance,                     // 프로그램 시작 주소
                       HINSTANCE hPrevInstance,                 // 이전 시작 주소 (현재는 가상 메모리 시스템으로 한 프로그램이 메모리에 단독으로 들어간 것처럼 사용되기 때문에 필요 x)
                       LPWSTR    lpCmdLine,                     // 프로그램 실행 cmd 명령어, 이것을 이용해 한 프로그램에 여러 실행 버전을 만들 수 있음 (예를 들어 개발자 모드)
                       int       nCmdShow)                      // 윈도우가 처음 실행될 때 어떤 화면의 형태를 가질지 (ex 최대화 상태, 최소화 상태) 
{

    // TODO: 여기에 코드를 입력합니다.

    // 생성시킬 윈도우 설정
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        // 초기화가 안되면 메인에서 탈출
        return FALSE;
    }


    // 단축키 정보들
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPISTUDY));     // Accle Table 정보에 저장된 단축키 정보를 가져옴

    // 메세지 구조체
    MSG msg = {};

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))                      // 메세지 큐에 쌓여 있는 메세지를 msg에 하나씩 가져온다, nullptr을 전달할 경우 스레드에 속하는 모든 창에 대한 메세지를 가져온다, 나머지 두 정수는 메세지 필터링 용이다.
    {

        // 메세지 처리
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  // 액셀러레이터(조합키 첫번째 요소)가 입력되었을 경우 TranslateMessage, DispatchMessage 함수가 실행되지 못하도록 막아 버리며 다음번의 WM_COMMAND메시지가 처리되도록 해 준다. 물론 액셀러레이터 입력이 아니면 FALSE를 리턴하여 다른 메시지들은 정상적으로 처리되도록 해 준다.
        {
            TranslateMessage(&msg);                              // 키 입력을 문자로 전환하여 메세지 큐에 저장한다
            DispatchMessage(&msg);                               // 창 프로시저에 메세지를 처리하도록 전달. 일반적으로 GetMessage 함수에 의해 검색된 메세지를 발송하는데 사용
        }
    }

    return (int) msg.wParam;                                     // 메세지에 대한 부가 정보
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;       // 윈도우 설정값들을 모아놓은 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;      // 해당 윈도우 이벤트 처리 함수 주소
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPISTUDY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"MyWin";     // 윈도우 설정값의 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우 생성
   // 윈도우 ==> 커널 오브젝트
   // 생성 후 주소대신 윈도우의 핸들(ID) 를 반환 (생성 실패 시 nullptr 반환)
   g_hWnd = CreateWindowW(L"MyWin", L"MyWindow", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   // 윈도우 보이기
   ShowWindow(g_hWnd, TRUE);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT,         WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션            메뉴를 처리합니다  .
//  WM_PAINT    - 주 창을 그립니다         .
//  WM_DESTROY  - 종료 메시지를           게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
          
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);    // WM_QUIT 발생
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:  // 윈도우에 무언가를 그리는 메세지. 최초로 창을 띄울때, 최대화 또는 최소화 할 때 등은 자동으로 WM_PAINT 메세지가 발생한다.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // dc(device context) : rendering 관련된 데이터 집합 (ex: pen - 그리기, brush - 채우기, bitmap - window에서 상단바를 제외한 배경)

            // 빨간색 브러쉬 생성
            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // hdc의 브러쉬를 redBrush로 교체하고 기존의 브러쉬를 prevBrush에 저장
            HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, redBrush);
            Rectangle(hdc, 100, 100, 200, 200);
          
            // hdc의 브러쉬를 blueBrush로 교체
            SelectObject(hdc, blueBrush);
            Ellipse(hdc, 100, 100, 200, 200);

            // 기존 브러쉬로 되돌려놓기
            SelectObject(hdc, prevBrush);
            
            // 사용이 끝난 브러쉬 삭제하기
            DeleteObject(redBrush);
            DeleteObject(blueBrush);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

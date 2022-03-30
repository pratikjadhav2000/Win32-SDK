#include<Windows.h>
//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc; 
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//create the window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("PJ:MyFirstWindow"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop(windows) //event loop(linux) //run loop (mac os) // game loop(rendering technology)
	while (GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return ((int)msg.wParam);



}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations

	HMODULE hLib=NULL;
	typedef int (*PMAKECUBEFUNCTION)(int);
	PMAKECUBEFUNCTION pMakeCube = NULL;

	int num1,num2;
	TCHAR str[255];	

	//code
	switch (iMsg)
	{

	case WM_CREATE:

	hLib = LoadLibrary(TEXT("MyMath.dll"));

	if( hLib == NULL )
	{
		MessageBox(hwnd, TEXT("LoadLibrary Failed"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	pMakeCube = (PMAKECUBEFUNCTION)GetProcAddress(hLib, "MakeCube" );

	if( pMakeCube == NULL )
	{
		MessageBox(hwnd, TEXT("PMAKECUBEFUNCTION address cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	num1 = 15;
	num2 = pMakeCube(num1);

		wsprintf(str,TEXT("Cube of %d is %d "),num1,num2);
		MessageBox(hwnd, str, TEXT("Cube"), MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

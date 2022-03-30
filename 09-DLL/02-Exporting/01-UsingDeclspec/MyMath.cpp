#include<windows.h>

BOOL WINAPI DllMain(HINSTANCE hdll, DWORD dwreason, LPVOID lpreserved)
{
	//code

	switch(dwreason){

	case DLL_PROCESS_ATTACH:
	break;

	case DLL_THREAD_ATTACH:
	break;

	case DLL_THREAD_DETACH:
	break;

	case DLL_PROCESS_DETACH:
	break;

	default:
	break;

	};

	return TRUE;

}

extern "C" __declspec(dllexport) int MakeCube(int num)
{
	//code
	int cube = num * num * num;

	return cube;
}

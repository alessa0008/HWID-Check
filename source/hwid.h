#define WIN32_LEAN_AND_MEAN
//===================
#include <fstream>
//===================
#include <iostream>
//===================
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <stdexcept>
//===================
#include <windows.h>
#include "wininet.h"
//===================
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "winmm.lib")

//================================================================================================
UCHAR
szFileSys[255],
szVolNameBuff[255];

DWORD
dwMFL,
dwSysFlags,
dwSerial;

#define My_HWID (000000000000) //HWID

VOID CheckValidHardwareID()
{

	GetVolumeInformation("C:\\", (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);
	if (dwSerial == My_HWID) // Lakukan perbandingan dengan hwid yang baru diambil dengan My_HWID
	{
		MessageBox(0, "TEXT", " = TEXT = ", MB_OK | MB_ICONINFORMATION);
		// Serial valid
	}
	else // Jika serial tersebut tidak cocok
	{
		MessageBox(0, "TEXT", "TEXT", MB_OK | MB_ICONERROR);
		ExitProcess(1); // Force Exit
						// Invalid Serial
	}

}
//================================================================================================
int ProtectOnline(char *url)
{
	char output[16];
	HINTERNET hInternet; HINTERNET hFile; DWORD ReadSize; BOOL bResult;
	hInternet = InternetOpen("Some USER-AGENT", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	hFile = InternetOpenUrl(hInternet, url, NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	ReadSize = 15; Sleep(500); bResult = InternetReadFile(hFile, output, 15, &ReadSize); output[ReadSize] = '\0';
	if (strcmp("ACTIVE", output) == 0) 
	{
		MessageBox(0, "TEXT", " = TEXT = ", MB_ICONINFORMATION | MB_OK);	//Notice VALID
		GetCurrentProcess();
	}
	else
	{
		MessageBox(0, ".-=*TEXT*=-.", "END", MB_OK + MB_ICONSTOP); 			//Notice INVALID
		Sleep(10);
		ExitProcess(0);
	}
	return 0;
}
void __stdcall RemoteControlDLL()
{
	ProtectOnline("https://pastebin.com/");
}

int _stdcall AktifRemoteControlDLL(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RemoteControlDLL, 0, 0, 0);
	return TRUE;
}

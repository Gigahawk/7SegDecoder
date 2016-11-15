#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "SevenSeg.h"

void killDAQ();

int main(){
	setupDAQ(4);
	while (!digitalRead(0)){
		writeNumber(300);
		Sleep(1000);
		writeNumber(12345);
		Sleep(1000);
		writeNumber(5);
		Sleep(1000);
		writeNumber(123456789);
		Sleep(1000);
	}

	system("PAUSE");

	/* 
   * Horribly inelegant, but this seems to be slightly faster
	 * than hitting the "Quit" button and also means the simulator
	 * automatically quits when I'm done reading the debug output
   */
	killDAQ();
	return 0;
}

// Written by the wonderful people on StackExchange
// http://stackoverflow.com/questions/7956519/how-to-kill-processes-by-name-win32-api
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>
void killDAQ()
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof (pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, "runsim.exe") == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

DWORD GetPid(char* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 ProcEntry;

	ProcEntry.dwSize = sizeof(ProcEntry);

	do
	{
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			DWORD dwPID = ProcEntry.th32ProcessID;

			CloseHandle(hPID);

			return dwPID;
		}
	} while (Process32Next(hPID, &ProcEntry));
}

int main()
{
	//Setup console window
	SetConsoleTitle("injector"); //injektoriaplikaation nimi

	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 760, 440, 400, 200, TRUE);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	//get dllnimi
	string dllname;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //v‰rin vaihto konsolissa
	cout << "Anna Dll nimi: \n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> dllname; //otetaan sis‰‰n dll tiedoston nimi

	string checkfor = ".dll";

	if (!(dllname.find(checkfor) != std::string::npos)) //check for .dll ending
	{
		dllname += ".dll"; //jos tiedostossa ei ole .dll p‰‰tett‰ se lis‰t‰‰n
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Injektoidaan ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << dllname;

	LPCSTR DLL_NAME = dllname.c_str();

	//inject as usual
	DWORD dwProcess;
	char myDLL[MAX_PATH];
	GetFullPathName(DLL_NAME, MAX_PATH, myDLL, 0);

	dwProcess = GetPid((char*)"csgo.exe"); //prosessin nimi mihin ollaan injektoimassa

	HANDLE Process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);
	LPVOID allocatedMem = VirtualAllocEx(Process, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(Process, allocatedMem, myDLL, sizeof(myDLL), NULL);
	CreateRemoteThread(Process, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

	CloseHandle(Process);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "\n Have Fun!";

	auto start3 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(2s);
	auto end3 = std::chrono::high_resolution_clock::now();

	return 0;
}
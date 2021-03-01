#include <Windows.h>
#include <iostream>
#include "Setti.h"
#include "Offsets.h"
#include "Janis.h"
#include "Vector3.h"
#include "Vec3.h"

DWORD WINAPI OnDllAttach(PVOID base)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("GH_Aimbot_Tutorial - Debug");
#endif

	world JanisGameWorld;
	entity JanisLocalPlayer;

	//clientmodule //liittyy rekoon
	uintptr_t clientModule = (uintptr_t)GetModuleHandle("client.dll"); //liittyy rekoon
	//enginemodule //liittyy rekoon
	uintptr_t engineModule = (uintptr_t)GetModuleHandle("engine.dll"); //liittyy rekoon
	//localplayer ptr //liittyy rekoon
	uintptr_t localPlayer = *(uintptr_t*)(clientModule + hazedumper::signatures::dwLocalPlayer); //liittyy rekoon
	//viewangles ptr //liittyy rekoon
	Vec3* viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles); //liittyy rekoon
	//shotsfired ptr	//liittyy rekoon
	int* iShotsFired = (int*)(localPlayer + hazedumper::netvars::m_iShotsFired);	//liittyy rekoon returns the amount of shots fired after you started klicking to when you let go
	//aimpunch ptr	//liittyy rekoon
	Vec3* aimPunchAngle = (Vec3*)(localPlayer + hazedumper::netvars::m_aimPunchAngle);	//liittyy rekoon kertoo missä tähtäin on
	
	Vec3 oPunch{ 0,0,0 };		//liittyy rekoon

	while (!(GetAsyncKeyState(VK_END) & 0x8000))	//tämä looppi pyörittää settejä ja sulkee setit kun painaa END nappia
	{
		/*
		if (GetAsyncKeyState(VK_RBUTTON)) //painamalla hiiren oikeeta norecoil triggeröityy päälle
		{
			Vec3 punchAngle = *aimPunchAngle * 2; // * 2
			if (*iShotsFired > 1) {
				//laske rekyyli
				Vec3 newAngle = *viewAngles + oPunch - punchAngle;
				//normalisoi
				newAngle.Normalize();
				//aseta
				*viewAngles = newAngle;
			}

			//korjaus
			oPunch = punchAngle;

		}
		*/

		if (GetAsyncKeyState(VK_MENU)) //painamalla alt aimbot triggeröityy päälle
		{

			Run();
			Sleep(1);

		}

		Vec3 punchAngle = *aimPunchAngle * 2; // * 2 liittyy rekoon
		if (*iShotsFired > 1) {
			//laske rekyyli
			Vec3 newAngle = *viewAngles + oPunch - punchAngle;
			//normalisoi
			newAngle.Normalize();
			//aseta
			*viewAngles = newAngle;
		}

		//korjaus
		oPunch = punchAngle;
	

		if (GetAsyncKeyState(VK_SPACE)) //punihopi lähtee rullaa ku painaa spacee
		{
			JanisLocalPlayer.EntityPtr = *(DWORD*)(JanisGameWorld.GameModule + hazedumper::signatures::dwLocalPlayer);

			if (JanisLocalPlayer.EntityPtr != NULL)
			{
				JanisLocalPlayer.health = *(int*)(JanisLocalPlayer.EntityPtr + hazedumper::netvars::m_iHealth);
				JanisLocalPlayer.flags = *(int*)(JanisLocalPlayer.EntityPtr + hazedumper::netvars::m_fFlags);

				if (JanisLocalPlayer.health > 0 && JanisLocalPlayer.flags == 257) //jos pelaaja on hengissä ja jalat osuu maahan, pakota hyppy
				{
					JanisLocalPlayer.ForceJump(JanisGameWorld.GameModule);
				}
			}
		}

	}
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
}

VOID WINAPI OnDllDetach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

		OnDllDetach();
	}
	return TRUE;
}
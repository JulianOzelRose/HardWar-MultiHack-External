/*
	HardWar-MultiHack-External.cpp
	by Julian Rose
	7-26-2022
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <TlHelp32.h>
#include "HackProcess.h"

int main()
{
	// Memory offsets
	std::vector<unsigned int> cashOffset = {0x03C};
	std::vector<unsigned int> playerStatusOffset = {0x02C};
	std::vector<unsigned int> shieldOffsets = {0x030, 0x294};
	std::vector<unsigned int> thrustOffsets = {0x030, 0x438};
	std::vector<unsigned int> stallWarningLvlOffsets = {0x030, 0x390};
	std::vector<unsigned int> targetStructureDmgOffsets = {0x030, 0x1F0, 0x29C};
	std::vector<unsigned int> engineDmgOffsets = {0x030, 0x298};
	std::vector<unsigned int> structureDmgOffsets = {0x030, 0x29C};
	std::vector<unsigned int> cpuDmgOffsets = {0x030, 0x2A0};
	std::vector<unsigned int> powerDmgOffsets = {0x030, 0x2A4};
	std::vector<unsigned int> weaponsDmgOffsets = {0x030, 0x2A8};
	std::vector<unsigned int> targetStatusOffsets = {0x030, 0x1D4};
	std::vector<unsigned int> targetTypeOffsets = {0x030, 0x1F0, 0x0};
	std::vector<unsigned int> mothStatusOffsets = {0x030, 0x1D4};

	// Game constants
	const int MAX_CASH = 999999999;
	const int IN_MOTH = 1;
	const DWORD IN_HANGAR = 0x7FFF;
	const DWORD MAX_SHIELDS = 0x4000;
	const DWORD MAX_DMG = 0x4000;
	const DWORD MAX_THRUST = 0x4000;
	const DWORD MAX_HEALTH = 0x0;
	const DWORD MIN_THRUST = 0x0;
	const DWORD NO_STALL = 0x0;
	const DWORD TYPE_MOTH = 0x3FFF;
	const DWORD TYPE_BLDG = 0x3E8;

	// Open process
	HWND hwWindow = FindWindow(0, _T("Hardwar"));
	DWORD processId = GetProcessId(L"HardwarW.exe");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	uintptr_t moduleBase = GetModuleBaseAddress(processId, L"HardwarW.exe");
	uintptr_t playerBase = 0x11D9AC;
	uintptr_t dynamicPtrBaseAddress = moduleBase + playerBase;

	// Get memory addresses
	uintptr_t thrustAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, thrustOffsets);
	uintptr_t shieldAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, shieldOffsets);
	uintptr_t cashAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, cashOffset);
	uintptr_t stallWarningLvlAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, stallWarningLvlOffsets);
	uintptr_t playerStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerStatusOffset);
	uintptr_t targetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStructureDmgOffsets);
	uintptr_t targetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetTypeOffsets);
	uintptr_t engineDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, engineDmgOffsets);
	uintptr_t structureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, structureDmgOffsets);
	uintptr_t cpuDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, cpuDmgOffsets);
	uintptr_t powerDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, powerDmgOffsets);
	uintptr_t weaponsDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, weaponsDmgOffsets);
	uintptr_t targetStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStatusOffsets);
	uintptr_t mothStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, mothStatusOffsets);
	uintptr_t playerAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, {0});

	// Game variables
	DWORD thrust;
	DWORD shields;
	DWORD engineDmg;
	DWORD structureDmg;
	DWORD cpuDmg;
	DWORD powerDmg;
	DWORD weaponsDmg;
	DWORD targetStatus;
	DWORD targetType;
	DWORD targetStructureDmg;
	DWORD stallWarningLvl;
	DWORD mothStatus = 0x0;
	DWORD newThrust = MAX_THRUST * 6;
	BYTE playerStatus = 2;
	int cash;

	// Toggle variables
	bool bSpeedHack = FALSE;
	bool bInstakill = TRUE;
	
	system("color A");
	std::cout << "HardWar-MultiHack" << std::endl;
	
	// Check process
	if (hwWindow)
	{
		std::cout << "Process found! Running..." << std::endl;
	}

	while (1)
	{
		// Re-check process
		hwWindow = FindWindow(0, _T("Hardwar"));
		while (!hwWindow)
		{
			std::cout << "Game process not found..." << std::endl;
			Sleep(2000);
			hwWindow = FindWindow(0, _T("Hardwar"));
			if (hwWindow)
			{
				processId = GetProcessId(L"HardwarW.exe");
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
				moduleBase = GetModuleBaseAddress(processId, L"HardwarW.exe");
				dynamicPtrBaseAddress = moduleBase + playerBase;
				bSpeedHack = FALSE;
				bInstakill = TRUE;
				std::cout << "Process found! Running..." << std::endl;
			}
		}
		
		// Update addresses
		thrustAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, thrustOffsets);
		shieldAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, shieldOffsets);
		cashAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, cashOffset);
		stallWarningLvlAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, stallWarningLvlOffsets);
		playerStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerStatusOffset);
		targetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStructureDmgOffsets);
		targetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetTypeOffsets);
		engineDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, engineDmgOffsets);
		structureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, structureDmgOffsets);
		cpuDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, cpuDmgOffsets);
		powerDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, powerDmgOffsets);
		weaponsDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, weaponsDmgOffsets);
		targetStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStatusOffsets);
		mothStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, mothStatusOffsets);
		playerAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, {0});

		// Update values
		ReadProcessMemory(hProcess, (BYTE*)playerStatusAddress, &playerStatus, sizeof(playerStatus), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)targetStatusAddress, &targetStatus, sizeof(targetStatus), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)mothStatusAddress, &mothStatus, sizeof(mothStatus), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)thrustAddress, &thrust, sizeof(thrust), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)shieldAddress, &shields, sizeof(shields), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)structureDmgAddress, &structureDmg, sizeof(structureDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)engineDmgAddress, &engineDmg, sizeof(engineDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)cpuDmgAddress, &cpuDmg, sizeof(cpuDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)powerDmgAddress, &powerDmg, sizeof(powerDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)weaponsDmgAddress, &weaponsDmg, sizeof(weaponsDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)targetTypeAddress, &targetType, sizeof(targetType), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)targetStructureDmgAddress, &targetStructureDmg, sizeof(targetStructureDmg), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)stallWarningLvlAddress, &stallWarningLvl, sizeof(stallWarningLvl), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)cashAddress, &cash, sizeof(cash), nullptr);

		// Toggle Instakill
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			bInstakill = !bInstakill;

			std::cout << "Instakill: ";

			if (bInstakill)
			{
				std::cout << "ON" << std::endl;
			}

			if (!bInstakill)
			{
				std::cout << "OFF" << std::endl;
			}
		}

		// Toggle SpeedHack
		if (GetAsyncKeyState(VK_END) & 1)
		{
			bSpeedHack = !bSpeedHack;

			std::cout << "Speedhack: ";

			if (bSpeedHack)
			{
				WriteProcessMemory(hProcess, (BYTE*)thrustAddress, &newThrust, sizeof(newThrust), nullptr);
				std::cout << "ON" << std::endl;
			}

			if (!bSpeedHack)
			{
				WriteProcessMemory(hProcess, (BYTE*)thrustAddress, &MIN_THRUST, sizeof(MIN_THRUST), nullptr);
				std::cout << "OFF" << std::endl;
			}
		}
		
		// Invincibility
		if ((shields < MAX_SHIELDS) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)shieldAddress, &MAX_SHIELDS, sizeof(MAX_SHIELDS), nullptr);
			std::cout << "Damage detected - Shields restored to FULL" << std::endl;
		}
		if ((structureDmg > MAX_HEALTH) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)structureDmgAddress, &MAX_HEALTH, sizeof(MAX_HEALTH), nullptr);
			std::cout << "Damage detected - Structure health restored to FULL" << std::endl;
		}
		if ((engineDmg > MAX_HEALTH) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)engineDmgAddress, &MAX_HEALTH, sizeof(MAX_HEALTH), nullptr);
			std::cout << "Damage detected - Engine health restored to FULL" << std::endl;
		}
		if ((cpuDmg > MAX_HEALTH) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)cpuDmgAddress, &MAX_HEALTH, sizeof(MAX_HEALTH), nullptr);
			std::cout << "Damage detected - CPU health restored to FULL" << std::endl;
		}
		if ((powerDmg > MAX_HEALTH) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)powerDmgAddress, &MAX_HEALTH, sizeof(MAX_HEALTH), nullptr);
			std::cout << "Damage detected - Power health restored to FULL" << std::endl;
		}
		if ((weaponsDmg > MAX_HEALTH) && (playerStatus == IN_MOTH))
		{
			WriteProcessMemory(hProcess, (BYTE*)weaponsDmgAddress, &MAX_HEALTH, sizeof(MAX_HEALTH), nullptr);
			std::cout << "Damage detected - Weapons health restored to FULL" << std::endl;
		}

		// Instakill targeted pilot
		if ((bInstakill) && (targetType == TYPE_MOTH) && (targetStructureDmg != MAX_DMG) && (playerStatus == IN_MOTH) && (targetStatus != IN_HANGAR))
		{
			WriteProcessMemory(hProcess, (BYTE*)targetStructureDmgAddress, &MAX_DMG, sizeof(MAX_DMG), nullptr);
			std::cout << "Pilot detected and destroyed" << std::endl;
		}

		// Speedhack
		if ((bSpeedHack) && (mothStatus != IN_HANGAR))
		{
			WriteProcessMemory(hProcess, (BYTE*)thrustAddress, &newThrust, sizeof(newThrust), nullptr);
		}

		// Stall negation
		if ((stallWarningLvl > NO_STALL) && (playerStatus == IN_MOTH) && (mothStatus != IN_HANGAR))
		{
			WriteProcessMemory(hProcess, (BYTE*)stallWarningLvlAddress, &NO_STALL, sizeof(NO_STALL), nullptr);
			std::cout << "Stall detected and averted" << std::endl;
		}

		// Infinite cash
		if ((cash < MAX_CASH) && (playerAddress != NULL))
		{
			WriteProcessMemory(hProcess, (BYTE*)cashAddress, &MAX_CASH, sizeof(MAX_CASH), nullptr);
			std::cout << "Player cash re-maxed" << std::endl;
		}

		Sleep(250);
	}

	return 0;
}
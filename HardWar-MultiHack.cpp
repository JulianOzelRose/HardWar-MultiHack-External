/*
	HardWar-MultiHack
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
	std::vector<unsigned int> cashOffsets = {0x3C};
	std::vector<unsigned int> playerStatusOffsets = {0x58};
	std::vector<unsigned int> shieldOffsets = {0x30, 0x294};
	std::vector<unsigned int> thrustOffsets = {0x30, 0x438};
	std::vector<unsigned int> stallWarningLvlOffsets = {0x30, 0x390};
	std::vector<unsigned int> targetTypeOffsets = {0x30, 0x1EC};
	std::vector<unsigned int> targetStructureDmgOffsets = {0x30, 0x1F0, 0x29C};

	// Game constants
	const DWORD MAX_SHIELDS = 0x4000;
	const DWORD MAX_DMG = 0x4000;
	const DWORD MAX_THRUST = 0x4000;
	const int MAX_CASH = 999999999;

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
	uintptr_t cashAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, cashOffsets);
	uintptr_t stallWarningLvlAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, stallWarningLvlOffsets);
	uintptr_t statusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerStatusOffsets);
	uintptr_t targetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStructureDmgOffsets);
	uintptr_t targetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetTypeOffsets);

	// Game variables
	DWORD newThrust = MAX_THRUST*6;
	DWORD targetStructureDmg;
	DWORD shields;
	BYTE playerStatus = 0;
	BYTE newPlayerStatus = 0;
	int newStallWarningLvl = 0;
	int stallWarningLvl;
	int targetType;
	int cash;

	system("color A");

	if (!hwWindow) {
		std::cout << "HardWar game process not found, please restart hack with HardWar running." << std::endl;
		Sleep(10000);
		exit(0);
	}
	else {
		std::cout << "HardWar-MultiHack running..." << std::endl;
	}

	while (1) {
		// Update target info
		targetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetTypeOffsets);
		targetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, targetStructureDmgOffsets);
		targetType = ReadProcessMemory(hProcess, (BYTE*)targetTypeAddress, &targetType, sizeof(targetType), nullptr);

		// Instakill targeted pilot
		ReadProcessMemory(hProcess, (BYTE*)targetTypeAddress, &targetType, sizeof(targetType), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)targetStructureDmgAddress, &targetStructureDmg, sizeof(targetStructureDmg), nullptr);
		if ((targetType == 1) && (targetStructureDmg != MAX_DMG)) {
			WriteProcessMemory(hProcess, (BYTE*)targetStructureDmgAddress, &MAX_DMG, sizeof(MAX_DMG), nullptr);
			std::cout << "Pilot detected and destroyed" << std::endl;
		}

		// Invincibility
		ReadProcessMemory(hProcess, (BYTE*)shieldAddress, &shields, sizeof(shields), nullptr);
		if (shields < MAX_SHIELDS) {
			WriteProcessMemory(hProcess, (BYTE*)shieldAddress, &MAX_SHIELDS, sizeof(MAX_SHIELDS), nullptr);
			std::cout << "Damage detected - shields restored to FULL" << std::endl;
		}

		// Stall negation
		ReadProcessMemory(hProcess, (BYTE*)stallWarningLvlAddress, &stallWarningLvl, sizeof(stallWarningLvl), nullptr);
		if (stallWarningLvl > 0) {
			WriteProcessMemory(hProcess, (BYTE*)stallWarningLvlAddress, &newStallWarningLvl, sizeof(newStallWarningLvl), nullptr);
			std::cout << "Stall detected and averted" << std::endl;
		}

		// Report player status
		ReadProcessMemory(hProcess, (BYTE*)statusAddress, &newPlayerStatus, sizeof(newPlayerStatus), nullptr);
		if ((newPlayerStatus == 3) && (newPlayerStatus != playerStatus)) {
			std::cout << "Player is now in a moth" << std::endl;
			playerStatus = newPlayerStatus;
		}
		if ((newPlayerStatus == 4) && (newPlayerStatus != playerStatus)) {
			std::cout << "Player is now in a hangar" << std::endl;
			playerStatus = newPlayerStatus;
		}

		// Speedhack
		WriteProcessMemory(hProcess, (BYTE*)thrustAddress, &newThrust, sizeof(newThrust), nullptr);

		// Check if process is still running
		HWND hwWindow = FindWindow(0, _T("Hardwar"));
		if (!hwWindow) {
			std::cout << "HardWar process no longer detected, exiting program..." << std::endl;
			Sleep(10000);
			exit(0);
		}

		// Infinite cash
		ReadProcessMemory(hProcess, (BYTE*)cashAddress, &cash, sizeof(cash), nullptr);
		if (cash < MAX_CASH) {
			WriteProcessMemory(hProcess, (BYTE*)cashAddress, &MAX_CASH, sizeof(MAX_CASH), nullptr);
			std::cout << "Player cash re-maxed" << std::endl;
		}

		Sleep(250);
	}

	return 0;
}
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
	std::vector<unsigned int> playerCashOffsets = {0x3C};
	std::vector<unsigned int> playerStatusOffsets = {0x58};
	std::vector<unsigned int> playerShieldOffsets = {0x30, 0x294};
	std::vector<unsigned int> playerThrustOffsets = {0x30, 0x438};
	std::vector<unsigned int> playerStallWarningLvlOffsets = {0x30, 0x390};
	std::vector<unsigned int> currentTargetTypeOffsets = {0x30, 0x1EC};
	std::vector<unsigned int> currentTargetStructureDmgOffsets = {0x30, 0x1F0, 0x29C};

	// Game constants
	const int MAX_SHIELDS = 16384;
	const int MAX_DMG = 16384;
	const int MAX_THRUST = 99999;
	const int MAX_CASH = 999999999;

	// Open process
	HWND hwWindow = FindWindow(0, _T("Hardwar"));
	DWORD processId = GetProcessId(L"HardwarW.exe");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
	uintptr_t moduleBase = GetModuleBaseAddress(processId, L"HardwarW.exe");
	uintptr_t dynamicPtrBaseAddress = moduleBase + 0x11D9AC;

	// Get memory addresses
	uintptr_t playerThrustAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerThrustOffsets);
	uintptr_t playerShieldAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerShieldOffsets);
	uintptr_t playerCashAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerCashOffsets);
	uintptr_t playerStallWarningLevelAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerStallWarningLvlOffsets);
	uintptr_t playerStatusAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, playerStatusOffsets);
	uintptr_t currentTargetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, currentTargetStructureDmgOffsets);
	uintptr_t currentTargetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, currentTargetTypeOffsets);

	// Game variables
	int newThrust = 150000;
	int stallWarningLvl;
	int newStallWarningLvl = 0;
	int currentTargetStructureDmg;
	int currentTargetType;
	int currentShields;
	int playerCash;
	BYTE playerStatus = 0;
	BYTE newPlayerStatus = 0;

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
		currentTargetTypeAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, currentTargetTypeOffsets);
		currentTargetStructureDmgAddress = FindDmaAddress(hProcess, dynamicPtrBaseAddress, currentTargetStructureDmgOffsets);
		currentTargetType = ReadProcessMemory(hProcess, (BYTE*)currentTargetTypeAddress, &currentTargetType, sizeof(currentTargetType), nullptr);

		// Instakill targeted pilot
		ReadProcessMemory(hProcess, (BYTE*)currentTargetTypeAddress, &currentTargetType, sizeof(currentTargetType), nullptr);
		ReadProcessMemory(hProcess, (BYTE*)currentTargetStructureDmgAddress, &currentTargetStructureDmg, sizeof(currentTargetStructureDmg), nullptr);
		if ((currentTargetType == 1) && (currentTargetStructureDmg != MAX_DMG)) {
			WriteProcessMemory(hProcess, (BYTE*)currentTargetStructureDmgAddress, &MAX_DMG, sizeof(MAX_DMG), nullptr);
			std::cout << "Pilot detected and destroyed" << std::endl;
		}

		// Invincibility
		ReadProcessMemory(hProcess, (BYTE*)playerShieldAddress, &currentShields, sizeof(currentShields), nullptr);
		if (currentShields < MAX_SHIELDS) {
			WriteProcessMemory(hProcess, (BYTE*)playerShieldAddress, &MAX_SHIELDS, sizeof(MAX_SHIELDS), nullptr);
			std::cout << "Damage detected - shields restored to FULL" << std::endl;
		}

		// Stall negation
		ReadProcessMemory(hProcess, (BYTE*)playerStallWarningLevelAddress, &stallWarningLvl, sizeof(stallWarningLvl), nullptr);
		if (stallWarningLvl > 0) {
			WriteProcessMemory(hProcess, (BYTE*)playerStallWarningLevelAddress, &newStallWarningLvl, sizeof(newStallWarningLvl), nullptr);
			std::cout << "Stall detected and averted" << std::endl;
		}

		// Report player status
		ReadProcessMemory(hProcess, (BYTE*)playerStatusAddress, &newPlayerStatus, sizeof(newPlayerStatus), nullptr);
		if ((newPlayerStatus == 3) && (newPlayerStatus != playerStatus)) {
			std::cout << "Player is now in a moth" << std::endl;
			playerStatus = newPlayerStatus;
		}
		if ((newPlayerStatus == 4) && (newPlayerStatus != playerStatus)) {
			std::cout << "Player is now in a hangar" << std::endl;
			playerStatus = newPlayerStatus;
		}

		// Speedhack
		WriteProcessMemory(hProcess, (BYTE*)playerThrustAddress, &newThrust, sizeof(newThrust), nullptr);

		// Check if process is still running
		HWND hwWindow = FindWindow(0, _T("Hardwar"));
		if (!hwWindow) {
			std::cout << "HardWar process no longer detected, exiting program..." << std::endl;
			Sleep(10000);
			exit(0);
		}

		// Infinite cash
		ReadProcessMemory(hProcess, (BYTE*)playerCashAddress, &playerCash, sizeof(playerCash), nullptr);
		if (playerCash < MAX_CASH) {
			WriteProcessMemory(hProcess, (BYTE*)playerCashAddress, &MAX_CASH, sizeof(MAX_CASH), nullptr);
			std::cout << "Player cash re-maxed" << std::endl;
		}

		Sleep(250);
	}

	return 0;
}
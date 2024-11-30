#include "pch.h"
#pragma warning(disable : 4996)

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
#define ReplaceTex(pvm, pvr, folder, pngname, gbix, x, y) helperFunctions.ReplaceTexture(pvm, pvr, (std::string(path) + "\\textures\\" folder "\\" pngname ".png").c_str(), gbix, x, y);

HelperFunctions HelperFunctionsGlobal;

wchar_t* ConvertCharToWChar(const char* value)
{
	const size_t cSize = strlen(value) + 1;
	wchar_t* wcharVariable = new wchar_t[cSize];
	mbstowcs(wcharVariable, value, cSize);
	return wcharVariable;
}

void ReplaceCharacter(const char* iniFile, const char* modDirectory, const HelperFunctions& helper)
{
	std::string iniFilePathString = modDirectory + (std::string)"\\" + iniFile + ".ini";

	const char* iniFilePathChar = iniFilePathString.c_str();
	wchar_t* iniFileFullPath = ConvertCharToWChar(iniFilePathChar);
	wchar_t* modPath = ConvertCharToWChar(modDirectory);

	helper.LoadDLLData(iniFileFullPath, modPath);
	delete[] iniFileFullPath;
	delete[] modPath;
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		ReplaceCharacter("chrmodels_data", path, helperFunctions);
		std::string fullPath = path + (std::string)"\\qo_jvlist.ini";
		helperFunctions.RegisterCharacterWelds(Characters_Sonic, fullPath.c_str());
		WriteJump((void*)0x49BE2D, (void*)0x49BE68);
		ReplacePVM("sonic", "Qoli");
		ReplacePVM("supersonic", "superqoli");
		ReplacePVM("son_eff", "qoli_eff");
		ReplaceTex("OBJ_REGULAR", "item_1up", "GUI", "item_1up", 4031, 64, 64);
		ReplaceTex("AVA_EMBLEMVIEW", "head_sonic", "GUI", "head_qoli", 10000613, 128, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "head_sonic", "GUI", "head_qoli", 10000613, 128, 32);
		ReplaceTex("AVA_FILESEL", "maru_sonic", "GUI", "maru_qoli", 365134, 64, 64);
		ReplaceTex("AVA_FILESEL_E", "maru_sonic", "GUI", "maru_qoli", 365134, 64, 64);
		ReplaceTex("AVA_FILESEL", "maru_supersonic", "GUI", "maru_superqoli", 365140, 64, 64);
		ReplaceTex("AVA_FILESEL_E", "maru_supersonic", "GUI", "maru_superqoli", 365140, 64, 64);
		ReplaceTex("B_CHNAM", "B_SONIC", "GUI", "B_QOLI", 365077, 512, 64);
		ReplaceTex("B_CHNAM", "b_supersonic", "GUI", "b_superqoli", 365083, 512, 64);
		ReplaceTex("B_CHNAM_E", "B_SONIC_e", "GUI", "B_QOLI_e", 10000032, 512, 64);
		ReplaceTex("B_CHNAM_E", "b_supersonic_e", "GUI", "b_superqoli_e", 10000028, 512, 64);
		ReplaceTex("CON_REGULAR", "hyoji_zanki_s", "GUI", "hyoji_zanki_j", 951, 32, 32);
		ReplaceTex("CON_REGULAR_E", "hyoji_zanki_s", "GUI", "hyoji_zanki_j", 951, 32, 32);
		ReplaceTex("M_CHNAM", "m_sonic", "GUI", "m_qoli", 365071, 256, 64);
		ReplaceTex("M_CHNAM", "m_supersonic", "GUI", "m_superqoli", 365255, 256, 64);
		ReplaceTex("MILESRACE", "tailsplay_sonic", "GUI", "tailsplay_qoli", 983, 128, 128);
		ReplaceTex("TX_CHNAM", "TX_SONIC", "GUI", "TX_QOLI", 365145, 64, 16);
		ReplaceTex("TX_CHNAM_E", "TX_SONIC", "GUI", "TX_QOLI_E", 10000463, 64, 16);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}
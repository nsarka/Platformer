#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Textures.h"
#include "LevelManager.h"
#include "Player.h"
#include "SDL_framerate.h"
#include "Mainmenu.h"
#include "Toolbar.h"
#include <iostream>
#include <string>
#include <vector>


class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	//Keep game loop going
	bool Running() { return bRunning; }

	void HandleEvents();
	void Render();
	void Update();
	void Delay();

	void UpdateDebugText();
	void DrawText(std::string TextString);
	void ToggleDebugInfo() { bDebugInfo = !bDebugInfo; }
	void ToggleSandboxMode() { bSandboxMode = !bSandboxMode; }

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	FPSmanager fpsManager;

	Mainmenu Menu;
	Toolbar* pEditorBar;

	bool bRunning = false;
	bool bDebugInfo = false;
	bool bSandboxMode = false;

	TTF_Font* GameOverFont;
	SDL_Color TextColor;

	std::string DebugString = "null";

	LevelManager levelManager;
};
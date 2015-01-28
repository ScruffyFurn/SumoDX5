//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

// SumoDX:
// This is the main game class.  It controls game play logic and game state.
// Some of the key object classes used by SumoDX are:
//     MoveLookController - for handling all input to control player/camera/cursor movement.
//     GameRenderer - for handling all graphics presentation.
//     Camera - for handling view projections.
//     m_renderObjects <GameObject> - is the list of all objects in the scene that may be rendered.

#include "../GameObjects/GameConstants.h"
#include "../GameObjects/Camera.h"
#include "../GameObjects/GameObject.h"
#include "../Utilities/GameTimer.h"
#include "../Input/MoveLookController.h"
#include "../Utilities/PersistentState.h"
#include "../Rendering/GameRenderer.h"
#include "../GameObjects/AISumoBlock.h"
#include "../GameObjects/SumoBlock.h"
#include "../GameObjects/Skydome.h"
#include "../Utilities/Audio.h"
#include "../GameObjects/SoundEffect.h"
#include "../GameObjects/PowerUpManager.h"
#include "../GameObjects/Face.h"

//--------------------------------------------------------------------------------------

enum class GameState
{

	Waiting,
	Active,
	PlayerLost,
	GameComplete,
};

typedef struct
{
    float bestRoundTime;
	float yourRoundTime;
} HighScoreEntry;

typedef std::vector<HighScoreEntry> HighScoreEntries;

//--------------------------------------------------------------------------------------

ref class GameRenderer;

ref class SumoDX
{
internal:
    SumoDX();

    void Initialize(
        _In_ MoveLookController^ controller,
        _In_ GameRenderer^ renderer
        );

    void LoadGame();
  
  
    void StartLevel();
    void PauseGame();
    void ContinueGame();
    GameState RunGame();

    void OnSuspending();
    void OnResuming();

    bool IsActivePlay()                         { return m_timer->Active(); }
	int RoundTime()								{ return m_timer->PlayingTime(); }
    
    bool GameActive()                           { return m_gameActive; }
    
    HighScoreEntry HighScore()                  { return m_topScore; }
  
    Camera^ GameCamera()                        { return m_camera; }
	std::vector<GameObject^> RenderObjects()    { return m_renderObjects; }
	Skydome^ GetSkydome()							{ return m_skydome; }
	Face^	GetGroundPlane()						{ return m_groundPlane; }
	PowerUpManager^ GetPowerUpManager()				{ return m_powerUpManager; }
	float GetPlayingTime()							{ return m_timer->PlayingTime(); }

	void	SlapSound(_In_ SoundEffect^ sound);
	void         StartSound(_In_ SoundEffect^ sound);
	void         MenuPopped(_In_ SoundEffect^ sound);
	void         MenuClicked(_In_ SoundEffect^ sound);
	SoundEffect^ SlapSound();
	SoundEffect^ StartSound();
	SoundEffect^ MenuPopped();
	SoundEffect^ MenuClicked();
private:
    void LoadState();
    void SaveState();
    void SaveHighScore();
    void LoadHighScore();
 
    void UpdateDynamics();

    MoveLookController^                         m_controller;
    GameRenderer^                               m_renderer;
    Camera^                                     m_camera;
	Audio^                                      m_audioController;

    HighScoreEntry                              m_topScore;
    PersistentState^                            m_savedState;

    GameTimer^                                  m_timer;
    bool                                        m_gameActive;

    SumoBlock^                                  m_player;
	AISumoBlock^								m_enemy;
	Skydome^									m_skydome;
	Face^										m_groundPlane;
	PowerUpManager^								m_powerUpManager;
	SoundEffect^								m_startSound;
	SoundEffect^								m_menuPoppedSound;
	SoundEffect^								m_menuClickedSound;
	SoundEffect^								m_slapSound;
    std::vector<GameObject^>                    m_renderObjects;     // List of all objects to be rendered.
	std::vector<GameObject^>                    m_animatedObjects;			// List of all objects to be animated
};


__forceinline void SumoDX::SlapSound(_In_ SoundEffect^ sound)
{
	m_slapSound = sound;
}

__forceinline void SumoDX::StartSound(_In_ SoundEffect^ sound)
{
	m_startSound = sound;
}

__forceinline void SumoDX::MenuPopped(_In_ SoundEffect^ sound)
{
	m_menuPoppedSound = sound;
}

__forceinline void SumoDX::MenuClicked(_In_ SoundEffect^ sound)
{
	m_menuClickedSound = sound;
}

__forceinline SoundEffect^ SumoDX::SlapSound()
{
	return m_slapSound;
}
__forceinline SoundEffect^ SumoDX::StartSound()
{
	return m_startSound;
}

__forceinline SoundEffect^ SumoDX::MenuPopped()
{
	return m_menuPoppedSound;
}

__forceinline SoundEffect^ SumoDX::MenuClicked()
{
	return m_menuClickedSound;
}
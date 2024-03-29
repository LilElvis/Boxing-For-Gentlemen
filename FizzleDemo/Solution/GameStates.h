#pragma once
#include <iostream> 
#include <string>
#include <unordered_map>

class GameState;

class GameStateManager
{
public:
	void AddGameState(std::string a_string, GameState* a_state);
	void RemoveGameState(std::string a_string);
	GameState* GetGameState(std::string a_string);
	void Update();
private:
	std::unordered_map<std::string, GameState*> m_states;
};

class GameState
{
public:
	virtual void Update() = 0;
	void SetPaused(bool a_paused);

	bool m_paused = false;

	GameStateManager* m_parent;
};
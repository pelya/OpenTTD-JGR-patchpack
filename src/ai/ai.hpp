/* $Id$ */

/** @file ai.hpp Base functions for all AIs. */

#ifndef AI_HPP
#define AI_HPP

#include "api/ai_event_types.hpp"

#ifndef AI_CONFIG_HPP
struct ltstr { bool operator()(const char *s1, const char *s2) const { return strcmp(s1, s2) < 0; } };
#endif /* AI_CONFIG_HPP */
typedef std::map<const char *, class AIInfo *, ltstr> AIInfoList;


void CcAI(bool success, TileIndex tile, uint32 p1, uint32 p2);

class AI {
public:
	/**
	 * The default months AIs start after eachother.
	 */
	enum StartNext {
		START_NEXT_EASY   = 48,
		START_NEXT_MEDIUM = 24,
		START_NEXT_HARD   = 12,
	};

	/**
	 * Is it possible to start a new AI company?
	 * @return True if a new AI company can be started.
	 */
	static bool CanStartNew();

	/**
	 * Start a new AI company.
	 * @param company At which slot the AI company should start.
	 */
	static void StartNew(CompanyID company);

	/**
	 * Called every game-tick to let AIs do something.
	 */
	static void GameLoop();

	/**
	 * Get the current AI tick.
	 */
	static uint GetTick();

	/**
	 * Stop a company to be controlled by an AI.
	 * @param company The company from which the AI needs to detach.
	 * @pre !IsHumanCompany(company).
	 */
	static void Stop(CompanyID company);

	/**
	 * Kill any and all AIs we manage.
	 */
	static void KillAll();

	/**
	 * Initialize the AI system.
	 */
	static void Initialize();

	/**
	 * Uninitialize the AI system
	 * @param keepConfig Should we keep AIConfigs, or can we free that memory?
	 */
	static void Uninitialize(bool keepConfig);

	/**
	 * Reset all AIConfigs, and make them reload their AIInfo.
	 * If the AIInfo could no longer be found, an error is reported to the user.
	 */
	static void ResetConfig();

	/**
	 * Queue a new event for an AI.
	 */
	static void NewEvent(CompanyID company, AIEvent *event);

	/**
	 * Broadcast a new event to all active AIs.
	 */
	static void BroadcastNewEvent(AIEvent *event, CompanyID skip_company = MAX_COMPANIES);

	/**
	 * Save data from an AI to a savegame.
	 */
	static void Save(CompanyID company);

	/**
	 * Load data for an AI from a savegame.
	 */
	static void Load(CompanyID company, int version);

	/**
	 * Get the number of months before the next AI should start.
	 */
	static int GetStartNextTime();

	static char *GetConsoleList(char *p, const char *last);
	static const AIInfoList *GetInfoList();
	static AIInfo *FindInfo(const char *name, int version);
	static bool ImportLibrary(const char *library, const char *class_name, int version, HSQUIRRELVM vm);
	static void Rescan();

private:
	static uint frame_counter;
	static class AIScanner *ai_scanner;
};

#endif /* AI_HPP */

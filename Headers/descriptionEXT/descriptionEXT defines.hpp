/* ----------------------------------------------------------------------------
	Corpse & Wreck Manager Modes
---------------------------------------------------------------------------- */
#define CW_MANAGER_MODE_NONE 0
#define CW_MANAGER_MODE_ALL 1
#define CW_MANAGER_MODE_ONLY_RESPAWNED 2
#define CW_MANAGER_MODE_ALL_BUT_RESPAWNED 3

/* ----------------------------------------------------------------------------
	Debug Console Settings
---------------------------------------------------------------------------- */
#define ENABLE_DEBUG_CONSOLE_EDITOR 0
#define ENABLE_DEBUG_CONSOLE_ADMIN_HOSTS 1
#define ENABLE_DEBUG_CONSOLE_ALL 2

/* ----------------------------------------------------------------------------
	Game Types
---------------------------------------------------------------------------- */
#define GAME_TYPE_UNKNOWN Unknown
#define GAME_TYPE_DEATHMATCH DM
#define GAME_TYPE_CAPTURE_THE_FLAG CTF
#define GAME_TYPE_COOP Coop
#define GAME_TYPE_CAPTURE_THE_ISLAND CTI
#define GAME_TYPE_SECTOR_CONTROL SC
#define GAME_TYPE_TEAM_DEATHMATCH TDM
#define GAME_TYPE_ROLE_PLAY RPG
#define GAME_TYPE_SANDBOX Sandbox
#define GAME_TYPE_KING_OF_THE_HILL KOTH
#define GAME_TYPE_LAST_MAN_STANDING LastMan
#define GAME_TYPE_SURVIVAL Survive
#define GAME_TYPE_ZEUS Zeus
#define GAME_TYPE_SUPPORT Support
#define GAME_TYPE_END_GAME EndGame
#define GAME_TYPE_APEX Apex
#define GAME_TYPE_ESCAPE Escape
#define GAME_TYPE_COMBAT_PATROL Patrol
#define GAME_TYPE_VANGUARD Vanguard
#define GAME_TYPE_WARLORDS Warlords

/* ----------------------------------------------------------------------------
	Respawn Types
---------------------------------------------------------------------------- */
#define RESPAWN_TYPE_NONE 0
#define RESPAWN_TYPE_BIRD 1
#define RESPAWN_TYPE_INSTANT 2
#define RESPAWN_TYPE_BASE 3
#define RESPAWN_TYPE_GROUP 4
#define RESPAWN_TYPE_SIDE 5

/* ----------------------------------------------------------------------------
	Respawn Templates
---------------------------------------------------------------------------- */
#define RESPAWN_TEMPLATE_NONE "None"
#define RESPAWN_TEMPLATE_SPECTATOR "Spectator"
#define RESPAWN_TEMPLATE_INSTANT "Instant"
#define RESPAWN_TEMPLATE_BASE "Base"
#define RESPAWN_TEMPLATE_GROUP "Group"
#define RESPAWN_TEMPLATE_SIDE "Side"
#define RESPAWN_TEMPLATE_SEAGULL "Seagull"
#define RESPAWN_TEMPLATE_WAVE "Wave"
#define RESPAWN_TEMPLATE_TICKETS "Tickets"
#define RESPAWN_TEMPLATE_COUNTER "Counter"
#define RESPAWN_TEMPLATE_END_MISSION "EndMission"
#define RESPAWN_TEMPLATE_MENU_POSITION "MenuPosition"
#define RESPAWN_TEMPLATE_MENU_INVENTORY "MenuInventory"

/* ----------------------------------------------------------------------------
	respawnOnStart Modes
---------------------------------------------------------------------------- */
// players do not respawn on mission start and onPlayerRespawn is NOT run
#define RESPAWN_ON_START_NONE -1
// players do NOT respawn on mission start but onPlayerRespawn IS run at start
#define RESPAWN_ON_START_NONE_RUN_SCRIPT 0
// players do respawn on mission start and onPlayerRespawn is run
#define RESPAWN_ON_START_RUN_SCRIPT 1

/* ----------------------------------------------------------------------------
	Misc
---------------------------------------------------------------------------- */
#define OFF 0
#define ON 1

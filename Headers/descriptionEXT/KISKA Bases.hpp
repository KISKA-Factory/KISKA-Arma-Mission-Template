// Side IDs are from BIS_fnc_sideID
#define SIDE_OPFOR 0
#define SIDE_BLUFOR 1
#define SIDE_INDEP 2

#define OFF 0
#define ON 1

class KISKA_Bases
{
    class aBase
    {
        side = SIDE_OPFOR;
        infantryClasses[] = { // these arrays can be weigthed or unweighted
            "someClass"
        };

        class turrets
        {
            //infantryClasses[] = {};
            class turretSet_1
            {
                //side = SIDE_OPFOR;
                //turrets[] = {}; // fill with variable names of turrets
                turrets = ""; // Searches for mission layer objects
                //infantryClasses[] = {};
                dynamicSim = ON;
            };
        };

        class infantry
        {
            //infantryClasses[] = {};
            class infantrySpawnSet_1
            {
                //infantryClasses[] = {};
                // side = SIDE_OPFOR;
                numberOfUnits = -1; // if -1, number of available positions is used this can only max out at the number of available positions
                unitsPerGroup = 1;

                positions = ""; // will search for objects in mission layer
                //positions[] = {};

                dynamicSim = ON;
                canPath = ON;
            };

        };

        class patrols
        {
            //infantryClasses[] = {};
            class patrol_1
            {
                // side = SIDE_OPFOR;
                //infantryClasses[] = {};
                spawnPosition = ""; // used with object, needs to be object's variable name
                //spawnPosition[] = {}; //positions in ATL format
                numberOfUnits = 5;

                // same as strings for corresponding waypoint commands
                behaviour = "SAFE";
                speed = "LIMITED";
                combatMode = "RED";
                formation = "STAG COLUMN";
                dynamicSim = ON;

                // SpecificPatrol will be used over RandomPatrol. Remove it if using RandomPatrol
            /*
                class SpecificPatrol
                {
                    patrolPoints = ""; // used with mission layer
                    //patrolPoints[] = {};
                    random = 1; // patrol randomly around the points or in order defined
                    numberOfPoints = -1; // patrol every provided positon if -1
                };
            */

                class RandomPatrol // uses CBA_fnc_taskPatrol
                {
                    //center[] = {}; // leave empty or remove to patrol around spawnPosition
                    numberOfPoints = 3; // number of waypoints
                    radius = 500; // max radius waypoints will be created around the area
                    waypointType = "MOVE";
                };

            };

        };

        class simples
        {
            class someClass
            {
                objectClasses[] = {

                };

                //positions = ""; // use with mission layer objects
                positions[] = {

                };
            };
        };
    };
};

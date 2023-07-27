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
        // infantryClasses will be either an array of classnames of possible infantry to spawn
        // or a string that will be compiled into a function that needs to return an array of classnames
        infantryClasses[] = { 
            // these arrays can be weigthed or unweighted
            // "someClass"
        };

        class turrets
        {
            // infantryClasses[] = {};
            class turretSet_1
            {
                // side = SIDE_OPFOR;
                // turrets[] = {}; // fill with variable names of turrets
                turrets = ""; // Searches for mission layer objects
                //infantryClasses[] = {};
                dynamicSim = ON;

                // script that is compiled once and called on each unit after all units are created for this set
                // params: 0: <OBJECT> - the created unit
                onUnitCreated = "";

                // script that is compiled once and called on each unit and turret after the unit has been moved in as gunner
                // params: 0: <OBJECT> - the created unit   1: <OBJECT> - the turret the unit's in
                onUnitMovedInGunner = "";
            };
        };

        // agents use most of the same properties, classes, and structures as infantry
        // except for unitsPerGroup, stancess, and canPath
        // numberOfUnits is instead numberOfAgents
        // and onUnitsCreated is instead onAgentsCreated
        class agents
        {
            class agentGroup_1
            {
                // if -1, number of available positions is used this can only max out at the number of available positions
                numberOfAgents = -1;
                // script that is compiled once and called with all units after all are created
                    // params: 0: <ARRAY> - the created units
                onAgentsCreated = "";
            };        
        };

        class infantry
        {
            // infantryClasses[] = {};
            class infantrySpawnSet_1
            {
                // infantryClasses[] = {};
                // side = SIDE_OPFOR;
                numberOfUnits = -1; // if -1, number of available positions is used this can only max out at the number of available positions
                unitsPerGroup = 1;

                // script that is compiled once and called with all units after all are created
                    // params: 0: <ARRAY> - the created units
                onUnitsCreated = "";

                positions = ""; // will search for objects in mission layer
                //positions[] = {};

                dynamicSim = ON;
                canPath = ON;

                // A weighted or unweighted array of values that will be randomly selected for unit positions
                // the positions need to be compatible with setUnitPos
                // An empty array or undefined property will be replaced with ["up",0.7,"middle",0.3]
                stances[] = {
                    "up",
                    0.7,
                    "middle",
                    0.3
                };

                // see KISKA_fnc_ambientAnim for functional details as that is the function
                // used to creat the animation affects
                class AmbientAnim
                {
                    // The "animationSet" property will determine what animations may play on the unit
                    // The "animationSet" property can be either a class, string[] (array), or string.
                    // animationSet refers to a definition of a collection of certain animations
                    // Default animation sets are defined in the configFile >> "KISKA_AmbientAnimations" class

                    // An array means that an animation set will be randomly selected from the array
                    /// for each unit in created by infantrySpawnSet_1
                    /// This array can be weighted or unweighted ({"set1",0.5,"set2",0.5})
                    // animationSet[] = {};

                    // A string for animationSet will mean that every unit will have this animation applied to them
                    // animationSet = "";

                    // A class for animationSet is used for snapping animations
                    // It also enables the use of units that might stand an might not
                    /// due to it having the ability to detect when a unit can't find
                    /// something to snap to
                    class animationSet
                    {
                        // snapToAnimations = "";
                        snapToAnimations[] = {
                            ""
                        };
                        // "backupAnimations" are used in lieu of the unit successfully being able to snap to an object
                        // backupAnimations = "";
                        backupAnimations[] = {
                            // both backupAnimations and snapToAnimations can be weighted arrays
                            "", 1 
                        };
                        // "snapToRange" is the radius to search around the unit for potential objects to snap to
                        // the max radius is 5.
                        snapToRange = 10;

                        // should a unit fail to find a nearby object to snap to and no 
                        // backupAnimations are present this function will be run
                        // see KISKA_fnc_ambientAnim for params
                        fallbackFunction = "";
                    };

                    // Adjustements to equipment of unit to fit the animation
                    // these adjustments are temporary and full equipment will be restored
                    // upon stopping the animation with KISKA_fnc_ambientAnim_stop
                    // - "": no changes
                    // - "NONE": no goggles, headgear, vest, weapon, nvgs, backpack
                    // - "LIGHT": no goggles, headgear, vest, backpack
                    // - "MEDIUM": no goggles, headgear
                    // - "FULL": no goggles
                    equipmentLevel = "";
                    // "equipmentLevel" can also be a weighted or unweighted array to randomly select from
                    // equipmentLevel[] = {"NONE",1};

                    // Certain animation sets (mostly sitting in chair ones)
                    // will automatically snap to objects of certain classes
                    // should they be in this radius
                    snapToRange = 5;

                    // if units get into combat, they will stop their animations
                    // and have their loadouts restored
                    exitOnCombat = ON;

                    // if your animation sets do not fall into the default configFile >> "KISKA_AmbientAnimations" class
                    // this function can provide a custom animation set map
                    // see KISKA_fnc_ambientAnim_createMapFromConfig
                    getAnimationMapFunction = "";
                };
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
                //spawnPosition[] = {}; // position in ATL format
                numberOfUnits = 5;
                // script that is compiled and run on the patrol group after they are spawned and given patrol route
                // params are 0: <GROUP> - the patrol group
                onGroupCreated = "";

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

                class reinforce
                {
                    id = "patrolUnit";
                    // see KISKA_fnc_bases_triggerReaction
                    // Must return bool, whether or not to prevent KISKA_fnc_bases_triggerReaction after
                    // this script completes (e.g. return false to run KISKA_fnc_bases_triggerReaction)
                    onEnteredCombat = "hint str _this; false";
                    canCall[] = {
                        "armorReinforcement"
                    };
                };

            };

        };

        class landVehicles
        {
            class aVehicle
            {
                vehicleClass = "some_vehicle_class_name";

                position[] = {0,0,0};
                // position[] = {0,0,0, 300}; // alternative to give direction to face
                // position = ""; // alternative for with an object

                // see KISKA_fnc_spawnVehicle _crewInstructions param
                // used with moveInAny in order of appearance
                // overflow is deleted
                crew[] = {
                    "B_crew_F", // driver class
                    "B_crew_F", // commander class
                    "B_crew_F" // gunner class
                    //... etc.
                };


                onVehicleCreated = ""; // code to compile after vehicle is created and properties set
                    // params: 0: <OBJECT> - the created vehicle
                    // params: 1: <ARRAY> - An array containing the vehicle's crew
                    // params: 2: <GROUP> - The crew's group

                canPath = ON; // PATH ai will be disabled on driver
                dynamicSim = ON; // vehicle and created groups will be dynamically simmed on all machines

                class reinforce
                {
                    // id will default to the configName if no present (e.g. this would mean id = "aVehicle")
                    // id = "armorReinforcement";

                    // see KISKA_fnc_bases_triggerReaction
                    // Must return bool, whether or not to prevent KISKA_fnc_bases_triggerReaction after
                    // this script completes (e.g. return false to run KISKA_fnc_bases_triggerReaction)
                    onEnteredCombat = "hint str _this; false";
                    canCall[] = {
                        "patrolUnit"
                    };
                    // mission priority will determine if a canCall unit should break off
                    // from a lesser priority call in order to support this one
                    priority = 1;
                };
            };
        };

        class simples
        {
            class setOfVehicles
            {

                positions = ""; // mission layer of objects to get positions from
                // positions[] = { /* expects array positionWorld positions */ };
                class vehicleClass_1
                {
                    // "filterCondition" can be used to dynamically filter out a given 
                    /// class from being available for random selection; (`true` to include, `false` to exclude)
                    // an undefined "filterCondition" or empty ("") one will always be available sor selection
                        // parameters: 0: <CONFIG> - this config class
                    filterCondition = "";

                    // followTerrain = ON;  // Should object try to adjust to the terrain angle (ON by default)
                    // superSimple = ON; // Should object be super simple, which offers slightly more performance for vehicles (ON by default)
                    // vectorUp[] = {}; // vectorUp to apply to vehicles upon creation
                    // vectorDir[] = {}; // vectorDir to apply to vehicles upon creation
                    // offset[] = {0,0,0.1}; // an offset to apply to the spawn position of the object with "vectorAdd" (defaults to {0,0,0.1})

                /*
                    // an array of animations and their phase to apply to the vehicle upon creation
                    animations[] = {
                        {"someAnimation",15}
                    };
                */

                /*
                    // an array of hidden selection arrays to adjust upon creation with "hideSelection"
                    // if right number is greater than 0, hideSelection will be given "true"
                    selections[] = {
                        // (_simpleObject hideSelection ["hiddenSelectionToHide", true])
                        {"hiddenSelectionToHide",1},

                        // (_simpleObject hideSelection ["otherHiddenSelectionToHide", false])
                        {"otherHiddenSelectionToHide",0}
                    };
                */

                    // a function that runs upon creation of each simple object for this class
                        // parameters: 0: <OBJECT> - the simple object created
                    // onObjectCreated = "hint str _this";

                    type = "vehicle_1_classname";

                    // A function that when compiled will return the classname to use for this simple object
                    // If both `type` and `getTypeFunction` properties are present, getTypeFunction's return will be used
                    /// (e.g. the class this `getTypeFunction` property is defined in)
                        // parameters: 0: <CONFIG> - this config class
                    // getTypeFunction = "";
                };

                class vehicleClass_2 : vehicleClass_1
                {
                    type = "vehicle_2_classname";
                };
            };

        };
    };
};

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
        /* -------------------------------------------------------------------------------
            Description: 
                - side: <NUMBER> - Sets the side of units that spawn in the base.

            Required: 
                - NO
            
            Sections:
                - infantry
                - agents
                - turrets
                - vehicles

            Definition Levels:
                - Base Root
                - Base Section
                - Section Set

            Examples:
                (begin example)
                    side = 0; // OPFOR
                (end)
                
                (begin example)
                    side = 1; // BLUFOR
                (end)
                
                (begin example)
                    side = 2; // INDEPENDENT
                (end)
        ------------------------------------------------------------------------------- */
        side = SIDE_OPFOR;

        /* -------------------------------------------------------------------------------
            Description: 
                - unitClasses: <STRING | STRING[]> - The classNames of units that can be spawned

                STRING:
                    A script that is compiled once and must return an array of classNames 
                    (weighted or unweighted) to choose from.

                    Parameters:
                        0: <CONFIG> - The config path of the set that is being parsed

                STRING[]:
                    An array of classNames to randomly select from. Array can be weighted or
                    unweighted.

            Required: 
                - YES

            Sections:
                - infantry
                - agents
                - turrets

            Definition Levels:
                - Base Root
                - Base Section
                - Section Set

            Examples:
                (begin example)
                    unitClasses = "['B_soldier_AR_F', 'B_Soldier_GL_F']";
                (end)

                (begin example)
                    // will select randomly from two classNames
                    unitClasses[] = {"B_soldier_AR_F", "B_Soldier_GL_F"};
                (end)

                (begin example)
                    // weighted
                    unitClasses[] = {"B_soldier_AR_F", 1, "B_Soldier_GL_F", 0.5};
                (end)
        ------------------------------------------------------------------------------- */
        unitClasses[] = {};
        
        /* -------------------------------------------------------------------------------
            Description: 
                - dynamicSim: <`0` | `1`> - Adjusts whether the turret and its gunner are dynamically
                simulated after being spawned. `0` to turn off, `1` to turn on.

            Required: 
                - NO

            Definition Levels:
                - Base Root
                - Base Section
                - Section Set
            
            Sections:
                - infantry
                - agents
                - turrets
                - vehicles

            Default: 
                - `0`

            Examples:
                (begin example)
                    dynamicSim = 1;
                (end)
        ------------------------------------------------------------------------------- */                    
        dynamicSim = ON;

        class turrets
        {
            class sets
            {
                class turret_1
                {
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - spawnPositions: <STRING | (PositionATL[] | PositionAGL[])[]> - The positions 
                            that the turret can spawn at. Final positions will be randomly selected from the results.
                            
                            STRING:
                                The name of a mission layer that contains objects that will be used as possible 
                                spawn positions for the turrets. Turrets will face the same direction as a given 
                                object if selected from the layer as a spawn position.

                            ARRAY:
                                Array must be of positions in the format PositionATL[] or PositionAGL[] 
                                (if over water). Optionally, a fourth number in the position array may be
                                added that will designate what direction the turret will face after spawning.
                                This array can also be weighted or unweighted.

                        Required: 
                            - YES

                        Definition Levels:
                            - Section Set

                        Examples:
                            (begin example)
                                spawnPositions = "myLayerWithObjects";
                            (end)
                            
                            (begin example)
                                // unweighted 
                                spawnPositions[] = {
                                    {0,0,0},
                                    {0,0,0,180} // turret will face 180 degrees
                                };
                            (end)
                            
                            (begin example)
                                // weighted 
                                spawnPositions[] = {
                                    {0,0,0}, 1
                                    {0,0,0,180}, 0.5
                                };
                            (end)
                    ------------------------------------------------------------------------------- */
                    spawnPositions = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - turretClassNames: <STRING | STRING[]> - The classNames of turrets that can be spawned.

                            STRING:
                                A script that is compiled once and must return an array of classNames 
                                (weighted or unweighted) to choose from.

                                Parameters:
                                    0: <CONFIG> - The config path of the infantry set

                            STRING[]:
                                An array of classNames to randomly select from. Array can be weighted or
                                unweighted.

                        Required: 
                            - YES

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                turretClassNames = "['B_HMG_01_high_F', 'B_GMG_01_high_F']";
                            (end)

                            (begin example)
                                // will select randomly from two classNames
                                turretClassNames[] = {"B_HMG_01_high_F", "B_GMG_01_high_F"};
                            (end)

                            (begin example)
                                // weighted
                                turretClassNames[] = {"B_HMG_01_high_F", 1, "B_GMG_01_high_F", 0.5};
                            (end)
                    ------------------------------------------------------------------------------- */
                    turretClassNames[] = {};


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - numberOfTurrets: <NUMBER | STRING> - The number of turrets to spawn. Can't exceed the
                            number of `spawnPositions`. If a negative number, all turret positions will be used.

                            NUMBER:
                                The number of turrets.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number.

                                Parameters:
                                    0: <CONFIG> - The config path of the turret base set
                                    1: <OBJECT[] | (PositionATL[] | PositionAGL[])[]> - The possible spawn positions

                        Required: 
                            - YES

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Default:
                            - `-1`

                        Examples:
                            (begin example)
                                numberOfTurrets = -1;
                            (end)

                            (begin example)
                                numberOfTurrets = -1;
                            (end)

                            (begin example)
                                numberOfTurrets = "params ['_config','_spawnPositions']; count _spawnPositions";
                            (end)
                    ------------------------------------------------------------------------------- */
                    numberOfTurrets = -1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - onGunnerCreated: <STRING> - Uncompiled code that will be compiled and executed
                            immediatley after the gunner is created BEFORE they are moved into the turret.

                            Parameters:
                                0: <CONFIG> - The config path of the turret base set
                                1: <OBJECT> - The gunner created
                                2: <OBJECT> - The turret the gunner will be moved into

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Examples:
                            (begin example)
                                onGunnerCreated = "params ['_config','_gunner','_turret']; hint str _gunner";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onGunnerCreated = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - onUnitMovedInGunner: <STRING> - Uncompiled code that will be compiled and executed
                            immediatley after the gunner is moved into the turret.

                            Parameters:
                                0: <CONFIG> - The config path of the turret base set
                                1: <OBJECT> - The gunner created
                                2: <OBJECT> - The turret the gunner will be moved into

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                onUnitMovedInGunner = "params ['_config','_gunner','_turret']; hint str _gunner";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onUnitMovedInGunner = "";
                };
            };
        };

        // agents use most of the same properties, classes, and structures as infantry
        // except for unitsPerGroup, stanceses, and canPath
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
            class sets
            {
                class infantrySpawnSet_1
                {
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - numberOfUnits: <NUMBER | STRING> - The number of units in total to spawn. Can't exceed the
                            number of `spawnPositions`. If a negative number, all positions will be used.

                            NUMBER:
                                The number of units.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number.

                                Parameters:
                                    0: <CONFIG> - The config path of the infantry base set
                                    1: <OBJECT[] | (PositionATL[] | PositionAGL[])[]> - The possible spawn positions

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Infantry Section
                            - Section Set

                        Default:
                            - `-1`

                        Examples:
                            (begin example)
                                numberOfUnits = -1;
                            (end)

                            (begin example)
                                numberOfUnits = -1;
                            (end)

                            (begin example)
                                numberOfUnits = "params ['_config','_spawnPositions']; count _spawnPositions";
                            (end)
                    ------------------------------------------------------------------------------- */
                    numberOfUnits = -1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - unitsPerGroup: <NUMBER | STRING> - The number of units per each group.
                            this will determine how the total number of units created for the set are
                            divided between each group.

                            NUMBER:
                                The number of units that will be in each group.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number.

                                Parameters:
                                    0: <CONFIG> - The config path of the infantry base set
                                    1: <OBJECT[] | (PositionATL[] | PositionAGL[])[]> - The possible spawn positions

                        Required: 
                            - NO

                        Definition Levels:
                            - Infantry Section
                            - Section Set

                        Default: 
                            - `-1`

                        Examples:
                            (begin example)
                                unitsPerGroup = -1;
                            (end)

                            (begin example)
                                unitsPerGroup = -1;
                            (end)

                            (begin example)
                                unitsPerGroup = "params ['_setConfig','_numberOfUnits','_spawnPositions']; (count _numberOfUnits) / 2";
                            (end)
                    ------------------------------------------------------------------------------- */
                    unitsPerGroup = -1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - spawnPositions: <STRING | (PositionATL[] | PositionAGL[])[]> - The positions 
                            that the units can spawn at. Final positions will be randomly selected from the results.
                            
                            STRING:
                                The name of a mission layer that contains objects that will be used as possible 
                                spawn positions for the units. Units will face the same direction as a given 
                                object if selected from the layer as a spawn position.

                            ARRAY:
                                Array must be of positions in the format PositionATL[] or PositionAGL[] 
                                (if over water). Optionally, a fourth number in the position array may be
                                added that will designate what direction the turret will face after spawning.
                                This array can also be weighted or unweighted.

                        Required: 
                            - YES

                        Definition Levels:
                            - Section Set

                        Examples:
                            (begin example)
                                spawnPositions = "myLayerWithObjects";
                            (end)
                            
                            (begin example)
                                // unweighted 
                                spawnPositions[] = {
                                    {0,0,0},
                                    {0,0,0,180} // turret will face 180 degrees
                                };
                            (end)
                            
                            (begin example)
                                // weighted 
                                spawnPositions[] = {
                                    {0,0,0}, 1
                                    {0,0,0,180}, 0.5
                                };
                            (end)
                    ------------------------------------------------------------------------------- */
                    spawnPositions = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - canPath: <`0` | `1`> - Adjusts whether the units spawned can walk away from
                            their spawn position.

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Section
                            - Section Set
                        
                        Default: 
                            - `1`

                        Examples:
                            (begin example)
                                // pathing enabled
                                canPath = 1;
                            (end)
                    ------------------------------------------------------------------------------- */ 
                    // canPath = 1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - onUnitsCreated: <STRING> - Code that will be compiled and run after units
                            in the set have been initialized.

                                Parameters:
                                    0: <CONFIG> - The config path of the infantry base set
                                    1: <OBJECT[]> - The units created for the infantry set

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                onUnitsCreated = "params ["_infantrySetConfig","_units"]; hint str _this;";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onUnitsCreated = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - stances: <STRING[]> - The stances that units will be able to randomly
                            take. See `setUnitPos` command for options. Array can be weighted or unweighted.

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Section
                            - Section Set

                        Default:
                            - `{"up", 0.7, "MIDDLE", 0.3}`

                        Examples:
                            (begin example)
                                // will select randomly list
                                stances[] = {"DOWN", "UP", "MIDDLE"};
                            (end)

                            (begin example)
                                // weighted
                                stances[] = {"up", 0.5, "middle", 0.3};
                            (end)
                    ------------------------------------------------------------------------------- */
                    // stances[] = {};


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - AmbientAnim: <class> - Handles automatically animating units that are spawned
                            for the given set. See KISKA_fnc_ambientAnim for implementation details. 
                            This is relatively slow to initialize and should really be done at mission start up. 
                            Dyamic simulation does work with these animations.

                        Required: 
                            - NO

                        Definition Levels:
                            - Section Set
                    ------------------------------------------------------------------------------- */
                    class AmbientAnim
                    {
                        /* -------------------------------------------------------------------------------
                            Description: 
                                - animationSet: <STRING | class | STRING[]> - Determines what animation set
                                the spawned units can use. And animation set is a collection of animations that
                                a unit will be able to cycle through. Default animation sets are defined in 
                                the `configFile >> "KISKA_AmbientAnimations"` class.

                                STRING:
                                    - A string for animationSet will mean that every unit will have this 
                                    animation set applied to them.
                                
                                STRING[]:
                                    - An array means that an animation set will be randomly selected from 
                                    the array on a per unit basis. This array can be weighted or unweighted.

                                class:
                                    - Class provides the most detailed and allows the use of snap-to animation
                                    sets such as those for sitting animations.

                            Required: 
                                - YES

                            Examples:
                                (begin example)
                                    animationSet[] = {"STAND_ARMED_1","STAND_ARMED_2"};
                                (end)

                                (begin example)
                                    // weighted
                                    animationSet[] = {"STAND_ARMED_1",0.5,"STAND_ARMED_2",0.5};
                                (end)

                                (begin example)
                                    // single animation set
                                    animationSet = "STAND_ARMED_1";
                                (end)
                        ------------------------------------------------------------------------------- */
                        class animationSet
                        {
                            /* -------------------------------------------------------------------------------
                                Description: 
                                    - snapToAnimations: <STRING | STRING[]> - Used specifically assigning snap-to
                                    animation sets to units. If defined, `snapToAnimations` will be selected over
                                    other properties. A snap-to animation is one that will automatically orient
                                    a unit to a compatible object within a given distance, such as a sitting 
                                    animation for a chair.
                                    
                                    !!IMPORTANT!! All `snapToAnimations` will be tried (in a random order) until 
                                    an object to snap to has been found. Should every provided snap animation 
                                    be tried and no objects found, the order of precedence is:
                                        1. `backupAnimations`
                                        2. `fallbackFunction`
                                        3. No ambient animation applied

                                    STRING:
                                        - Every unit will have this snap-to animation set applied to them.
                                    
                                    STRING[]:
                                        - An array of (snap-to) animation sets to randomly play on units in the base
                                        spawn set. This array can be weighted or unweighted. Each animation is randomly
                                        selected per unit.

                                Required: 
                                    - YES

                                Examples:
                                    (begin example)
                                        snapToAnimations = "SIT_CHAIR_ARMED_1";
                                    (end)

                                    (begin example)
                                        // unweighted
                                        snapToAnimations[] = {"SIT_CHAIR_ARMED_1","SIT_CHAIR_ARMED_1"};
                                    (end)

                                    (begin example)
                                        // weighted
                                        snapToAnimations[] = {"SIT_CHAIR_ARMED_1",0.5,"SIT_CHAIR_ARMED_1",0.5};
                                    (end)
                            ------------------------------------------------------------------------------- */
                            snapToAnimations[] = {};


                            /* -------------------------------------------------------------------------------
                                Description: 
                                    - backupAnimations: <STRING | STRING[]> - Backup animations are used when
                                    no object can be found to snap to for the `snapToAnimations`.

                                    STRING:
                                        - Any unit that fails to find a suitable snap-to animation will have this
                                        backup animation applied to them.
                                    
                                    STRING[]:
                                        - An array of non-snap-to animation sets to randomly play on units in the base
                                        spawn set. This array can be weighted or unweighted. Each animation is randomly
                                        selected per unit.

                                Required: 
                                    - NO

                                Examples:
                                    (begin example)
                                        backupAnimations[] = {"STAND_ARMED_1","STAND_ARMED_2"};
                                    (end)

                                    (begin example)
                                        // weighted
                                        backupAnimations[] = {"STAND_ARMED_1",0.5,"STAND_ARMED_2",0.5};
                                    (end)

                                    (begin example)
                                        // single animation set
                                        backupAnimations = "STAND_ARMED_1";
                                    (end)
                            ------------------------------------------------------------------------------- */
                            // backupAnimations[] = {};


                            /* -------------------------------------------------------------------------------
                                Description: 
                                    - snapToRange: <NUMBER> - The radius to search for a compatible object 
                                    within for every animation set in `snapToAnimations`. The search center is
                                    the given unit's position. Higher number is more performance intensive. 
                                    Ultimately the closest compatible object will be used. Max radius is `10`.

                                Required: 
                                    - NO

                                Default:
                                    - `5`

                                Examples:
                                    (begin example)
                                        snapToRange = 10;
                                    (end)
                            ------------------------------------------------------------------------------- */
                            // snapToRange = 5;


                            /* -------------------------------------------------------------------------------
                                Description: 
                                    - fallbackFunction: <STRING> - A function that will be compiled (once) and
                                    called if no `backupAnimations` are present and no suitable `snapToAnimations` 
                                    can be found. The idea of this funciton is that it gives you all the values you
                                    would need to make specific adjustments to how you want a unit to be animated
                                    should no snap animations be found, and therefore allow you to call `KISKA_fnc_ambientAnim`
                                    manually.

                                    Parameters:
                                        - 0: _unit <OBJECT> - The unit that was trying to be animated.
                                        - 1: _animationParams <STRING[], (STRING,NUMBER)[], or STRING> - The parsed
                                        input value for `KISKA_fnc_ambientAnim`. This will essentially be the `animationSet`
                                        property.
                                        - 2: _exitOnCombat <BOOL> - Whether or not units will stop ambient animations
                                        upon detecting an enemy.
                                        - 3: _equipmentLevel <STRING[], (STRING,NUMBER)[], or STRING> - The `equipmentLevel` 
                                        property value.
                                        - 4: _animationMap <HASHMAP or CONFIG> - This is a hashmap that will searched for 
                                        information for a specific animation set.

                                Required: 
                                    - NO

                                Examples:
                                    (begin example)
                                        fallbackFunction = "params ["_unit","_animationParams","_exitOnCombat","_equipmentLevel","_animationMap"]; hint str _this;"
                                    (end)
                            ------------------------------------------------------------------------------- */
                            // fallbackFunction = "";
                        };


                        /* -------------------------------------------------------------------------------
                            Description: 
                                - equipmentLevel: <STRING | STRING[]> - Adjustments to equipment of unit to fit the animation
                                these adjustments are temporary and full equipment will be restored upon
                                stopping the animation with `KISKA_fnc_ambientAnim_stop` which happens 
                                when exiting from combat.

                                Options:
                                    - "": no changes
                                    - "NONE": no goggles, headgear, vest, weapon, nvgs, backpack
                                    - "LIGHT": no goggles, headgear, vest, backpack
                                    - "MEDIUM": no goggles, headgear
                                    - "FULL": no goggles

                                STRING:
                                    - All units will be assigned this equipment level.

                                STRING[]:
                                    - Units will randomly select from the equipment levels provided. Array
                                    can be weighted or unweighted.
                                
                            Required: 
                                - NO

                            Default:
                                - `""`

                            Examples:
                                (begin example)
                                    equipmentLevel = "MEDIUM";
                                (end)

                                (begin example)
                                    // weighted
                                    equipmentLevel[] = {"NONE",0.5,"",0.5};
                                (end)

                                (begin example)
                                    // unweighted
                                    equipmentLevel[] = {"NONE",""};
                                (end)
                        ------------------------------------------------------------------------------- */
                        // equipmentLevel = "";

        
                        /* -------------------------------------------------------------------------------
                            Description: 
                                - exitOnCombat: <`0` | `1`> - Adjusts whether or not a unit will exit their
                                ambient animation upon entering combat or detecting an enemy.

                            Required: 
                                - NO

                            Default: 
                                - `0`

                            Examples:
                                (begin example)
                                    // will NOT exit on combat
                                    exitOnCombat = 0;
                                (end)
                        ------------------------------------------------------------------------------- */ 
                        // exitOnCombat = 1;


                        /* -------------------------------------------------------------------------------
                            Description: 
                                - fallbackFunction: <STRING> - A function that will be compiled (once) and
                                called that must return either a CONFIG or HASHMAP. This is for advanced users
                                that want to add a custom list of animation sets. See `KISKA_fnc_ambientAnim_createMapFromConfig`
                                to see how configs are parsed or how a HASHMAP should be shaped.

                                Parameters:
                                    NONE

                            Required: 
                                - NO

                            Examples:
                                (begin example)
                                    // provide default animation map
                                    getAnimationMapFunction = "configFile >> 'KISKA_AmbientAnimations' >> 'DefaultAnimationMap'";
                                (end)
                        ------------------------------------------------------------------------------- */
                        // getAnimationMapFunction = "";
                    };
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

                // used with object, needs to be object's variable name
                spawnPosition = ""; 

                // position in ATL format
                //spawnPosition[] = {}; 

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
                    // used with mission layer
                    patrolPoints = ""; 
                    //patrolPoints[] = {};

                    // randomly around the points or in order defined
                    random = 1; // patrol 
                    // patrol every provided positon if -1
                    numberOfPoints = -1; 
                };
            */
                // uses CBA_fnc_taskPatrol
                class RandomPatrol 
                {
                    // leave empty or remove to patrol around spawnPosition
                    //center[] = {}; 

                    // number of waypoints
                    numberOfPoints = 3;

                    // max radius waypoints will be created around the area
                    radius = 500; 

                    waypointType = "MOVE";
                };

                class reinforce
                {
                    id = "patrolUnit";
                    // see KISKA_fnc_bases_triggerReaction
                    // Must return bool, whether or not to prevent KISKA_fnc_bases_triggerReaction after
                    // this script completes (e.g. return false to run KISKA_fnc_bases_triggerReaction)
                    onEnemyDetected = "hint str _this; false";
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
                    onEnemyDetected = "hint str _this; false";
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

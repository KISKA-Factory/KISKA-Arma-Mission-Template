// Side IDs are from BIS_fnc_sideID
#define SIDE_OPFOR 0
#define SIDE_BLUFOR 1
#define SIDE_INDEP 2

#define OFF 0
#define ON 1

/* ----------------------------------------------------------------------------
    Conditional properties

    All properties in a base at any level can be placed in a conditional class that allows 
    for more dynamic base creation. `KISKA_fnc_getConditionalConfigValue` is what 
    supports this functionality.

    Let's say that I want my `side` to conditionally change and I define it at the 
    base root:
    (begin example)
        class KISKA_Bases
        {
            class MyBase
            {
                // classes MUST be titles `conditional`
                class conditional
                {
                    class MyConditionalClass_1
                    {
                        condition = "localNamespace getVariable ['KISKA_makeSideIndependent',false]";

                        class properties
                        {
                            side = SIDE_INDEP;
                        };
                    };
                };
            };
        };
    (end)

    Since `side` can be defined in any section, we could also specify this conditional property
    in say an infantry section or set:
    (begin example)
        class KISKA_Bases
        {
            class MyBase
            {
                class infantry
                {
                    class sets
                    {
                        class InfantrySet_1
                        {
                            class conditional
                            {
                                class MyConditionalSideClass_1
                                {
                                    condition = "localNamespace getVariable ['KISKA_makeInfantrySet1SideIndependent',false]";

                                    class properties
                                    {
                                        side = SIDE_INDEP;
                                    };
                                };
                            };

                            spawnPositions = "SomeLayer";
                            numberOfUnits = 3;
                            canPath = ON;
                        };
                    };
                };
            };
        };

        It's important to understand how `KISKA_fnc_getConditionalConfigValue` works and
        its limitations. Read the documentation in its file on Github if you intend to use
        this feature.

        Also of note is that conditional properties are checked BEFORE the level's
    (end)

---------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------
    Reinforce Classes

    A reinforce class can be added to a patrol, infantry, and/or landVehicle set.
    This provides a configured mechanism of very basic (at the moment) reactivity
    among units at the base when enemies are spotted. See `KISKA_fnc_bases_triggerReaction`
    for more details.

class infantry
{
    class sets
    {
        class MyInfantrySet
        {
            class reinforce
            {
                Description: 
                    - id: <NUMBER | STRING> - A GLOBALLY unique identifier for this reinforce class.

                Required: 
                    - NO

                Default: 
                    - If left blank, the set `configName` is used (e.g. "MyInfantrySet" in this case)

                Examples:
                    (begin example)
                        id = "SomeUniqueId";
                    (end)
                    
                    (begin example)
                        id = 1;
                    (end)
                id = "";


                Description: 
                    - onEnemyDetected: <STRING> - Uncompiled code that will be run once an enemy is detected by the
                    units in the set.

                    Parameters:
                        0: <GROUP> - The group that detected the enemy and is the group of the set
                        1: <OBJECT> - The detected target
                        2: <GROUP[]> - The groups that can be called to respond to the detecting group
                        2: <NUMBER> - The priority of the call

                Required: 
                    - NO

                Default: 
                    - See `KISKA_fnc_bases_triggerReaction` for default behaviour.

                Examples:
                    (begin example)
                        id = "SomeUniqueId";
                    (end)
                    
                    (begin example)
                        onEnemyDetected = "hint str _this";
                    (end)
                onEnemyDetected = "";


                Description: 
                    - canCall: <(STRING | NUMBER)[]> - An array of other reinforce `id`s that can be called 
                    by the detecting group

                Required: 
                    - YES

                Examples:
                    (begin example)
                        canCall[] = {1, "SomeId"};
                    (end)
                canCall[] = {};


                Description: 
                    - priority: <NUMBER> - The priority of the call that this group will have.
                    With the default behaviour, if a group in the `canCall` is responding to a lower
                    priority call, they will break off and attempt to respond to the higher one.

                Required: 
                    - NO

                Default: 
                    - -1

                Examples:
                    (begin example)
                        priority = 100;
                    (end)
                priority = -1;
            };
        };
    };
};
---------------------------------------------------------------------------- */



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
                - patrols
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
                - patrols
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
                - patrols

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
                                    0: <CONFIG> - The config path of the turrets set

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
                            - minElevation: <NUMBER | STRING> - Used with the `setTurretLimits`, allows
                            the designer to limit a turret's field of fire.

                            NUMBER:
                                The exact minimum for the turret's elevation.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number
                                for the limit.

                                Parameters:
                                    0: <CONFIG> - The config path of the turret base set
                                    1: <OBJECT> - The turret
                                    2: <OBJECT> - The gunner
                                    3: <NUMBER[]> - The turret's default limits `[minTurn, maxTurn, minElev, maxElev]`

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Default:
                            - Whatever the default limit is for the specific turret.

                        Examples:
                            (begin example)
                                minElevation = -10;
                            (end)

                            (begin example)
                                minElevation = "params ['_config','_turret','_gunner','_defaultLimits']; -10";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // minElevation = 0;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - maxElevation: <NUMBER | STRING> - Used with the `setTurretLimits`, allows
                            the designer to limit a turret's field of fire.

                            NUMBER:
                                The exact maximum for the turret's elevation.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number
                                for the limit.

                                Parameters:
                                    0: <CONFIG> - The config path of the turret base set
                                    1: <OBJECT> - The turret
                                    2: <OBJECT> - The gunner
                                    3: <NUMBER[]> - The turret's default limits `[minTurn, maxTurn, minElev, maxElev]`

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Default:
                            - Whatever the default limit is for the specific turret.

                        Examples:
                            (begin example)
                                maxElevation = 10;
                            (end)

                            (begin example)
                                maxElevation = "params ['_config','_turret','_gunner','_defaultLimits']; 10";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // maxElevation = 0;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - maxRotation: <NUMBER | STRING> - Used with the `setTurretLimits`, allows
                            the designer to limit a turret's field of fire.

                            NUMBER:
                                The exact maximum for the turret's rotation.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number
                                for the limit.

                                Parameters:
                                    0: <CONFIG> - The config path of the turret base set
                                    1: <OBJECT> - The turret
                                    2: <OBJECT> - The gunner
                                    3: <NUMBER[]> - The turret's default limits `[minTurn, maxTurn, minElev, maxElev]`

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Default:
                            - Whatever the default limit is for the specific turret.

                        Examples:
                            (begin example)
                                maxRotation = 45;
                            (end)

                            (begin example)
                                maxRotation = "params ['_config','_turret','_gunner','_defaultLimits']; 45";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // maxRotation = 0;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - minRotation: <NUMBER | STRING> - Used with the `setTurretLimits`, allows
                            the designer to limit a turret's field of fire.

                            NUMBER:
                                The exact minimum for the turret's rotation.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number
                                for the limit.

                                Parameters:
                                    0: <CONFIG> - The config path of the turret base set
                                    1: <OBJECT> - The turret
                                    2: <OBJECT> - The gunner
                                    3: <NUMBER[]> - The turret's default limits `[minTurn, maxTurn, minElev, maxElev]`

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set
                        
                        Default:
                            - Whatever the default limit is for the specific turret.

                        Examples:
                            (begin example)
                                minRotation = -45;
                            (end)

                            (begin example)
                                minRotation = "params ['_config','_turret','_gunner','_defaultLimits']; -45";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // maxRotation = 0;


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
                    // numberOfUnits = -1;


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
                                    1: <NUMBER> - The number of units that will spawn

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
                                unitsPerGroup = "params ['_setConfig','_numberOfUnits']; (count _numberOfUnits) / 2";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // unitsPerGroup = -1;


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


        class agents
        {
            class sets
            {
                class agentSpawnSet_1
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
                                    0: <CONFIG> - The config path of the agent base set
                                    1: <OBJECT[] | (PositionATL[] | PositionAGL[])[]> - The possible spawn positions

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - agent Section
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
                            - onUnitsCreated: <STRING> - Code that will be compiled and run after units
                            in the set have been initialized.

                                Parameters:
                                    0: <CONFIG> - The config path of the agent base set
                                    1: <OBJECT[]> - The units created for the agent set

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                onUnitsCreated = "params ["_agentSetConfig","_units"]; hint str _this;";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onUnitsCreated = "";


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
            class sets
            {
                class patrol_1
                {
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - specificSpawn: <STRING | PositionATL[] | PositionAGL[]> - The spawn place
                            of the patrol, use when only a single spawn position is required. 
                            Has precedence over `spawnPositions`.

                            STRING:
                                Uncompiled code that will run that must return an object, PositionATL[],
                                or PositionAGL[] (if over water).

                                Parameters:
                                    0: <CONFIG> - The config path of the patrol set

                            ARRAY:
                                Array must be of positions in the format PositionATL[] or PositionAGL[] 
                                (if over water).

                        Required: 
                            - YES

                        Definition Levels:
                            - Section Set

                        Examples:
                            (begin example)
                                specificSpawn = "params ["_patrolSetConfig"]; missionNameSpace getVariable 'myPatrolSpawnObject'";
                            (end)

                            (begin example)
                                specificSpawn[] = {0,0,0};
                            (end)
                    ------------------------------------------------------------------------------- */
                    // specificSpawn = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - spawnPositions: <STRING | (PositionATL[] | PositionAGL[])[]> - The positions 
                            that the patrol can spawn at. Final position will be randomly selected.
                            Should `specificSpawn` be defined, it will be used instead.
                            
                            STRING:
                                The name of a mission layer that contains objects that will be used as possible 
                                spawn positions for the units.

                            ARRAY:
                                Array must be of positions in the format PositionATL[] or PositionAGL[] 
                                (if over water). This array can also be weighted or unweighted.

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
                                    {1,2,3}
                                };
                            (end)
                            
                            (begin example)
                                // weighted 
                                spawnPositions[] = {
                                    {0,0,0}, 1
                                    {1,2,3}, 0.5
                                };
                            (end)
                    ------------------------------------------------------------------------------- */
                    // spawnPositions = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - numberOfUnits: <NUMBER | STRING> - The number of units in total to spawn. Can't exceed the
                            number of `spawnPositions`. If a negative number, all positions will be used.

                            NUMBER:
                                The number of units.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number.

                                Parameters:
                                    0: <CONFIG> - The config path of the patrol base set
                                    1: <OBJECT[] | (PositionATL[] | PositionAGL[])[]> - The possible spawn positions

                        Required: 
                            - YES

                        Definition Levels:
                            - Base Root
                            - Patrol Section
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
                            - onPartrolCreated: <STRING> - Code that will be compiled and run after units
                            in the partol set have been initialized.

                                Parameters:
                                    0: <CONFIG> - The config path of the patrol set
                                    1: <OBJECT[]> - The units created for the partrol set
                                    2: <GROUP> - The patrol group to which all the units belong

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                onPartrolCreated = "params ["_patrolSetConfig","_units","_group"]; hint str _this;";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onPartrolCreated = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - behaviour: <STRING> - Determines the patrol group's waypoint behaviour
                            setting. Used with `setWaypointBehaviour` command.

                            Options:
                                - "UNCHANGED"
                                - "CARELESS"
                                - "SAFE"
                                - "AWARE"
                                - "COMBAT"
                                - "STEALTH"

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"SAFE"`

                        Examples:
                            (begin example)
                                behaviour = "SAFE";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // behaviour = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - speed: <STRING> - Determines the patrol group's waypoint speed setting. 
                            Used with `setWaypointSpeed` command.

                            Options:
                                - "UNCHANGED"
                                - "LIMITED"
                                - "NORMAL"
                                - "FULL"

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"LIMITED"`

                        Examples:
                            (begin example)
                                behaviour = "LIMITED";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // speed = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - combatMode: <STRING> - Determines the patrol group's waypoint combatMode 
                            setting. Used with `setWaypointCombatMode` command.

                            Options:
                                - "NO CHANGE"
                                - "BLUE"
                                - "GREEN"
                                - "WHITE"
                                - "YELLOW"
                                - "RED"

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"RED"`

                        Examples:
                            (begin example)
                                combatMode = "RED";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // combatMode = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - formation: <STRING> - Determines the patrol group's waypoint formation 
                            setting. Used with `setWaypointFormation` command.

                            Options:
                                - "NO CHANGE"
                                - "COLUMN"
                                - "STAG COLUMN"
                                - "WEDGE"
                                - "ECH LEFT"
                                - "ECH RIGHT"
                                - "VEE"
                                - "LINE"
                                - "FILE"
                                - "DIAMOND"

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"STAG COLUMN"`

                        Examples:
                            (begin example)
                                formation = "STAG COLUMN";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // formation = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - patrolType: <STRING> - Determines how the patrol's waypoints are created.

                            Options:
                                - "GENERATED" - Generates a random set of waypoints around a given center
                                position.
                                - "DEFINED" - Will select from given list of possible partol points.

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"GENERATED"`

                        Examples:
                            (begin example)
                                patrolType = "DEFINED";
                            (end)
                    ------------------------------------------------------------------------------- */
                    patrolType = "GENERATED";

                    
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - numberOfPoints: <NUMBER> - The number of patrol waypoints that will be created.

                        PatrolType:
                            - "GENERATED" - The number of random positions generated within the given radius.
                            - "DEFINED" - The number of waypoint positions that will be selected from
                            the provided list. `-1` can be used to have every possible positions used.

                        Required: 
                            - NO

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `-1` for "DEFINED" patrols, `5` for "GENERATED" patrols

                        Examples:
                            (begin example)
                                numberOfPoints = 5;
                            (end)
                    ------------------------------------------------------------------------------- */
                    numberOfPoints = 5;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - waypointType: <STRING> - The type of waypoints created to patrol. See
                            `setWaypointType` command options.

                        Required: 
                            - NO

                        PatrolType:
                            - "GENERATED"

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `"MOVE"`

                        Examples:
                            (begin example)
                                waypointType = "SAD";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // waypointType = "MOVE";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - patrolPointOrder: <`0` | `1` | `2`> - How to order the patrol points defined
                            in `patrolPoints` property.
                        
                        Options:
                            - 0: order defined
                            - 1: randomized order
                            - 2: order by object name numeric. If a using mission layer syntax for 
                            `patrolPoints`, the patrol points will be sorted by object name ending numeric.
                            Each object must end in `_*number*` such as: `patrolPoint_1` and `patrolPoint_2`.
                            The `_1` point would come before the `_2` point. See `KISKA_fnc_sortStringsNumerically`
                            for details.

                        Required: 
                            - NO

                        PatrolType:
                            - "DEFINED"

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default: 
                            - `0`

                        Examples:
                            (begin example)
                                patrolPointOrder = 0;
                            (end)
                    ------------------------------------------------------------------------------- */                    
                    // patrolPointOrder = -1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - patrolPoints: <STRING | PositionATL[][]> - The positions that the patrol 
                            can select from when using a "DEFINED" `patrolType`.
                            
                            STRING:
                                The name of a mission layer that contains objects that will be used as 
                                possible patrol points.

                            ARRAY:
                                An array of positions that must be in the format PositionATL[]. This 
                                array can be weighted or unweighted.

                        Required: 
                            - YES

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Examples:
                            (begin example)
                                patrolPoints = "myLayerWithObjects";
                            (end)
                            
                            (begin example)
                                // unweighted 
                                patrolPoints[] = {
                                    {0,0,0},
                                    {1,2,3}
                                };
                            (end)
                            
                            (begin example)
                                // weighted 
                                patrolPoints[] = {
                                    {0,0,0}, 1
                                    {1,2,3}, 0.5
                                };
                            (end)
                    ------------------------------------------------------------------------------- */
                    // patrolPoints[] = {};


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - center: <STRING | PositionATL[][]> - The center around which a given patrol
                            will have its waypoints generated.
                            
                            STRING:
                                Uncompiled code that will be compiled and run. Must return a PositionATL[].

                                Parameters:
                                    0: <CONFIG> - The config path of the patrol set

                            ARRAY:
                                An array of positions that must be in the format PositionATL[]. This 
                                array can be weighted or unweighted.

                        Required: 
                            - NO

                        PatrolType:
                            - "GENERATED"

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - The spawn position of the patrol.

                        Examples:
                            (begin example)
                                center = "params ['_patrolSetConfig']; [0,0,0]";
                            (end)
                            
                            (begin example)
                                // unweighted 
                                center[] = {
                                    {0,0,0},
                                    {1,2,3}
                                };
                            (end)
                            
                            (begin example)
                                // weighted 
                                center[] = {
                                    {0,0,0}, 1
                                    {1,2,3}, 0.5
                                };
                            (end)
                    ------------------------------------------------------------------------------- */
                    // center[] = {};


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - center: <STRING | PositionATL[][]> - The furthest radius from the `center` 
                            that waypoints possibly will be generated for the patrol.

                        Required: 
                            - NO

                        PatrolType:
                            - "GENERATED"

                        Definition Levels:
                            - Patrol Section
                            - Section Set

                        Default:
                            - `500`

                        Examples:
                            (begin example)
                                radius = 500;
                            (end)

                    ------------------------------------------------------------------------------- */
                    radius = 500;
                };
            };
        };


        class landVehicles
        {
            class sets
            {
                class vehicleSet_1
                {
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - spawnPositions: <STRING | (PositionATL[] | PositionAGL[])[]> - The positions 
                            that the vehicles can spawn at. Final positions will be randomly selected from the results.
                            
                            STRING:
                                The name of a mission layer that contains objects that will be used as possible 
                                spawn positions for the vehicles. Vehicles will face the same direction as a given 
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
                                    {0,0,0,180} // vehicle will face 180 degrees
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
                            - vehicleClassNames: <STRING | STRING[]> - The classNames of vehicles that can be spawned.

                            STRING:
                                A script that is compiled once and must return an array of classNames 
                                (weighted or unweighted) to choose from.

                                Parameters:
                                    0: <CONFIG> - The config path of the vehicles set

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
                                vehicleClassNames = "['B_HMG_01_high_F', 'B_GMG_01_high_F']";
                            (end)

                            (begin example)
                                // will select randomly from two classNames
                                vehicleClassNames[] = {"B_HMG_01_high_F", "B_GMG_01_high_F"};
                            (end)

                            (begin example)
                                // weighted
                                vehicleClassNames[] = {"B_HMG_01_high_F", 1, "B_GMG_01_high_F", 0.5};
                            (end)
                    ------------------------------------------------------------------------------- */
                    vehicleClassNames[] = {};


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - numberOfVehicles: <NUMBER | STRING> - The number of vehicles to spawn. Can't exceed the
                            number of `spawnPositions`. If a negative number, all vehicle spawn positions will be used.

                            NUMBER:
                                The number of vehicles.
                            
                            STRING:
                                Uncompiled code that will be compiled and executed. Must return a number.

                                Parameters:
                                    0: <CONFIG> - The config path of the vehicle base set
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
                                numberOfVehicles = -1;
                            (end)

                            (begin example)
                                numberOfVehicles = -1;
                            (end)

                            (begin example)
                                numberOfVehicles = "params ['_config','_spawnPositions']; count _spawnPositions";
                            (end)
                    ------------------------------------------------------------------------------- */
                    numberOfVehicles = -1;


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - canPath: <`0` | `1`> - Adjusts whether the DRIVER of the vehicle has its pathing
                            AI enabled.

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
                            - onVehicleCreated: <STRING> - Uncompiled code that will be compiled and executed
                            immediatley after vehicle is created.

                            Parameters:
                                0: <CONFIG> - The config path of the vehicle base set
                                1: <OBJECT> - the created vehicle
                                2: <ARRAY> - An array containing the vehicle's crew
                                4: <GROUP> - The crew's group

                        Required: 
                            - NO

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                onVehicleCreated = "params ['_config','_vehicle','_crew','_crewGroup']; hint str _vehicle";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // onVehicleCreated = "";


                    /* -------------------------------------------------------------------------------
                        Description: 
                            - vehicleClassNames: <STRING | STRING[]> - The units that will make up the vehicle's
                            crew. Units are moved in the order that they appear in the array using `moveInAny`, see 
                            KISKA_fnc_spawnVehicle for more details.

                            STRING:
                                A script that is compiled once and must return an array of classNames and/or unit
                                objects.

                                Parameters:
                                    0: <CONFIG> - The config path of the vehicles set

                            STRING[]:
                                An array of unit classNames that will be used to create the vehicles crew.

                        Required: 
                            - YES

                        Definition Levels:
                            - Base Root
                            - Base Section
                            - Section Set

                        Examples:
                            (begin example)
                                crew[] = {
                                    "B_crew_F", // driver class
                                    "B_crew_F", // commander class
                                    "B_crew_F" // gunner class
                                    //... etc.
                                };
                            (end)

                            (begin example)
                                crew = "params ['_config']; ['B_crew_F',SomeUnitThatIsAlreadyCreated]"
                            (end)
                    ------------------------------------------------------------------------------- */
                    crew[] = {};
                };
            };
        };

        // TODO: update documentation comments
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

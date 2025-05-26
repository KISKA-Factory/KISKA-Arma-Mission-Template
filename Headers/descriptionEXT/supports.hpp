INCLUDE_IF_HAS("\Kiska_Functions\Headers\Support Framework\CommonSupportConfigMacros.hpp")

#if __has_include("\Kiska_Functions\Headers\Support Framework\CommonCommMenuSupportTemplates.hpp")
    // import KISKA_abstract_commMenuArty from KISKA_supports;
    // import KISKA_support_commMenu_155Arty_template from KISKA_supports;
    // import KISKA_support_commMenu_120Arty_template from KISKA_supports;
    // import KISKA_support_commMenu_82Mortar_template from KISKA_supports;
    // import KISKA_support_commMenu_230Arty_template from KISKA_supports;

    // import KISKA_abstract_commMenuCloseAirSupport from KISKA_supports;
    // import KISKA_support_commMenu_gunRun_template from KISKA_supports;
    // import KISKA_support_commMenu_gunsRockets_template from KISKA_supports;
    // import KISKA_support_commMenu_bombs_template from KISKA_supports;
    // import KISKA_support_commMenu_napalm_template from KISKA_supports;

    // import KISKA_abstract_commMenuHelicopterCAS from KISKA_supports;
    
    // import KISKA_abstract_commMenuSupplyDrop from KISKA_supports;
#endif

class KISKA_abstract_commMenuSupport
{
    class KISKA_commMenuDetails
    {
        /* -------------------------------------------------------------------------------
            Description: 
                - text: <STRING> - The text that will appear in the commanding menu selection
                    when selecting a support.

            Required: 
                - YES

            Examples:
                (begin example)
                    text = "Custom Support";
                (end)
        ------------------------------------------------------------------------------- */
        text = "My Support";

        /* -------------------------------------------------------------------------------
            Description: 
                - icon: <STRING> - A path to an icon that will display in the communication
                    menu support pane.

            Required: 
                - NO

            Examples:
                (begin example)
                    icon = CALL_ICON;
                (end)
        ------------------------------------------------------------------------------- */
        icon = CALL_ICON;

        /* -------------------------------------------------------------------------------
            Description: 
                - onSupportSelected: <STRING> - Uncompiled code that will be compiled and executed
                immediatley after the support is added. Only executed on the local machine.
                Most commonly will be used with `KISKA_fnc_commMenu_onSupportAdded`.
                See `KISKA_fnc_supports_add` for further detail.

                Parameters:
                    0: <STRING> - The id of the added support.
                    1: <CONFIG> - The top level config of the support, meaning the parent of 
                        this `KISKA_supportDetails` class.
                    2: <NUMBER> - How many uses the support currently has left.
                    3: <PositionASL[]> - The targetted position of the support.
                    4: <NUMBER> - How many uses of the support were used in the call.
                    5: <BOOL> - Whether or not the support was selected while the player
                        was in the map (`false`) or outside of it (`true`).
                    6: <OBJECT> - The player's `cursortTarget` when they selected the support.

            Required: 
                - YES

            Examples:
                (begin example)
                    onSupportSelected = "_this call KISKA_fnc_commMenu_openArty";
                (end)
        ------------------------------------------------------------------------------- */
        onSupportSelected = "";
        
        /* -------------------------------------------------------------------------------
            Description: 
                - enableExpression: <STRING> - An expression to determine if the support
                    can be initially selected from the communication menu.

                    see https://community.bistudio.com/wiki/Arma_3:_Communication_Menu#Simple_expressions

            Required: 
                - NO

            Examples:
                (begin example)
                    enableExpression = "cursorOnGround";
                (end)
        ------------------------------------------------------------------------------- */
        // enableExpression = "1";

        /* -------------------------------------------------------------------------------
            Description: 
                - cursor: <STRING> - A path to an icon that will display when the communication
                    menu is open an a support item is selected.

            Required: 
                - NO

            Examples:
                (begin example)
                    cursor = "\a3\Ui_f\data\IGUI\Cfg\Cursors\iconCursorSupport_ca.paa";
                (end)
        ------------------------------------------------------------------------------- */
        // cursor = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - iconText: <STRING> - Text to appear with the icon.

            Required: 
                - NO

            Examples:
                (begin example)
                    iconText = "something";
                (end)
        ------------------------------------------------------------------------------- */
        // iconText = "";
    };

    // Governs the support framework interaction
    // This is an essential class
    class KISKA_supportDetails
    {
        /* -------------------------------------------------------------------------------
            Description: 
                - numberOfUses: <NUMBER> - The number of "uses" that the support has in total.
                    For things like artillery, it could correspond to how many rounds in
                    total can be fired.

            Required: 
                - YES

            Examples:
                (begin example)
                    numberOfUses = 1;
                (end)
        ------------------------------------------------------------------------------- */
        numberOfUses = 1;

        /* -------------------------------------------------------------------------------
            Description: 
                - onSupportAdded: <STRING> - Uncompiled code that will be compiled and executed
                immediatley after the support is added. Only executed on the local machine.
                Most commonly will be used with `KISKA_fnc_commMenu_onSupportAdded`.
                See `KISKA_fnc_supports_add` for further detail.

                Parameters:
                    0: <STRING> - The id of the added support.
                    1: <CONFIG> - The top level config of the support, meaning the parent of 
                        this `KISKA_supportDetails` class.
                    2: <NUMBER> - How many uses the support currently has left.

            Required: 
                - NO

            Examples:
                (begin example)
                    onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";
                (end)
        ------------------------------------------------------------------------------- */
        onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";

        /* -------------------------------------------------------------------------------
            Description: 
                - onSupportRemoved: <STRING> - Uncompiled code that will be compiled and executed
                immediatley after the support is removed. Only executed on the local machine.
                Most commonly will be used with `KISKA_fnc_commMenu_onSupportRemoved`.
                See `KISKA_fnc_supports_remove` for further detail.

                Parameters:
                    0: <STRING> - The id of the removed support.
                    1: <CONFIG> - The top level config of the support, meaning the parent of 
                        this `KISKA_supportDetails` class.

            Required: 
                - YES

            Examples:
                (begin example)
                    onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";
                (end)
        ------------------------------------------------------------------------------- */
        onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";

        /* -------------------------------------------------------------------------------
            Description: 
                - onSupportCalled: <STRING> - Uncompiled code that will be compiled and executed
                immediatley after the support is called. Only executed on the local machine.
                This should handle the producing the actual effect of the support like launching
                artillery shells or conducting an aircraft to shoot, etc.

                See `KISKA_fnc_supports_call` for further detail.

                Parameters:
                    0: <ANY> - Whatever arguments are passed to `KISKA_fnc_supports_call` as the
                        on called args.
                    1: <STRING> - The id of the called support.
                    2: <CONFIG> - The top level config of the support, meaning the parent of 
                        this `KISKA_supportDetails` class.
                    3: <PositionASL[]> - The targetted position of the support.
                    4: <NUMBER> - How many uses of the support were used in the call.

            Required: 
                - YES

            Examples:
                (begin example)
                    onSupportCalled = "_this call KISKA_fnc_supports_onCalledVirtualArty";
                (end)
        ------------------------------------------------------------------------------- */
        onSupportCalled = "";

        /* -------------------------------------------------------------------------------
            Description: 
                The AddedNotifcation class defines a `KISKA_fnc_showNotification` compatible
                class that will be shown when the given support is added to the player with
                `KISKA_fnc_supports_add`. See `KISKA_fnc_showNotification` for further details
                on class implementation.

            Required: 
                - NO

            Examples:
                (begin example)
                    class AddedNotifcation
                    {
                        title = "Support Added";
                        duration = 3;
                        description = "A support has been added to your menu";
                        iconPicture = CALL_ICON;
                    };
                (end)
        ------------------------------------------------------------------------------- */
        // class AddedNotifcation
        // {
        // };
    };

    // Governs interaction with the KISKA support manager
    // If the support is not intended for use in it, remove the class
    class KISKA_supportManagerDetails
    {
        /* -------------------------------------------------------------------------------
            Description: 
                - text: <STRING> - The text that will appear in the KISKA Support manager
                    lists for this support.

            Required: 
                - YES

            Examples:
                (begin example)
                    text = "Custom Support";
                (end)
        ------------------------------------------------------------------------------- */
        text = "My Support";

        /* -------------------------------------------------------------------------------
            Description: 
                - picture: <STRING> - A path to an icon that will display to the left of the
                    text in the Support Manager.

            Required: 
                - NO

            Examples:
                (begin example)
                    picture = CALL_ICON;
                (end)
        ------------------------------------------------------------------------------- */
        picture = CALL_ICON;

        /* -------------------------------------------------------------------------------
            Description: 
                - pictureColor: <ARRAY> - An array of RGBA that will determine what color
                    the support is in the manager (when it has not been used before).

            Required: 
                - NO

            Examples:
                (begin example)
                    pictureColor[] = {1,0,1,1};
                (end)
        ------------------------------------------------------------------------------- */
        // pictureColor[] = {};

        /* -------------------------------------------------------------------------------
            Description: 
                - selectedPictureColor: <ARRAY> - An array of RGBA that will determine what color
                    the support is in the manager (when it has not been used before) and it
                    is currently selected in a listbox.

            Required: 
                - NO

            Examples:
                (begin example)
                    selectedPictureColor[] = {1,0,1,1};
                (end)
        ------------------------------------------------------------------------------- */
        // selectedPictureColor[] = {};

        /* -------------------------------------------------------------------------------
            Description: 
                - tooltip: <STRING> - Tooltip text that will appear when hovering over
                    a support of this class in the manager.

            Required: 
                - NO

            Examples:
                (begin example)
                    tooltip = "hello tooltip";
                (end)
        ------------------------------------------------------------------------------- */
        // tooltip = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - managerCondition: <STRING> - Code that will be compiled and run when
                    a player attempts to take the support from the support manager.
                    Must return a <BOOL>, `true` means that the user can take the support,
                    `false` means that they cant.

                    Parameters:
                        0: <CONFIG> - The parent config above the KISKA_supportManagerDetails

            Required: 
                - NO

            Examples:
                (begin example)
                    managerCondition = "params ["_supportConfig"]; true";
                (end)
        ------------------------------------------------------------------------------- */
        // managerCondition = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - conditionMessage: <STRING> - A message that will appear when the attempting
                    to take the support results in a failure. A default message is used in
                    the event this is undefined or `""`.

            Required: 
                - NO

            Examples:
                (begin example)
                    conditionMessage = "You cant take the support";
                (end)
        ------------------------------------------------------------------------------- */
        // conditionMessage = "";
    };
};





class KISKA_example_155arty
{
    class KISKA_commMenuDetails
    {
        text = "Artillery Example";
        icon = ARTILLERY_ICON;
        onSupportSelected = "_this call KISKA_fnc_commMenu_openArty";

        /* -------------------------------------------------------------------------------
            Description: 
                - canSelectRounds: <NUMBER> - Determines whether or not a user can select
                    the number of rounds they would like to fire for the artillery. If
                    off, all the `numberOfUses` will be expended on one call. `0` means`
                    no, `1` means yes.

            Required: 
                - NO

            Default:
                - `1`

            Examples:
                (begin example)
                    canSelectRounds = 0; // cant select
                (end)
        ------------------------------------------------------------------------------- */
        canSelectRounds = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - draw3dMarker: <NUMBER> - Determines whether or not a user will see

            Required: 
                - NO

            Default:
                - `0`

            Examples:
                (begin example)
                    draw3dMarker = 0; // No 3d marker
                (end)
        ------------------------------------------------------------------------------- */
        draw3dMarker = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - radiuses: <NUMBER[]> - Provides the list of selectable radiuses of spread
                    for the artillery fire.

            Required: 
                - NO

            Examples:
                (begin example)
                    radiuses[] = {100};
                (end)
        ------------------------------------------------------------------------------- */
        radiuses[] = {50,100};

        /* -------------------------------------------------------------------------------
            Description: 
                - ammoTypes: <[STRING,STRING][]> - Provides the list of selectable ammos 
                    and their labels.

            Required: 
                - NO

            Examples:
                (begin example)
                    ammoTypes[] = {
                        AMMO_155_HE,
                        AMMO_155_CLUSTER,
                        AMMO_155_MINES,
                        AMMO_155_ATMINES
                    };
                (end)
        ------------------------------------------------------------------------------- */
        ammoTypes[] = {
            {"155mm - HE","Sh_155mm_AMOS"},
            {"155mm - Cluster","Cluster_155mm_AMOS"},
            AMMO_155_MINES,
            AMMO_155_ATMINES
        };
    };
    
    class KISKA_supportDetails
    {
        numberOfUses = 10;
        onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";
        onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";
        onSupportCalled = "_this call KISKA_fnc_supports_onCalledVirtualArty";
    };

    class KISKA_supportManagerDetails
    {
        picture = ARTILLERY_ICON;
        text = "Artillery Example";
    };
};




class KISKA_example_CAS
{
    class KISKA_commMenuDetails
    {
        text = "CAS Example";
        icon = CAS_ICON;
        onSupportSelected = "_this call KISKA_fnc_commMenu_openCas";
        draw3dMarker = ON;
        
        /* -------------------------------------------------------------------------------
            Description: 
                - canSelectIngress: <NUMBER> - Determines whether or not a user 
                    can select the bearing that the aircraft will ingress at. The default
                    behavior will be the the direction the player is currently facing.

            Required: 
                - NO

            Examples:
                (begin example)
                    canSelectIngress = 0; // cant select
                (end)

                (begin example)
                    canSelectIngress = 1; // can select
                (end)
        ------------------------------------------------------------------------------- */
        canSelectIngress = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - aircraftClass: <STRING> - The classname of the aircraft to perform the CAS

            Required: 
                - YES

            Examples:
                (begin example)
                    aircraftClass = "B_Plane_CAS_01_dynamicLoadout_F";
                (end)
        ------------------------------------------------------------------------------- */
        aircraftClass = "B_Plane_CAS_01_dynamicLoadout_F";

        /* -------------------------------------------------------------------------------
            Description: 
                The AttackTypes class defines an individual set of arguments for how a 
                given CAS strike could be conducted. Each subclass is expected to contain
                the possible arguments and will be presented as a selectable option.

            Required: 
                - YES

            Examples:
                (begin example)
                    // User can choose between both attack types
                    class AttackTypes
                    {
                        class GunRun100
                        {
                            label = "Gun Run 100 rounds";
                            allowDamage = OFF;
                            class FireOrders
                            {
                                class gun
                                {
                                    weapon = "Gatling_30mm_Plane_CAS_01_F";
                                    numberOfTriggerPulls = 100;
                                    strafeIncrement = 0.1;
                                };
                            };
                        };

                        class GunRun200 : GunRun100
                        {
                            label = "Gun Run 200 rounds";
                            class FireOrders : FireOrders
                            {
                                class gun : gun
                                {
                                    numberOfTriggerPulls = 200;
                                };
                            };
                        };
                    };
                (end)
        ------------------------------------------------------------------------------- */
        class AttackTypes
        {
            class GunRun
            {
                /* -------------------------------------------------------------------------------
                    Description: 
                        - label: <STRING> - The selection label for this attack type that will appear
                            in the commanding menu.

                    Required: 
                        - YES

                    Examples:
                        (begin example)
                            label = "My Attack Type";
                        (end)
                ------------------------------------------------------------------------------- */
                label = "Gun Run";

                /* -------------------------------------------------------------------------------
                    Description: 
                        - canSelectAttackDirection: <NUMBER> - Determines whether or not a user 
                            can select the bearing that the aircraft will ingress at. The default
                            behavior will be the the direction the player is currently facing.

                    Required: 
                        - NO

                    Examples:
                        (begin example)
                            canSelectAttackDirection = 0; // cant select
                        (end)

                        (begin example)
                            canSelectAttackDirection = 1; // can select
                        (end)
                ------------------------------------------------------------------------------- */
                allowDamage = OFF;

                /* -------------------------------------------------------------------------------
                    Description: 
                        

                    Required: 
                        - YES

                    Examples:
                        (begin example)
                            // Will fire guns and then rockets
                            class FireOrders
                            {
                                class gun
                                {
                                    weapon = "Gatling_30mm_Plane_CAS_01_F";
                                    numberOfTriggerPulls = 100;
                                    strafeIncrement = 0.1;
                                };
                                class RocketPod
                                {
                                    weapon = "pylon";
                                    mag = "PylonRack_7Rnd_Rocket_04_HE_F";
                                    numberOfTriggerPulls = 7;
                                    timeBetweenShots = 0.5;
                                    weaponProfile = "guide_to_strafe_target";
                                    strafeIncrement = 0.01;
                                };
                            };
                        (end)
                ------------------------------------------------------------------------------- */
                class FireOrders
                {
                    class ExampleOrder
                    {
                        /* -------------------------------------------------------------------------------
                            Description: 
                                - weapon: <STRING> - The classname of the weapon to fire. In the even that
                                    a pylon weapon is to be added, set the weapon to `"pylon"`.

                            Required: 
                                - YES

                            Examples:
                                (begin example)
                                    weapon = "pylon";
                                    mag = "PylonRack_7Rnd_Rocket_04_HE_F";
                                (end)

                                (begin example)
                                    weapon = "Gatling_30mm_Plane_CAS_01_F";
                                (end)
                        ------------------------------------------------------------------------------- */
                        weapon = "Gatling_30mm_Plane_CAS_01_F";

                        /* -------------------------------------------------------------------------------
                            Description: 
                                - mag: <STRING> - The classname of the magazine to use with the provided 
                                    weapon. If undefined or an empty string, the default magazine for the
                                    weapon will be used.

                            Required: 
                                - NO

                            Default:
                                - `""`

                            Examples:
                                (begin example)
                                    weapon = "pylon";
                                    mag = "PylonRack_7Rnd_Rocket_04_HE_F";
                                (end)

                                (begin example)
                                    mag = "";
                                (end)
                        ------------------------------------------------------------------------------- */
                        // mag = "";

                        /* -------------------------------------------------------------------------------
                            Description: 
                                - numberOfTriggerPulls: <NUMBER> - The number of trigger pulls. If less than 0, 
                                    the number of pulls will correspond to whatever the magazine's `count` value
                                    is as defined in the `configFile >> "CfgMagazine" >> {{mag}}`

                            Required: 
                                - NO

                            Default:
                                - `-1`

                            Examples:
                                (begin example)
                                    numberOfTriggerPulls = 200;
                                (end)

                                (begin example)
                                    // use defined amount in CfgMagazine "count" value
                                    numberOfTriggerPulls = -1; 
                                (end)
                        ------------------------------------------------------------------------------- */
                        numberOfTriggerPulls = 200; 

                        /* -------------------------------------------------------------------------------
                            Description: 
                                - timeBetweenShots: <NUMBER> - The time to wait between trigger pulls.

                            Required: 
                                - NO
                            
                            Default:
                                - `0.05`

                            Examples:
                                (begin example)
                                    timeBetweenShots = 1;
                                (end)
                        ------------------------------------------------------------------------------- */
                        // timeBetweenShots = 0.05;

                        /* -------------------------------------------------------------------------------
                            Description: 
                                - weaponProfile: <STRING> - Either `"guide_to_original_target"`, `"guide_to_strafe_target"`, or `""`.
                                    `guide_to_original_target` will guide each round of the weapon fired directly to the
                                    attack position specified. `guide_to_strafe_target` will guide each round onto the
                                    stafing target giving the illusion of strafing. Leave empty if no guidance is necessary.
                                    This can be performance intensive.

                            Required: 
                                - NO
                            
                            Default:
                                - `""`

                            Examples:
                                (begin example)
                                    // guides projectiles along the aircraft nose position
                                    weaponProfile = "guide_to_original_target";
                                (end)

                                (begin example)
                                    // guides projectiles along the aircraft nose position
                                    weaponProfile = "guide_to_strafe_target";
                                (end)
                        ------------------------------------------------------------------------------- */
                        // weaponProfile = "";

                        /* -------------------------------------------------------------------------------
                            Description: 
                                - strafeIncrement: <STRING> - For every 0.01 seconds the aircraft is firing these munitions,
                                    how much space should there be added to the aicraft's nose position? This
                                    will help with strafing a target.

                            Required: 
                                - NO
                            
                            Default:
                                - `0`

                            Examples:
                                (begin example)
                                    strafeIncrement = 0.1;
                                (end)
                        ------------------------------------------------------------------------------- */
                        // strafeIncrement = 0;
                    };
                };
            }; 
        };
    };

    class KISKA_supportDetails
    {
        numberOfUses = 1;
        onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";
        onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";
        onSupportCalled = "_this call KISKA_fnc_supports_onCalledCloseAirSupport";
    };

    class KISKA_supportManagerDetails
    {
        text = "CAS Example";
        picture = CAS_ICON;
    };
};






class KISKA_example_helicopterCAS
{
    class KISKA_commMenuDetails
    {
        text = "Helicopter CAS Example";
        icon = CAS_HELI_ICON;
        onSupportSelected = "_this call KISKA_fnc_commMenu_openHelicopterCAS";
        draw3dMarker = ON;
        canSelectIngress = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - aircraftClass: <STRING> - The classname of the aircraft to perform the CAS

            Required: 
                - YES

            Examples:
                (begin example)
                    aircraftClass = "B_Heli_Attack_01_dynamicLoadout_F";
                (end)
        ------------------------------------------------------------------------------- */
        aircraftClass = "B_Heli_Attack_01_dynamicLoadout_F";

        /* -------------------------------------------------------------------------------
            Description: 
                - patrolRadiuses: <NUMBER[]> - A list of options to select the radius that
                    the helicopter will patrol around.

            Required: 
                - NO

            Default:
                - `200`

            Examples:
                (begin example)
                    patrolRadiuses[] = { 200 };
                (end)
        ------------------------------------------------------------------------------- */
        // patrolRadiuses[] = {};

        /* -------------------------------------------------------------------------------
            Description: 
                - patrolAltitudes: <NUMBER[]> - A list of options to select the altitude at
                    which the helicopter will conduct its patrol above ground level.

            Required: 
                - NO

            Default:
                - `50`

            Examples:
                (begin example)
                    patrolAltitudes[] = { 50 };
                (end)
        ------------------------------------------------------------------------------- */
        // patrolAltitudes[] = {};
    };

    class KISKA_supportDetails
    {
        numberOfUses = 1;
        onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";
        onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";
        onSupportCalled = "_this call KISKA_fnc_supports_onCalledHelicopterGunner";
    };

    class KISKA_supportManagerDetails
    {
        text = "Helicopter CAS Example";
        picture = CAS_HELI_ICON;
    };
};






class KISKA_example_supplyDrop
{
    class KISKA_commMenuDetails
    {
        text = "Supply Drop Example";
        icon = SUPPLY_DROP_ICON;
        onSupportSelected = "_this call KISKA_fnc_commMenu_openSupplyDrop";
        draw3dMarker = ON;

        // only applies if `aircraftClass` is defined
        // canSelectIngress = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - dropAltitudes: <NUMBER[]> - A list of options to select the altitude at
                    which the aircraft will fly and drop the cargo above ground level.

            Required: 
                - NO

            Default:
                - `100`

            Examples:
                (begin example)
                    dropAltitudes[] = { 100 };
                (end)
        ------------------------------------------------------------------------------- */
        // dropAltitudes[] = {};

        /* -------------------------------------------------------------------------------
            Description: 
                - aircraftClass: <STRING> - The classname of an aircraft to fly over the
                    drop zone and perform the simulated drop. If undefined, no aircraft will
                    be created to flyover the drop zone.

            Required: 
                - NO

            Examples:
                (begin example)
                    aircraftClass = "B_T_VTOL_01_vehicle_F";
                (end)
        ------------------------------------------------------------------------------- */
        // aircraftClass = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - spawnDistance: <NUMBER> - The distance an aircraft will spawn from the drop
                    zone and fly in. Only applies if `aircraftClass` is defined.

            Required: 
                - NO

            Default:
                - `2000`

            Examples:
                (begin example)
                    spawnDistance = 1000;
                (end)
        ------------------------------------------------------------------------------- */
        // spawnDistance = 2000;

        /* -------------------------------------------------------------------------------
            Description: 
                - objectClassNames: <STRING[]> - A list of classnames of objects that will
                    be dropped.

            Required: 
                - YES

            Examples:
                (begin example)
                    // drop two supply crates
                    objectClassNames[] = {
                        "B_supplyCrate_F",
                        "B_supplyCrate_F"
                    };
                (end)
        ------------------------------------------------------------------------------- */
        objectClassNames[] = {"B_supplyCrate_F"};

        /* -------------------------------------------------------------------------------
            Description: 
                - dropPositionRadius: <NUMBER> - The radius around the drop position that
                    the crates will be created.

            Required: 
                - NO

            Default:
                - `50`

            Examples:
                (begin example)
                    dropPositionRadius = 100;
                (end)
        ------------------------------------------------------------------------------- */
        // dropPositionRadius = 50;

        /* -------------------------------------------------------------------------------
            Description: 
                - parachuteClass: <STRING> - The class name of the parachutes that will
                    be used for the supplies.

            Required: 
                - NO

            Default:
                - `"b_parachute_02_F"`

            Examples:
                (begin example)
                    parachuteClass = "b_parachute_02_F";
                (end)
        ------------------------------------------------------------------------------- */
        // parachuteClass = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - dropZVelocity: <NUMBER> - The m/s rate of descent that
                    will be applied to the parachutes while every `velocityUpdateFrequency`
                    denoted time and if the object is above a surface beneath it as defined
                    with `distanceToStopVelocityUpdates`.

            Required: 
                - NO

            Default:
                - `-15`

            Examples:
                (begin example)
                    dropZVelocity = -10;
                (end)
        ------------------------------------------------------------------------------- */
        // dropZVelocity = -15;

        /* -------------------------------------------------------------------------------
            Description: 
                - velocityUpdateFrequency: <NUMBER> - How frequently to update the dropped 
                    objects' downward velocities.

            Required: 
                - NO

            Default:
                - `0.1`

            Examples:
                (begin example)
                    velocityUpdateFrequency = -0.1;
                (end)
        ------------------------------------------------------------------------------- */
        // velocityUpdateFrequency = -0.1;

        /* -------------------------------------------------------------------------------
            Description: 
                - distanceToStopVelocityUpdates: <NUMBER> - At what distance to the surface
                    beneath the objects should the velocity stop being applied.

            Required: 
                - NO

            Default:
                - `80`

            Examples:
                (begin example)
                    distanceToStopVelocityUpdates = 100;
                (end)
        ------------------------------------------------------------------------------- */
        // distanceToStopVelocityUpdates = 80;

        /* -------------------------------------------------------------------------------
            Description: 
                - allowDamage: <0 | 1> - Can the dropped supplies take damage?

            Required: 
                - NO

            Default:
                - `1`

            Examples:
                (begin example)
                    // no damage
                    allowDamage = 0;
                (end)
        ------------------------------------------------------------------------------- */
        // allowDamage = ON;

        /* -------------------------------------------------------------------------------
            Description: 
                - addArsenals: <0 | 1> - If true, arsenals will be added to the supplies
                    with `KISKA_fnc_addArsenal`

            Required: 
                - NO

            Default:
                - `0`

            Examples:
                (begin example)
                    addArsenals = 1;
                (end)
        ------------------------------------------------------------------------------- */
        // addArsenals = OFF;

        /* -------------------------------------------------------------------------------
            Description: 
                - clearCargo: <0 | 1> - If true, cargo will be cleared automatically from
                    the dropped crates using `KISKA_fnc_clearCargoGlobal`

            Required: 
                - NO

            Default:
                - `0`

            Examples:
                (begin example)
                    clearCargo = 1;
                (end)
        ------------------------------------------------------------------------------- */
        // clearCargo = OFF;
    };

    class KISKA_supportDetails
    {
        numberOfUses = 1;
        onSupportAdded = "_this call KISKA_fnc_commMenu_onSupportAdded";
        onSupportRemoved = "_this call KISKA_fnc_commMenu_onSupportRemoved";
        onSupportCalled = "_this call KISKA_fnc_supports_onCalledSupplyDrop";
    };

    class KISKA_supportManagerDetails
    {
        text = "Supply Drop Example";
        picture = SUPPLY_DROP_ICON;
    };
};
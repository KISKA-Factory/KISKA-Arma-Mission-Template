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
        text = "Artillery - 155mm";
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
        text = "Artillery - 155mm";

    };
};
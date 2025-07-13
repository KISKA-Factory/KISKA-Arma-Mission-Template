// the trait's name will be that of the configName
// meaning, if you want to check for this trait
// use `<UNIT> getUnitTrait "ExampleTrait"`;
class ExampleTrait
{
    // Governs interaction with the KISKA trait manager
    class KISKA_traitManagerDetails
    {
        /* -------------------------------------------------------------------------------
            Description: 
                - text: <STRING> - The text that will appear in the KISKA Trait Manager
                    lists. If undefined or an empty string, the configName of the parent
                    (ExampleTrait) will be used instead

            Required: 
                - NO

            Examples:
                (begin example)
                    text = "My Trait";
                (end)
        ------------------------------------------------------------------------------- */
        // text = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - picture: <STRING> - A path to an icon that will display to the left of the
                    text in the Trait Manager.

            Required: 
                - NO

            Examples:
                (begin example)
                    picture = "some/image.paa";
                (end)
        ------------------------------------------------------------------------------- */
        // picture = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - pictureColor: <ARRAY> - An array of RGBA that will determine what color
                    the trait is in the manager.

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
                    the trait is in the manager and it is currently selected in a listbox.

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
                    a trait of this class in the manager.

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
                    a player attempts to take the trait from the trait manager.
                    Must return a <BOOL>, `true` means that the user can take the trait,
                    `false` means that they cant.

                    Parameters:
                        0: <CONFIG> - The parent config above the KISKA_traitManagerDetails

            Required: 
                - NO

            Examples:
                (begin example)
                    managerCondition = "params ["_traitConfig"]; true";
                (end)
        ------------------------------------------------------------------------------- */
        // condition = "";

        /* -------------------------------------------------------------------------------
            Description: 
                - conditionMessage: <STRING> - A message that will appear when the attempting
                    to take the trait results in a failure. A default message is used in
                    the event this is undefined or `""`.

            Required: 
                - NO

            Examples:
                (begin example)
                    conditionMessage = "You cant take the trait";
                (end)
        ------------------------------------------------------------------------------- */
        // conditionMessage = "";
    };
};


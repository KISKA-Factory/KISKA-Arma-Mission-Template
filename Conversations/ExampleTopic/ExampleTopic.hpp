class ExampleTopic
{
    /* -------------------------------------------------------------------------------
        Description: 
            - bikb: <STRING> - The file path (relative to the mission root folder)
                that points to the .bikb file that corresponds with this given topic.
                The .bikb file contains definitions for each line that can be spoken
                for a given topic/conversation.

        Required:
            - YES
        
        Examples:
            (begin example)
                bikb = "Path\From\Mission\Root\MyKb.bikb";
            (end)
    ------------------------------------------------------------------------------- */
    bikb = "Conversations\ExampleTopic\ExampleTopic.bikb";

    /* -------------------------------------------------------------------------------
        Description: 
            - topicName: <STRING> - The name of the topic to refer to within sqf while
                interacting with knowledgebase (kb) commands. Should be unique. If undefined
                it will default to the topic config's name ("ExampleTopic").

        Required:
            - NO
        
        Examples:
            (begin example)
                topicName = "MyTopic";
            (end)
    ------------------------------------------------------------------------------- */
    // topicName = "";

    /* -------------------------------------------------------------------------------
        Description: 
            The `lines` class should for all intents and purposes be the included .bikb
            file and is defined as such for the sake of being able to reduce the amount
            of duplicated definitions for a given line. It should point to the same file
            as the `bikb` property.

        Required: 
            - YES

        Examples:
            (begin example)
                class lines
                {
                    #include "ExampleTopic.bikb"
                };
            (end)
    ------------------------------------------------------------------------------- */
    class lines 
    {
        #include "ExampleTopic.bikb"
    };

    class conversations
    {
        class ExampleOptionSet
        {
            /* -------------------------------------------------------------------------------
                Description: 
                    - preambleLine: <STRING | STRING[]> - The classname of any lines defined
                        in the conversation's .bikb file that should be played prior to the
                        options being presented to the player. Lines are played in sequential
                        order if defined as an array.

                Required:
                    - NO
                
                Examples:
                    (begin example)
                        preambleLine[] = {
                            "line_1",
                            "line_2"
                        };
                    (end)

                    (begin example)
                        preambleLine = "line_1";
                    (end)
            ------------------------------------------------------------------------------- */
            // preambleLine = "";
            
            /* -------------------------------------------------------------------------------
                Description: 
                    The Options class determines what the player can say to whomever they are speaking
                    to.

                Required: 
                    - YES

                Examples:
                    (begin example)
                        class Options
                        {
                            // player can select between saying "Hello" or "Goodbye"
                            class option_1
                            {
                                text = "Hello.";
                            };
                            class option_2
                            {
                                text = "Goodbye.";
                            };
                        };
                    (end)
            ------------------------------------------------------------------------------- */
            class Options
            {
                class ExampleOption_1
                {
                    /* -------------------------------------------------------------------------------
                        Description: 
                            - text: <STRING> - The text that will show in the option select menu for the
                                given option. In the even that this is undefined or an empty string,
                                one of two things will happen. 
                                
                                - If the `line` property of the option is defined and that line class 
                                has a `subtitle` property defined that is not an empty string, it will 
                                be used.

                                - If the line property's subtitle is undefined or an empty string,
                                the name of the class will be used (e.g. the option will read "ExampleOption_1").


                        Required:
                            - NO
                        
                        Examples:
                            (begin example)
                                text = "line_1";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // text = "";

                    /* -------------------------------------------------------------------------------
                        Description: 
                            - line: <STRING | STRING[]> - The classname of any .bikb defined lines for
                                the player to speak when the option is selected. If defined as an array
                                the lines are spoken in the given order of the array.


                        Required:
                            - NO
                        
                        Examples:
                            (begin example)
                                line = "playerLine_1";
                            (end)

                            (begin example)
                                line[] = {"playerLine_1","playerLine_2"};
                            (end)
                    ------------------------------------------------------------------------------- */
                    // line = "";

                    /* -------------------------------------------------------------------------------
                        Description: 
                            - postLine: <STRING | STRING[]> - The classname of any lines defined
                                in the conversation's .bikb file that should be played after the player 
                                has selected an option and played spoken their lines. Lines are played 
                                in sequential order if defined as an array.


                        Required:
                            - NO
                        
                        Examples:
                            (begin example)
                                postLine[] = {
                                    "line_1",
                                    "line_2"
                                };
                            (end)

                            (begin example)
                                postLine = "line_1";
                            (end)
                    ------------------------------------------------------------------------------- */
                    // postLine = "";

                    /* -------------------------------------------------------------------------------
                        Description: 
                            - nextConvo: <STRING> - The classname the next conversation to open. A conversation
                                being a list of options (`ExampleOptionSet`). These must be within the 
                                same topic. If you want to loop back to the same conversation, set to
                                the same conversation.


                        Required:
                            - NO
                        
                        Examples:
                            (begin example)
                                // loops back to the same conversation
                                nextConvo = "ExampleOptionSet"; 
                            (end)

                            (begin example)
                                nextConvo = "AnotherOptionSetClass"; 
                            (end)
                    ------------------------------------------------------------------------------- */
                    // nextConvo = "";
                };
            };
        };
    };
};
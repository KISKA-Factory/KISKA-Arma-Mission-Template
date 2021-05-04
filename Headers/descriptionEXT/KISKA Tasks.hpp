#define ON 1
#define OFF 0

class KISKA_Tasks
{
    class exampleTask
    {
        title = "";
        description = "";

        parentTask = "";
        type = "";

        // params for these are:
        // 0: task id (or class name) (STRING)
        // 1: config path (CONFIG)
        // 2: task state (STRING)
        onComplete = ""; // code that runs upon completion of task when using KISKA_fnc_endTask
        onCreate = ""; // code that runs on creation of task

        destination[] = {};

        defaultState = "";
        priority = -1;
        notifyOnComplete = ON;
        notifyOnCreate = ON;

        visibleIn3D = OFF;
    };
};

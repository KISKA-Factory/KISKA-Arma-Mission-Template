/*
// expression arguments

[caller, pos, target, is3D, id]
    caller: Object - unit which called the item, usually player
    pos: Array in format Position - cursor position
    target: Object - cursor target
    is3D: Boolean - true when in 3D scene, false when in map
    id: String - item ID as returned by BIS_fnc_addCommMenuItem function
*/

/*
	if a class is to be solely a base one, you need to include _baseClass (EXACTLY AS IT IS CASE SENSITIVE)
	 somewhere in the class name so that it can be excluded from being added to the shop
*/
/*
class basicSupport_baseClass
{
    text = "I'm a support!"; // text in support menu and Shop (DO NOT INCLUDE PRICE HERE, IT IS ADDED IN BLWK_fnc_shop_populateSupportTree)
    subMenu = "";
    expression = ""; // code to compile upon call of menu item
    icon = CALL_ICON; // icon in support menu
    curosr = SUPPORT_CURSOR;
    enable = "1";
    removeAfterExpressionCall = 1;

	// used for support selection menu
    // _this select 0 is the classname
    managerCondition = "";
};
*/

/* -------------------------------------------------------------------------------
    KISKA Cargo are a configuration representation of cargo that can be set
    on a given crate with the KISKA_fnc_containerCargo_* functions.

    One can define a cargo manifest of sorts here and then use KISKA_fnc_containerCargo_set
    to then set the contents of a given container to what they are in this manifest.

    The manifest is broken down into weapons, items, magazines, weapons, and containers.

    The "containers" section are merely any item with the potential of holding other 
    items within them such as backpacks, uniforms, and vests. This section allows one
    to recusively define subcontainers within these containers using the same top level
    layout of the config (see ExampleCargoCrate below). Uniforms and vests can also be defined
    under the "items" section but will not at that point be able to have subcontainers.

    The basic layout is:

    class MyCargoManifest
    {
        class weapons // <---- section
        {
            class arifle_AK12_GL_F // <---- the classname of the item to create
            {
                class EmptyRifle // <---- the name of this does not matter
                {
                    count = 5; // <---- the number of the item with these properties to be added
                };
            };
        };
    };
------------------------------------------------------------------------------- */
class ExampleCargoCrate
{
    class weapons
    {
        class arifle_AK12_GL_F
        {
            class profile_1 
            {
                count = 2;
                primaryMagazine = "30Rnd_762x39_AK12_Mag_F";
                primaryAmmo = 30;
                secondaryAmmo = 1;
                secondaryMagazine = "1Rnd_HE_Grenade_shell";
                optic = "optic_Arco";
                rail = "acc_flashlight";
                muzzle = "muzzle_snds_B_khk_F";
                bipod = "";
            };
        };
    };

    class containers
    {
        class B_Bergen_dgtl_F
        {
            class empty
            {
                count = 1;
            };
            class full
            {
                count = 2;
                class weapons
                {
                    class arifle_AK12_GL_F
                    {
                        class full
                        {
                            count = 1;
                            primaryMagazine = "30Rnd_762x39_AK12_Mag_F";
                            primaryAmmo = 30;
                            secondaryAmmo = 1;
                            secondaryMagazine = "1Rnd_HE_Grenade_shell";
                            optic = "optic_Arco";
                            rail = "acc_flashlight";
                            muzzle = "muzzle_snds_B_khk_F";
                            bipod = "";
                        };
                    };
                };

                class containers
                {
                    class U_B_survival_uniform
                    {
                        class filled
                        {
                            count = 1;
                            class items
                            {
                                class H_Booniehat_mgrn
                                {
                                    count = 1;
                                };
                            };
                        };
                    };
                };
            };
        };

        class U_B_survival_uniform
        {
            class empty
            {
                count = 1;
            };

            class filled
            {
                count = 2;
                class items
                {
                    class H_Booniehat_mgrn
                    {
                        count = 1;
                    };
                };
            };
        };
    };

    class magazines
    {
        class 30Rnd_762x39_AK12_Mag_F
        {
            class full
            {
                count = 30;
            };
            class partial
            {
                count = 10;
                ammo = 10;
            };
        };
    };

    class items
    {
        class ItemRadio
        {
            count = 1;
        };
    };
};
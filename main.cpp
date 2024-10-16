#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h" 
#include "AnimationFile.h"

extern "C"
{
    //registering data functions. - Needs to exist.
    void (*RegisterDataFunc)(void* ptr);

    //register a MotionTable Animation through AnimationFile.h
    AnimationFile* testAnimation;


    //main CWE Load function -- Important stuff like adding your CWE mod goes here
    void CWELoad(CWE_REGAPI* cwe_api)
    {
        //Create a MotionTableAction to define what the animation is.
        MotionTableAction AnimAction = { testAnimation->getmotion(), 0, 0, 0xFFFFFFFF, -40, 0, 5, 0.12f};

        //Register the animation as a name.
        int AnimID = cwe_api->RegisterChaoAnimation("testAnimation", &AnimAction);

        //Change the step dance animation to the testanimation animation
        *cwe_api->GetChaoAnimation(387) = *cwe_api->GetChaoAnimation(AnimID);
        
    }

    //initialization function - MUST exist in order to have CWE and SA2 see your mod
    __declspec(dllexport) void Init(const char* path)
    {
        HMODULE h = GetModuleHandle(L"CWE");

        std::string pathStr = std::string(path) + "\\";

        //add your animationFile here:
        testAnimation = new AnimationFile(pathStr + "dab.saanim");

        RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
        RegisterDataFunc(CWELoad);
    }
    __declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}
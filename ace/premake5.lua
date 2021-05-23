ACE_MAJOR_VERSION = 0
ACE_MINOR_VERSION = 1
ACE_PATCH_VERSION = 0

ACE_INCLUDE = path.getabsolute("include")
-- ASCII RENDERING ENGINE
project "ace"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir("%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}")

    defines {
        "ACE_MAJOR_VERSION=%{ACE_MAJOR_VERSION}",
        "ACE_MINOR_VERSION=%{ACE_MINOR_VERSION}",
        "ACE_PATCH_VERSION=%{ACE_PATCH_VERSION}",
    }

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs {
        ACE_INCLUDE,
        "src",
        "include",
        "include/ace",
    }

    links {
        "ncurses"
    }

    filter "configurations:debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:release"
        runtime "Release"
        optimize "On"

project "asciiscreen"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir("%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}")

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs {
        ACE_INCLUDE,
        "src"
    }

    links {
        "ace",
        "ncurses",
    }

    filter "configurations:debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:release"
        runtime "Release"
        optimize "On"

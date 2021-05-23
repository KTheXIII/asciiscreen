workspace "typeracer"
    architecture "x64"

    startproject "asciiscreen"

    configurations {
        "debug",
        "release"
    }

include "ace"
include "asciiscreen"

workspace "LearnOpenGL"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "first_proj"

    flags
	{
		"MultiProcessorCompile"
	}

    linkgroups "On"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "lib/"

project "first_proj"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


    files 
    {
        "lib/glm/**.hpp",
        "lib/glm/**.inl",
        "lib/stb_image/stb_image.cpp",
        "src/**.h",
        "src/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs 
    {
        "%{wks.location}/lib",
        "%{wks.location}/lib/glfw/include"
    }

    links 
    {
        "GLFW",
        "GLAD"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "system:windows"
        links
        {
            "opengl32.lib"
        }

    filter "system:linux"
        files
        {
            "lib/glm/**.cpp"
        }

        links 
        {
            "GL"
        }
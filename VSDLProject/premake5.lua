workspace "VSDLProject"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "x64"
    }

    filter { "platforms:x64" }
        system "Windows"
        architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL_mixer"] = "SDLProject/Vendor/SDL_mixer"
IncludeDir["SDL2_image"] = "SDLProject/Vendor/SDL2_image"
IncludeDir["SDL2_ttf"] = "SDLProject/Vendor/SDL2_ttf"
IncludeDir["SDL2"] = "SDLProject/Vendor/SDL2"

project "SDLProject"
    location "SDLProject"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Targets all cpp and header files.
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- Includes dependencies and include paths.
    includedirs 
    {
        "%{prj.name}/src",
        "%{prj.name}/src/include",

        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL2}/include",

        "%{IncludeDir.SDL2_image}",
        "%{IncludeDir.SDL2_image}/include",

        "%{IncludeDir.SDL2_ttf}",
        "%{IncludeDir.SDL_mixer}"
    }

    excludes
	{
		
	}

    links
    {
        "SDL2",
        "SDL2main",
        "SDL2test",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    filter { "platforms:x64" }
        libdirs
        {
            "Dependencies/SDL2/x64",
            "Dependencies/SDL2_image/x64",
            "Dependencies/SDL2_mixer/x64",
            "Dependencies/SDL2_ttf/x64"
        }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            
        }

    filter "configurations:Debug"
        defines "SDL_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "SDL_RELEASE"
        optimize "On"
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "SDL_DIST"
        optimize "On"
        buildoptions "/MD"
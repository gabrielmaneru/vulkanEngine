workspace "Gaia"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
		"Release"
	}

	startproject "Gaia_SampleProject"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Gaia/extern/GLFW/include"
IncludeDir["glm"] = "Gaia/extern/glm"

include "Gaia/extern/GLFW"

project "Gaia"
	location "Gaia"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "GaiaPCH.h"
	pchsource "%{prj.name}/src/GaiaPCH.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/extern",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}"
	}
	
	links 
	{ 
		"GLFW"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines 
		{
		}
		

	filter "configurations:Debug"
		defines "GAIA_DEBUG"
		symbols "On"
				
	filter "configurations:Release"
		optimize "On"

project "Gaia_SampleProject"
	location "Gaia_SampleProject"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	debugdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build-obj/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
		"Gaia"
	}
	
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"Gaia/src",
		"Gaia/extern"
	}

	postbuildcommands 
	{
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "GAIA_DEBUG"
		symbols "on"

		links
		{
		}

		postbuildcommands 
		{
		}
				
	filter "configurations:Release"
		optimize "on"

		links
		{
		}

		postbuildcommands 
		{
		}
		
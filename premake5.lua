workspace "DXBasic"
  architecture "x64"
  startproject "DXBasic"

  configurations
  {
    "Debug",
    "Release"
  }

  outputdir = "%{cfg.buildcfg}"

  IncludeDir = {}
  IncludeDir["json"] = "vendors/json/single_include"
  IncludeDir["MinHook"] = "vendors/MinHook/include"
  IncludeDir["ImGui"] = "vendors/ImGui"
  IncludeDir["ImGuiImpl"] = "vendors/ImGui/backends"
  IncludeDir["StackWalker"] = "vendors/StackWalker/Main/StackWalker/"
  
  CppVersion = "C++20"
  MsvcToolset = "v142"
  WindowsSdkVersion = "10.0"
  
  function DeclareMSVCOptions()
    filter "system:windows"
    staticruntime "Off"
    systemversion (WindowsSdkVersion)
    toolset (MsvcToolset)
    cppdialect (CppVersion)

    defines
    {
      "_CRT_SECURE_NO_WARNINGS",
      "NOMINMAX",
      "WIN32_LEAN_AND_MEAN",
      "_WIN32_WINNT=0x601" -- Support Windows 7
    }
    
    disablewarnings
    {
      "4100", -- C4100: unreferenced formal parameter
      "4201", -- C4201: nameless struct/union
      "4307"  -- C4307: integral constant overflow
    }
  end
   
  function DeclareDebugOptions()
    filter "configurations:Debug"
      defines { "_DEBUG" }
      symbols "On"
    filter "not configurations:Debug"
      defines { "NDEBUG" }
  end
   
  project "ImGui"
    location "vendors/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
      "vendors/%{prj.name}/imgui.cpp",
      "vendors/%{prj.name}/imgui_demo.cpp",
      "vendors/%{prj.name}/imgui_draw.cpp",
      "vendors/%{prj.name}/imgui_tables.cpp",
      "vendors/%{prj.name}/imgui_widgets.cpp",
      "vendors/%{prj.name}/backends/imgui_impl_dx11.cpp",
      "vendors/%{prj.name}/backends/imgui_impl_win32.cpp"
    }

    includedirs
    {
      "vendors/%{prj.name}"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

  project "StackWalker"
    location "vendors/%{prj.name}"
    kind "StaticLib"
    language "C++"
  
    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

    files
    {
      "vendors/%{prj.name}/Main/StackWalker/StackWalker.cpp"
    }

    includedirs
    {
      "vendors/%{prj.name}/Main/StackWalker/"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

  project "MinHook"
    location "vendors/%{prj.name}"
    kind "StaticLib"
    language "C"

    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

    files
    {
      "vendors/%{prj.name}/include/**.h",
      "vendors/%{prj.name}/src/**.h",
      "vendors/%{prj.name}/src/**.c"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

  project "DXBasic"
    location "DXBasic"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir)
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    PrecompiledHeaderInclude = "pch.h"
    PrecompiledHeaderSource = "%{prj.name}/src/pch/pch.cpp"
 
    files
    {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/src/**.asm"
    }

    includedirs
    {
      "%{IncludeDir.json}",
      "%{IncludeDir.MinHook}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.ImGuiImpl}",
      "%{IncludeDir.StackWalker}",
      "%{prj.name}/src"
    }

    libdirs
    {
      "bin/lib"
    }

    links
    {
      "MinHook",
      "ImGui",
      "StackWalker"
    }

    pchheader "%{PrecompiledHeaderInclude}"
    pchsource "%{PrecompiledHeaderSource}"

    forceincludes
    {
      "%{PrecompiledHeaderInclude}"
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

    flags { "NoImportLib", "Maps" }

    filter "configurations:Debug"
      defines { "DXBASIC_DEBUG" }

    filter "configurations:Release"
      defines { "DXBASIC_RELEASE" }
      optimize "speed"
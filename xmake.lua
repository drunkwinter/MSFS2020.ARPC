add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_runtimes("MD")

target("MSFS2020.ARPC")
    set_default(true)
    set_extension(".asi")
    set_kind("shared")
    add_includedirs("external/", "src/")
    add_files("src/dllmain.cpp")
    add_deps("Hooking.Patterns")

target("Hooking.Patterns")
    set_default(false)
    set_kind("static")
    add_includedirs("external/Hooking.Patterns/", { public = true })
    add_files("external/Hooking.Patterns/Hooking.Patterns.cpp")

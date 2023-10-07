$in_file = "src/dllmain.cpp"
$out_file = "MSFS2020.ARPC.asi"
$out_dir = "build"
$include_directories = "dependencies"
$libraries = "../dependencies/Hooking.Patterns/Hooking.Patterns.cpp", "User32.lib"
$compiler_options = "/nologo", "/EHsc", "/MD", "/std:c++20"
$linker_options = "/DLL", "/OUT:$out_file"

$vcvars64 = "${Env:ProgramFiles(x86)}/Microsoft Visual Studio/2022/BuildTools/VC/Auxiliary/Build/vcvars64.bat"

Remove-Item -Path "build" -Recurse -ErrorAction Ignore

New-Item -ItemType Directory -Path $out_dir | Out-Null

cmd /c pushd $out_dir '&&' $vcvars64 '&&' cls '&&' cl "../$in_file" $libraries $compiler_options /I "../$include_directories" /link $linker_options

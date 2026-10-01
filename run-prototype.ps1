$ErrorActionPreference = 'Stop'
Push-Location $PSScriptRoot
try {
    if (-not (Test-Path -LiteralPath 'build/CMakeCache.txt')) {
        python -m cmake -S . -B build
        if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
    }
    python -m cmake --build build --parallel 8
    if ($LASTEXITCODE -ne 0) { throw 'Build failed.' }
    & './build/bin/lvgl_simulator.exe'
} finally {
    Pop-Location
}

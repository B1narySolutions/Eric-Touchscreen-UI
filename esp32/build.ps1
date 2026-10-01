param(
    [string]$Port = "",
    [switch]$Flash,
    [switch]$Monitor
)

$ErrorActionPreference = "Stop"
$FirmwareRoot = $PSScriptRoot
$ProjectRoot = Split-Path $FirmwareRoot -Parent
$SourceFont = Join-Path $ProjectRoot "ui\fonts\Montserrat_Medium.ttf"
$FirmwareFont = Join-Path $FirmwareRoot "main\assets\fonts\Montserrat_Medium.ttf"
$BuildConfig = Join-Path $FirmwareRoot "build\config.env"

$Idf = Get-Command idf.py -ErrorAction SilentlyContinue
if (-not $Idf) {
    throw "idf.py was not found. Open an ESP-IDF 5.5+ terminal, then run this script again."
}

Copy-Item -LiteralPath $SourceFont -Destination $FirmwareFont -Force

# A Docker validation build contains Linux paths and cannot be reused by the
# native Windows ESP-IDF toolchain. Only discard that generated build cache.
if (Test-Path -LiteralPath $BuildConfig) {
    $BuildEnvironment = Get-Content -LiteralPath $BuildConfig -Raw
    if ($BuildEnvironment -match '(/opt/esp|/project/)') {
        Remove-Item -LiteralPath (Join-Path $FirmwareRoot "build") -Recurse -Force
    }
}

Push-Location $FirmwareRoot
try {
    if (-not (Test-Path "sdkconfig")) {
        & idf.py set-target esp32s3
        if ($LASTEXITCODE -ne 0) { throw "idf.py set-target failed" }
    }

    & idf.py build
    if ($LASTEXITCODE -ne 0) { throw "ESP-IDF build failed" }

    if ($Flash) {
        $Arguments = @()
        if ($Port) { $Arguments += @("-p", $Port) }
        $Arguments += "flash"
        if ($Monitor) { $Arguments += "monitor" }
        & idf.py @Arguments
        if ($LASTEXITCODE -ne 0) { throw "ESP-IDF flash failed" }
    }
}
finally {
    Pop-Location
}

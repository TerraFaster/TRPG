# Get the directory where this script is located
$scriptDir = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

# Set the number of processors for parallel builds
$processorCount = [environment]::ProcessorCount

# Navigate to the script's directory
Set-Location -Path $scriptDir

# Run the CMake build command with parallel jobs
cmake --build "$scriptDir\build" --config Debug -j $processorCount

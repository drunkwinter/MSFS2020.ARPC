# MSFS2020.ARPC
MSFS2020.ARPC is an open-source patch that fixes the sky colors in Microsoft Flight Simulator 2020 (MSFS2020) by replacing atmospheric coefficients, resulting in a more realistic sky rendering.

This tool patches the atmospheric coefficients in-memory, without modifying any game files. As a result, it prevents the patch from being overwritten or the game breaking with updates and offers a simpler installation and removal process.

This tool owes its existence to the discovery made by [Biology2394](https://forums.flightsimulator.com/u/Biology2394)/[FarukEroglu2048](https://github.com/FarukEroglu2048). See [credits](#credits).

## Getting Started
1. Download the latest release of [MSFS2020.ARPC.zip](https://github.com/drunkwinter/MSFS2020.ARPC/releases/latest/download/MSFS2020.ARPC.zip).
2. Drag and drop the `dinput8.dll` and `MSFS2020.ARPC.asi` files from the archive into your MSFS installation directory.

> [!NOTE]
> The installation path containing `FlightSimulator.exe` may vary depending on where you obtained  and installed MSFS:
>
> **MS Store**:
> `C:\Program Files\WindowsApps\Microsoft.FlightSimulator_1.34.16.0_x64__8wekyb3d8bbwe`<br />
> `C:\Users\[Your User Name]\AppData\Local\Packages\ Microsoft.FlightSimulator_8wekyb3d8bbwe`<br />
> **Steam**:
> `C:\Program Files (x86)\Steam\steamapps\common\MicrosoftFlightSimulator`<br />

## Screenshots
<p align="middle">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/4016abee-2c79-47b7-bebd-8a6a59835cb7" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/977c378b-ace6-4d03-81c4-906a92110aea" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/856600d1-a1a1-4400-89e7-461a4bcb8fc3" width="32%">
</p>

<p align="middle">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/50a47f69-cd1b-4090-b84f-924e172c9b8a" width="49%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/76e2bd8a-554b-4239-836e-55a69b8f45df" width="49%">
</p>

<img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/db0821a3-2d7d-4528-ad76-a8d3ed86e6c3" width="98%">

<p align="middle">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/76e2bd8a-554b-4239-836e-55a69b8f45df" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/506927cd-3112-463b-8fe3-24359f549cf7" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/f0a9bfbc-a9ca-4d4c-9427-f58c64aa5f81" width="32%">
</p>

## Development
### Prerequisites
- [Build Tools for Visual Studio 2022](https://visualstudio.microsoft.com/downloads/?q=build+tools#:~:text=Build%20Tools%20for%20Visual%20Studio%202022)

### Building
Run with PowerShell:
```powershell
./build.ps1
```
> [!NOTE]
> The build files are located in `./build`

## Credits
##### ARPC
GitHub Repository: https://github.com/FarukEroglu2048/ARPC

MSFS Forum: https://forums.flightsimulator.com/t/replace-the-atmosphere-parameters-with-more-accurate-ones-from-arpc/607603/1

##### Ultimate-ASI-Loader
`.asi` loader by [ThirteenAG](https://github.com/ThirteenAG)

GitHub Repository: https://github.com/ThirteenAG/Ultimate-ASI-Loader

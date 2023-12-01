# MSFS2020.ARPC
> [!WARNING]
> **This project is deprecated and is no longer maintained.**
>
> The issue solved by this project has been fixed in SU14, released on December 5, 2023.

MSFS2020.ARPC is an open-source patch that fixes the sky colors in Microsoft Flight Simulator 2020 (MSFS2020) by replacing atmospheric coefficients, resulting in a more realistic sky rendering.

This tool patches the atmospheric coefficients in-memory, without modifying any game files. As a result, it prevents the patch from being overwritten with updates and offers a simpler installation and removal process.

This tool owes its existence to the discovery made by [Biology2394](https://forums.flightsimulator.com/u/Biology2394)/[FarukEroglu2048](https://github.com/FarukEroglu2048). See [credits](#credits).

## Getting Started
1. Download the latest release of [MSFS2020.ARPC.zip](https://github.com/drunkwinter/MSFS2020.ARPC/releases/latest/download/MSFS2020.ARPC.zip).
2. Drag and drop the `dinput8.dll`, `MSFS2020.ARPC.asi` and (optional) `MSFS2020.ARPC.ini` files from the archive into your MSFS installation directory.

**The installation path containing `FlightSimulator.exe` may vary depending on where you obtained and installed MSFS:**

### MS Store
- `C:\XboxGames\Microsoft Flight Simulator\Content`
     > [!NOTE]
     > This folder might not exist if you have an older install, convert to the modern install. <br />
     > (See https://parallel42.com/blogs/wiki/converting-my-sim-install-from-legacy-to-modern)

- `C:\Program Files\WindowsApps\Microsoft.FlightSimulator_1.34.16.0_x64__8wekyb3d8bbwe`
     > [!IMPORTANT]
     > To access this folder you need to take ownership of the `WindowsApps` folder. <br />
     > (See https://forums.flightsimulator.com/t/take-ownership-of-the-windows-apps-folders/388969)
### Steam
- `C:\Program Files (x86)\Steam\steamapps\common\MicrosoftFlightSimulator`

## Configuration
`MSFS2020.ARPC.ini` allows you to customize the patch.

```ini
; WARNING: Do not leave out the values; remove the entire line instead.
;          Entering invalid values may cause the game to crash.

[COEFFICIENTS]
RED = 0.002723
GREEN = 0.001831
BLUE = -0.000083096

; Enable the live editing functionality
; When enabled, changes to the coefficients reflect in-game when saved
LIVE_EDITING_ENABLED = false ; Set to 'true' to enable live editing


[TOGGLE]
; Enable the toggle functionality
ENABLED = false ; Set to 'true' to enable the toggle feature

; Key code for toggling (See https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
KEY_CODE = 0x2D ; INSERT

; Enable or disable key modifiers
HOLD_ALT = false ; Set to 'true' to use Alt as a modifier
HOLD_CTRL = true ; Set to 'false' to disable Ctrl as a modifier
HOLD_SHIFT = false ; Set to 'true' to use Shift as a modifier
```

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

<p align="middle">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/db0821a3-2d7d-4528-ad76-a8d3ed86e6c3" width="98%">
</p>

<p align="middle">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/76e2bd8a-554b-4239-836e-55a69b8f45df" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/506927cd-3112-463b-8fe3-24359f549cf7" width="32%">
    <img src="https://github.com/drunkwinter/MSFS2020.ARPC/assets/38593134/f0a9bfbc-a9ca-4d4c-9427-f58c64aa5f81" width="32%">
</p>

## Development
### Prerequisites
- [Build Tools for Visual Studio 2022](https://visualstudio.microsoft.com/downloads/?q=build+tools#:~:text=Build%20Tools%20for%20Visual%20Studio%202022)
- [xmake](https://xmake.io/)

### Building
Run in terminal:
```powershell
xmake
```
> [!NOTE]
> The build files are located in `build/`

## Credits
#### ARPC
GitHub Repository: https://github.com/FarukEroglu2048/ARPC

MSFS Forum: https://forums.flightsimulator.com/t/replace-the-atmosphere-parameters-with-more-accurate-ones-from-arpc/607603/1

#### Ultimate-ASI-Loader
`.asi` loader by [ThirteenAG](https://github.com/ThirteenAG)

GitHub Repository: https://github.com/ThirteenAG/Ultimate-ASI-Loader

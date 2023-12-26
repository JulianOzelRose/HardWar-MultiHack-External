# HardWar-MultiHack-External
This program only modifies client sided variables. It cannot modify server sided variables,
so it will not work on a networked game, unless it is run directly by the host. Works with
game version UIM6. Includes invincibility, speedhack, infinite cash, instakill target,
and stall negation. For educational purposes only.

To download the hack, navigate to the [Release](https://github.com/JulianOzelRose/HardWar-MultiHack-External/tree/master/Release)
folder of this repo, then download ```HardWar-MultiHack-External.exe```. You can run the .exe from anywhere on your computer,
but it must be run with administrator priveleges. The hack will automatically detect and hook itself onto
the HardWar process. Once enabled in-game, the ```DELETE``` key toggles instakill, and the
```INSERT``` key toggles the speedhack.

## Data structures

The player entity pointer is stored on offset ```0x11D9AC``` from the module's base address. The player's cash variable,
for example, would be stored on the address at ```moduleBase + 0x11D9AC + 0x03C```. Memory mappings of the player, moth,
hangar, and cargo data structures can be found in the tables below.

#### Player ####
| **Offset** | **Type** | **Variable** |
| :---       | :---     | :---         |
| 0x004      | String   | Name         |
| 0x02C      | Integer  | Status       |
| 0x030      | Pointer  | Location     |
| 0x03C      | Integer  | Cash         |

The location pointer on offset ```0x030``` of the player data structure
points to the address of the moth or hangar that the player
is currently located. If the player is in a moth located in a hangar,
then the moth's address will be pointed to. If the player is on foot
in a hangar, then the hangar's address will be pointed to. Dead players
are teleported to the Limbo! hangar, where they remain on foot. For the
player status variable on offset ```0x02C```, a value of 1 indicates the
player is in a moth, a value of 2 means the player is on foot in a hangar,
a value of 3 means the player is in a monorail car, a value of 4 means the
player is awaiting a monorail car, and a value of 5 means the player is in a walkway.

#### Moth ####
| **Offset** | **Type**  | **Variable**       |
| :---       | :---      | :---               |
| 0x1D0      | Pointer   | Hangar             |
| 0x1D4      | DWORD     | Status             |
| 0x1D8      | Pointer   | Owner              |
| 0x1EC      | Integer   | Target Type        |
| 0x1F0      | Pointer   | Target             |
| 0x1F4      | Integer   | Drone Type         |
| 0x200      | Integer   | Engine Number      |
| 0x204      | Integer   | Cell Number        |
| 0x208      | Integer   | Pod Type           |
| 0x20C      | Integer   | Current Weapon     |
| 0x248      | Integer   | Weapon 1 Ammo      |
| 0x24C      | Integer   | Weapon 2 Ammo      |
| 0x250      | Integer   | Weapon 3 Ammo      |
| 0x254      | Integer   | Weapon 4 Ammo      |
| 0x2DC      | Pointer   | Pilot              |
| 0x2E0      | Pointer   | Passenger          |
| 0x2E4      | BYTE      | Autopilot Status   |
| 0x294      | DWORD     | Shields            |
| 0x298      | DWORD     | Engine Damage      |
| 0x29C      | DWORD     | Structure Damage   |
| 0x2A0      | DWORD     | CPU Damage         |
| 0x2A4      | DWORD     | Power Damage       |
| 0x2A8      | DWORD     | Weapons Damage     |
| 0x368      | Integer   | Flares             |
| 0x378      | Integer   | Chaff              |
| 0x37C      | Integer   | Shells             |
| 0x390      | Integer   | Stall Level        |
| 0x438      | DWORD     | Thrust             |

The hangar pointer on offset ```0x1D0``` of the moth data structure
points to the address of the hangar that the moth is currently parked
in, if applicable. The pilot pointer on offset ```0x2DC``` points to
the address of the pilot. The target pointer on offset ```0x1F0```
points to the address of the moth's current target -- which can be either
a hangar address or a moth address. The health and shield values on
```0x294```, ```0x298```, ```0x29C```, ```0x2A0```, ```0x2A4```, and ```0x2A8```
all have maximum values of 0x4000 (or 16384 in decimal). The hex value on
```0x0B8``` stores the autopilot, flight, power, and shield system versions.
The hex value on ```0x0BC``` stores the navigation, radar, target, and
infrared system versions.

#### Hangar ####
| **Offset** | **Type**  | **Variable**     |
| :---       | :---      | :---             |
| 0x004      | String    | Terminal Name    |
| 0x010      | String    | Display Name     |
| 0x034      | Integer   | Clearance Level  |
| 0x03C      | Pointer   | Enemies List     |
| 0x048      | Pointer   | Owner            |
| 0x8BC      | Integer   | Cash Held        |
| 0x8D8      | Pointer   | Bay 1            |
| 0x8DC      | Pointer   | Bay 2            |
| 0x8E0      | Pointer   | Bay 3            |
| 0x8E4      | Pointer   | Bay 4            |
| 0x8E8      | Pointer   | Bay 5            |
| 0x8EC      | Pointer   | Bay 6            |

The variable on offset ```0x004``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0x010``` holds the
display name that is viewed by the player. The clearance level variable
on offset ```0x034``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x8D8```,
```0x8DC```, ```0x8E0```, ```0x8E4```, ```0x8E8```, and ```0x8EC``` point to the address
of the moth that is currently in that bay.

#### Cargo ####
| **Offset** | **Type**  | **Variable** |
| :---       | :---      | :---         |
| 0x004      | Integer   | Quantity     |
| 0x008      | Integer   | Status       |
| 0x00C      | Pointer   | Location     |

The status variable on offset ```0x008``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0x00C``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x004``` simply holds the quantity of the item.

## Sources
I credit Guided Hacking for my knowledge of game hacking. They have very in-depth tutorials and guides
on how to create your own cheat tables and trainers from scratch. I highly reccommend purchasing a subscription
if you are interested in learning game hacking. Below are links to some of the guides I used to help me create this program.
* [Guided Hacking - Guide - GHB0 - Game Hacking Bible Introduction](https://guidedhacking.com/threads/ghb0-game-hacking-bible-introduction.14450/)
* [Guided Hacking - GHB1 - Start Here Beginner Guide to Game Hacking](https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/)
* [Guided Hacking - How to Hack Any Game Tutorial C++ Trainer #1 - External](https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-1-external.10897/)
* [Guided Hacking - How to Hack Any Game Tutorial C++ Trainer #2 - External v2](https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-2-external-v2.12000/)
* [Guided Hacking - FindDMAAddy - C++ Multilevel Pointer Function](https://guidedhacking.com/threads/finddmaaddy-c-multilevel-pointer-function.6292/)

# HardWar-MultiHack
This program only modifies client sided variables. It cannot modify server sided variables,
so it will not work on a networked game, unless it is run directly by the host. Works with
game version UIM6. Includes invincibility, speedhack, infinite cash, instakill target,
and stall negation. For educational purposes only.

# Data Structures of HardWar UIM6

The player entity pointer is stored on offset
```0x11D9AC``` from the module's base address. The player's cash variable,
for example, would be stored on the address at ```moduleBase + 0x11D9AC + 0x03C```.
Memory mappings of the player, moth, hangar, and cargo data structures can be found
in the tables below.

## Player data structure ##
| **Offset**     | **Variable**    | **Type**       |
| :---           | :---            | :---           |
| 0x004          | name            | String[32]     |
| 0x030          | location*       | Pointer        |
| 0x03C          | cash            | Integer        |
| 0x058          | status          | BYTE           |

The location pointer on offset ```0x030``` of the player data structure
points to the address of the moth or hangar that the player
is currently located. If the player is in a moth located in a hangar,
then the moth's address will be pointed to. If the player is on foot
in a hangar, then the hangar's address will be pointed to. Dead players
are teleported to the Limbo! hangar, where they remain on foot. For the
player status variable on offset ```0x058```, a value of 1 means the player
is currently in a moth, a value of 2 means the player is in hangar or dead,
and a value of 4 means the player is awaiting a monorail.


## Moth data structure ##
| **Offset**    | **Variable**    | **Type**      |
| :---          | :---            | :---          |
| 0x0B8         | systemUpgrades1 | DWORD         |
| 0x0BC         | systemUpgrades2 | DWORD         |
| 0x1D0         | hangar*         | Pointer       |
| 0x1D8         | owner*          | Pointer       |
| 0x1F0         | target*         | Pointer       |
| 0x1F4         | droneType       | Integer       |
| 0x200         | engineNum       | Integer       |
| 0x204         | cellNum         | Integer       |
| 0x208         | podType         | Integer       |
| 0x20C         | currentWeapon   | Integer       |
| 0x248         | weapon1Ammo     | Integer       |
| 0x24C         | weapon2Ammo     | Integer       |
| 0x250         | weapon3Ammo     | Integer       |
| 0x254         | weapon4Ammo     | Integer       |
| 0x294         | shields         | DWORD         |
| 0x298         | engineDamage    | DWORD         |
| 0x2DC         | pilot*          | Pointer       |
| 0x2E0         | passenger*      | Pointer       |
| 0x29C         | structureDamage | DWORD         |
| 0x2A0         | cpuDamage       | DWORD         |
| 0x2A4         | powerDamage     | DWORD         |
| 0x2A8         | weaponsDamage   | DWORD         |
| 0x368         | numFlares       | Integer       |
| 0x378         | numChaff        | Integer       |
| 0x37C         | numShells       | Integer       |
| 0x390         | stallWarningLvl | Integer       |
| 0x438         | thrust          | DWORD         |

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


## Hangar data structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x004         | terminalName     | String[32]    |
| 0x010         | displayName      | String[32]    |
| 0x034         | clearanceLvl     | Integer       |
| 0x03C         | enemiesList*     | Pointer       |
| 0x048         | owner*           | Pointer       |
| 0x8BC         | cashHeld         | Integer       |
| 0x8D8         | bay1*            | Pointer       |
| 0x8DC         | bay2*            | Pointer       |
| 0x8E0         | bay3*            | Pointer       |
| 0x8E4         | bay4*            | Pointer       |
| 0x8E8         | bay5*            | Pointer       |
| 0x8EC         | bay6*            | Pointer       |

The variable on offset ```0x004``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0x010``` holds the
display name that is viewed by the player. The clearance level variable
on offset ```0x034``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x8D8```,
```0x8DC```, ```0x8E0```, ```0x8E4```, ```0x8E8```, and ```0x8EC``` point to the address
of the moth that is currently in that bay.


## Cargo data structure ##
| **Offset**      | **Variable**     | **Type**      |
| :---            | :---             | :---          |
| 0x004           | quantity         | Integer       |
| 0x008           | status           | Integer       |
| 0x00C           | location*        | Pointer       |

The status variable on offset ```0x008``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0x00C``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x004``` simply holds the quantity of the item.

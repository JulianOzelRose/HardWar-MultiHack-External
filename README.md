# HardWar-MultiHack
This program only modifies client sided variables. It cannot modify server sided variables,
so it will not work on a networked game, unless it is run directly by the host. Works with
game version U2.04 only. Includes invincibility, speedhack, infinite cash, instakill target,
and stall negation. For educational purposes only.

# Data Structures of HardWar U2.04

The player entity pointer is stored on offset
```0x1471E4``` from the module's base address. The player's cash variable,
for example, would be stored on the address at ```moduleBase + 0x1471E4 + 0x24```.
Memory mappings of the player, moth, hangar, and cargo data structures can be found
in the tables below.

## Player data structure ##
| **Offset**    | **Variable**    | **Type**       |
| :---          | :---            | :---           |
| 0x0           | name            | String[32]     |
| 0x14          | status          | BYTE           |
| 0x18          | location*       | Pointer        |
| 0x24          | cash            | Integer        |

The location pointer on offset ```0x18``` of the player data structure
points to the address of the moth or hangar that the player
is currently located. If the player is in a moth located in a hangar,
then the moth's address will be pointed to. If the player is on foot
in a hangar, then the hangar's address will be pointed to. Dead players
are teleported to the Limbo! hangar, where they remain on foot. For the
player status variable on offset ```0x14```, a value of 1 means the player
is currently in a moth, a value of 2 means the player is in hangar or dead,
and a value of 4 means the player is awaiting a monorail.


## Moth data structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x1D0         | hangar*          | Pointer       |
| 0x1D8         | pilot*           | Pointer       |
| 0x1F0         | target*          | Pointer       |
| 0x1F4         | hasSalvageDrone  | Boolean       |
| 0x248         | weapon1Ammo      | Integer       |
| 0x24C         | weapon2Ammo      | Integer       |
| 0x250         | weapon3Ammo      | Integer       |
| 0x254         | weapon4Ammo      | Integer       |
| 0x294         | shields          | DWORD         |
| 0x298         | engineDamage     | DWORD         |
| 0x29C         | structureDamage  | DWORD         |
| 0x2A0         | cpuDamage        | DWORD         |
| 0x2A4         | powerDamage      | DWORD         |
| 0x2A8         | weaponsDamage    | DWORD         |
| 0x368         | numFlares        | Integer       |
| 0x378         | numChaff         | Integer       |
| 0x37C         | numShells        | Integer       |
| 0x390         | stallWarningLvl  | Integer       |
| 0x438         | thrust           | DWORD         |

The hangar pointer on offset ```0x1D0``` of the moth data structure
points to the address of the hangar that the moth is currently parked
in, if applicable. The pilot pointer on offset ```0x1D8``` points to
the address of the pilot. The target pointer on offset ```0x1F0```
points to the address of the moth's current target -- which can be either
a hangar address or a moth address. The health and shield values on
```0x294```, ```0x298```, ```0x29C```, ```0x2A0```, ```0x2A4```, and ```0x2A8```
all have maximum values of 4000.


## Hangar data structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x0           | terminalName     | String[32]    |
| 0xC           | displayName      | String[32]    |
| 0x30          | clearanceLvl     | Integer       |
| 0x38          | wantedList*      | Pointer       |
| 0x44          | owner*           | Pointer       |
| 0x300         | cashHeld         | Integer       |
| 0x31C         | bay[0]*          | Pointer       |
| 0x320         | bay[1]*          | Pointer       |
| 0x324         | bay[2]*          | Pointer       |
| 0x328         | bay[3]*          | Pointer       |
| 0x32C         | bay[4]*          | Pointer       |
| 0x330         | bay[5]*          | Pointer       |

The variable on offset ```0x0``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0xC``` holds the
actual display name that is viewed by the player. The clearance level variable
on offset ```0x30``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x31C```,
```0x320```, ```0x324```, ```0x328```, ```0x32C```, and ```0x330``` point to the address
of the moth that is currently in that bay.


## Cargo data structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x4           | quantity         | Integer       |
| 0x8           | status           | Integer       |
| 0xC           | location*        | Pointer       |

The status variable on offset ```0x8``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0xC``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x4``` simply holds the quantity of the item.

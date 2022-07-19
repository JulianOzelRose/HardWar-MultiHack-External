# Data Structures of HardWar U2.04

The player's local entity pointer is dynamically allocated on offset
```0x1471E4``` from the module base address. The player's cash variable,
for example, would be accessed by the address at ```moduleBase + 0x1471E4 + 0x24```.
Memory mappings of the player, moth, hangar, and cargo data structures can be found
in the tables below.

## Player structure ##
| **Offset**    | **Variable**    | **Type**       |
| :---          | :---            | :---           |
| 0x0           | name            | string         |
| 0x14          | status          | BYTE           |
| 0x18          | location*       | pointer        |
| 0x24          | cash            | integer        |
| 0x28          | pilotType       | BYTE           |

The location pointer on offset ```0x18``` of the player data structure
points to the address of the moth or hangar that the player
currently located. If the player is in a moth that is in a hangar,
then the moth's address will be pointed to. If the player is on foot
in a hangar, then the hangar's address will be pointed to. Dead players
are teleported to the Limbo! hangar, where they remain on foot. For the
player status variable on offset ```0x14```, a value of 1 means the player
is currently in a moth, a value of 2 means the player is in hangar or dead,
and a value of 4 means the player is awaiting a monorail.


## Moth structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x1D0         | hangar*          | pointer       |
| 0x1D8         | pilot*           | pointer       |
| 0x1F0         | target*          | pointer       |
| 0x1F4         | hasSalvageDrone  | boolean       |
| 0x248         | weapon1Ammo      | integer       |
| 0x24C         | weapon2Ammo      | integer       |
| 0x250         | weapon3Ammo      | integer       |
| 0x254         | weapon4Ammo      | integer       |
| 0x294         | shields          | DWORD         |
| 0x298         | engineDamage     | DWORD         |
| 0x29C         | structureDamage  | DWORD         |
| 0x2A0         | cpuDamage        | DWORD         |
| 0x2A4         | powerDamage      | DWORD         |
| 0x2A8         | weaponsDamage    | DWORD         |
| 0x368         | numFlares        | integer       |
| 0x378         | numChaff         | integer       |
| 0x37C         | numShells        | integer       |
| 0x390         | stallWarningLvl  | integer       |
| 0x438         | thrust           | DWORD         |

The hangar pointer on offset ```0x1D0``` of the moth data structure
points to the address of the hangar that the moth is currently parked
in, if applicable. The pilot pointer on offset ```0x1D8``` points to
the address of the pilot. The target pointer on offset ```0x1F0```
points to the address of the moth's current target -- this can be either
a hangar address or a moth address. The health and shield values on
```0x294```, ```0x298```, ```0x29C```, ```0x2A0```, ```0x2A4```, and ```0x2A8```
all have maximum values of 4000.


## Hangar structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x0           | terminalName     | string        |
| 0xC           | displayName      | string        |
| 0x30          | clearanceLvl     | integer       |
| 0x38          | wantedList*      | pointer       |
| 0x44          | owner*           | pointer       |
| 0x31C         | bay[0]*          | pointer       |
| 0x320         | bay[1]*          | pointer       |
| 0x324         | bay[2]*          | pointer       |
| 0x328         | bay[3]*          | pointer       |
| 0x32C         | bay[4]*          | pointer       |
| 0x330         | bay[5]*          | pointer       |
| 0x300         | cashHeld         | integer       |

The variable on offset ```0x0``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0xC``` holds the
actual display name that is viewed by the player. The clearance level variable
on offset ```0x30``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x31C```,
```0x320```, ```0x324```, ```0x328```, ```0x32C```, and ```0x330``` point to the address
of the moth that is currently in that bay.


## Cargo structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x4           | quantity         | integer       |
| 0x8           | status           | integer       |
| 0xC           | location*        | pointer       |

The status variable on offset ```0x8``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0xC``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x4``` simply holds the quantity of the item.

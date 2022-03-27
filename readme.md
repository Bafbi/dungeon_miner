# Dungeon Miner

Dungeon miner is a game coded in C and render in the console.

Current look of the game :  
![](https://cdn.discordapp.com/attachments/676180251155365893/957596506741964840/unknown.png)

---

## Current Implementation

-   Random world generator with perlin noise
-   A chunk system
-   Basic movement for the player
-   Simple render that show the current chunk the plyer if in with relative position in the console
-   Ability to the player to destroy block

---

## Futur Implementation

-   A better render with the use of the light as view distance
-   Load and unload chunk dynamically as the player pass chunk
-   Save chunk data into file and load them when needed
-   Render correctly when the user change the console size
-   Made the player pass from one side to another when he is on te border of the console
-   Implement items drop when mine a block
-   Implement inventory with the possibility to pick up items
-   Add more ore
-   Use a generator config for simplify world creation
-   Try to use more colors in console (don't know if it's realy possible)
-   Add multiplayer (will be complicated)

---

## Installation

The projet is compiled with gcc using MinGW on vscode, due to the scale of the current project the exe is in the repo, free to download and launch

---

## Contributing

Your free to test/fork the project and add issues but I will not accept pull request cause I want to do all by myself

---

## License

[MIT](https://github.com/Bafbi/dungeon_miner/blob/main/LICENSE)

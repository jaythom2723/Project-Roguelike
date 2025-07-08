# Project: Roguelike
Project: Roguelike is a relatively simple classic-roguelike prototype designed and programmed by Jacob Thomas. Inspired by the likes of Cogmind, Caves of Qud, and Dwarf Fortress, Project: Roguelike aspires to be another one of the many complicated "spreadsheet"-style of games.
As of the [first commit](https://github.com/jaythom2723/Project-Roguelike/commit/61038cfb1929a1a146e1560ab1487df37aec1088) the game is entirely compiled on Windows for 64-bit systems. Right now, the programming is still considered to be in an early dev-build and prototypal stage. This means that Linux will ***not*** be supported for quite some time.

# Roguelike Text-based Engine (RoTex/ROT)
RoTex is the custom-built game engine designed specifically for Project: Roguelike and other games alike (pun intended). The engine utilizes the most recent version of SDL3, SDL3ttf, and SDL3image in order to load and render text and various graphics onto the screen in High-Definition.
The engine, although rather barebones, supports a hierarchical entity system that is still heavily Work In Progress, alongside a grid-based placement and movement system for entities as well. You can even opt-out of grid usage if you'd like!

## Version 1.0 Archive
As of Monday, July 7th, 2025 11:27AM UTC-6, Version 1.0 for the engine has been archived and is considered *deprecated*. The engine will be undergoing a massive rewrite in order to meet design standards originally put in place at the start of the engine's development, but were neglected during programming. The following spreadsheet contains active design choices, brainstorming, and various other design-related topics related to Version 2.0 of ROTEX, perhaps even undergoing a name change.

Following the archiving of ROTEX v1, the engine should and will be compiled for linux *alongside* windows, for maximum portability purposes.

You can find the design spreadsheet [here](https://docs.google.com/spreadsheets/d/1Rv2bZHbDGYM2H6CBl9pF2B9HfRL5sjF3i0Gswf3lkiM/edit?usp=sharing)

## Version 2.0 - ACTIVE
Version 2.0 is the current and actively-developed version for the Roguelike Text-Based Engine (ROTEX/ROT). Periodic updates will be added to the readme under this section as needed.

# Changelogs
Changelogs will be provided in the "changes/" folder within the repo. These files will be markdown files that will document what has been changed since the previous commit.

# Designs
Designs will be provided in the "designs/" folder within the repo. These files will primarily consist of markdown files that provide in-depth explanations of why/how/what im implementing in a given *changelog*.

# Documentation
Documentation and samples for the *Roguelike Text-Based Engine (ROTEX)* will be made in subfolders whenever the engine is in a state to allow for samples to be created.

Documentation will be provided via "Doxygen"-style comments that will explain what a function does, what their parameters are, as well as what they return.

"Man" pages and "Markdown" files will also be provided via the 'documentation/' folder within the repo.

# Compiling
~~Open the SLN and press build. All dependencies *should* be included, if not, make an issue, and I'll try to get it resolved by adding a `redist` folder to the repo. Thanks for checking out the project!~~

^ as of **Version 1.0 Archive, Monday, July 7th, 2025 11:27AM UTC-6**, this compilation method will no-longer be supported as the main compilation standard for the rotex engine. Makefiles will be used in substitution (potentially alongside CMAKE).

Currently, the engine is not in a state that should be compiled by users wishing to program a game with the engine.

# Notes
*images will eventually be uploaded to this repository for the sake of adding flavor to this README. Other than the information listed above, I am not sure what else to add here.*
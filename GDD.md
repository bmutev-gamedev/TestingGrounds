# Testing Grounds GDD #

Game Design Document for the game Testing Grounds.

### Concept ###

* The player is a contestand in an entertainment game(similar to Hunger Games) 
* He has to survive as many testing grounds as he can

### Rules ###

* The player has to pass an area in the aloted time, and continue passing areas until:
  A: He dies.
  B: He runs out of time before leaving an area.
  
* AI enemies will be present in every area, with the first one having the least and every sequential more, until reaching a limit.
* There will be specific areas(checkpoints) where the player progress will be saved when entered.
* At checkpoints the timer is stopped.
* Thepending on the players kill score there will be health packs and ammonitions restoring the respective % of life and ammo.
* If killed he returns to the last checkpoint.
* The player is scored based on how long he has taken to pass an area, how many areas he passed and how many AI he killed.

### Requirements ###

* Testing ground landscape(s)
* Unreal starter content + landscape tools
* 2 guns, and two ammo box types
* A rigged humanoid character we can modify
* Various SFX, samples from Gamemaster Audio
* Some other stuff

### Potential Technical Challanges ###

* Serialisation when saving
* Checkpoint system architecture
* Smooth networking for co-op play
* Procedural generation of testing grounds
* Creating a new skeletal animation
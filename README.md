# Programming 3 Exercise project template

1. Make sure you have setup ssh-key for your GitLab account. https://course-gitlab.tuni.fi/profile/keys
2. Clone and add template repo as remote.
Address: git@course-gitlab.tuni.fi:tie-0240x-ohjelmointi-3-programming-3-2020-2021/group_template_project.git
3. Pull from template, and do git submodule update --init in repo. Check that Course now contains something.
4. Make sure you can build the project. (Should compile without issues if your environment is setup correctly)

## Submodule / CourseLib
Submodule for CourseLib is currently configured to use ssh. If you haven't yet setup an ssh-key. Go do it at  https://course-gitlab.tuni.fi/profile/keys

The page contains also instructions for generating and using existing ssh-keys.

Don't change anything in CourseLib ( You won't be able to submit changes made in it )

If you find any bugs and/or missing features you can report them in GitLab https://course-gitlab.tuni.fi/tie-0240x-ohjelmointi-3-programming-3-2020-2021/course/-/issues

## Doxygen documentation

No Doxyfile is provided with the project, but you may generate it using doxygen or doxywizard. For example, "doxygen -g" should generate configuration file named DoxyFile.

## How to play
Move: Key arrow or WASD

Shoot: Spacebar

## Game Play
At the beginning of the game, there will be a setting ui appear to let user choose level, mapsize and character(Iron Man, Captain America and Thor), each comes with different bullet. In the easy mode, there will be an Enemy (Thanos) appear each 500 ticks (about 15 second) while in normal mode, we add 1 more Enemy for you to destroy. Destroy the Enemy gives no reward, but if you don't, after jumping to random location 3 times, it will dissapear and destroyed about half of the current Nysse, reduce your chance to get high score. Easy mode lasts for 1 minute, while normal mode lasts for 3 minutes
If the player doesn't move, click the Player figure to focus it.

![Game Play](https://i.makeagif.com/media/11-30-2020/lhqiv-.gif)


## Scoring
Whenever you destroy a Nysse, the score will increase at least by 1. The more passengers the Nysse currently have, the higher score you will get.

## Requirements
### Basic requirements
- The game compiled successfully
- Scoring game-mechanics and game timer implemented
- Setting window implemented to let you choose the difficulty and hero.
- One own Enemy Actor

### Intermediate requirements
- Owns graphics fully implemented by the team (Nysse, Bus stop, Player, Enemy graphics)
- Additional unique Player Actor which can move and shoot using keyboard.
- The game works

### Top-grade requirements
- Passenger amounts: The passenger amount is display on Nysse's icons, but not on stops since some area may have high density of stops, such as Keskustori. Therefore, display the number of passenger at the stop can cause some confusions. However, you can see the number of passengers at stop by draging the mouse cursor to the stop.
- Following the game state: The statistics collected during game are shown in real time (score, Nysse left, New Nysse coming, Passed time)
- Scene-controlled animation: We overrided the QGraphicsScene::advance() in the city.hh to update the game smoother, running at 30fps. This slot advances the scene by one step, by calling ActorItem::advance(int phase) for all items on the scene. This is done in 2 phases: in the first phase, all items are notified that the scene is about to change, and in the second phase all items are notified that they can move. In the first phase, ActorItem::advance(int phase) is called with phase 0, and 1 is passed in the second phase.
- Option to choose many characters and different bullets are done as well.
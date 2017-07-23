# nutetris
tetris clone in c++11 and java for educational purposes

![nuTetris - Java version](https://7bcac53c-a-62cb3a1a-s-sites.googlegroups.com/site/eantcal/home/c/nutetris/jetris.png)

## Why nuTetris?

nuTetris is a good sample of not trivial application which can be used as example in a programming course.
So, it has been designed mainly for educational purposes for developers that can deal with a non-trivial example of object-oriented design, which relies on effective modern techniques for producing modular and reusable and multi-platform code.

## The game components
- Game manager 
  - Builds other game components 
  - Gets any input event from Input Manager 
  - Executes the game state machine 
  - Calls the Renderer in order to draw the game scene 
  - Canvas and Game Board are instance of Grid class (tetris::grid_t), which manages the interactions among the pieces. It is also used to represent the piece canvas which shows a preview of next falling piece Game data (tetris::game_mgr_t::game_renderer_data_t) object holds information passed to the Renderer which use them to draw the scene
  
![nuTetris components](http://www.eantcal.eu/home/c/nutetris/tetrismodules.jpg?attredirects=0)

- Renderer
  - Interface for the game scene renderer 
  - At compile time is selected one of the following renderer implementations: 
  - Text Renderer (is a Renderer) 
  - Renders the game scene using ASCII art graphics 
  - GDI Renderer (is a Renderer) relies on GUI (tetris::gui_t) which provides an Adapter for Linux (X11) and Windows implementations
  
- Piece Factory
  - Creates each Tetris Piece instance needed by Game Manager 
  
- Tetris Piece (implements the abstract class tetris::piece_t) 
  - Holds piece shape information
  
- Input Manager (is an Input Event Dispatcher) 
  - Manages the input devices (Keyboard, Timers) and notifies the Game Manager of user and timer events 
  
- Input Device
  - Interface which defines how input is managed 
  
- Keyboard Input Device (is an Input Device) 
  - Gets keyboard events
 

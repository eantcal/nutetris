using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;

namespace nuTetris
{
    /**  
     * Builds game components.
     * Processes any input event from Input Manager.
     * Executes the game state machine.
     * Calls the Renderer in order to draw the game scene.
     **/
    public class GameManager
    {
        /** Game states */
        enum GameState
        {
            BEGIN, PLAYING, GAMEOVER
        };

        /** Game input events */
        public enum InputEvent
        {
            NONE,
            MOVE_RIGHT,
            MOVE_LEFT,
            MOVE_DOWN,
            ROTATE_CW,
            ROTATE_ACW,
            DROP_PIECE,
            EXIT,
            PAUSE_GAME
        };

        /** Board columns */
        private const int DEF_COLS = 10;

        /** Board rows */
        private const int DEF_ROWS = 20;

        /** Window size */
        public const int DEF_XRES = 480;
        public const int DEF_YRES = 480;

        /** 'Full-row blink' delay (ms) */
        private const int FULL_ROW_BLNK_DL = 250;

        /** Score multiplier */
        private const int FULL_ROW_SCORE_ODM = 10;

        /** Board position */
        private const int BOARD_X = 10;
        private const int BOARD_Y = 20;

        /** Canvas position */
        private const int CANVS_X = 320;
        private const int CANVS_Y = 50;

        private const int BRICKSIZE = 20;

        public GameManager(MainForm mainForm)
        {
            this.mainForm = mainForm;
            gameGrid = new Grid(DEF_COLS, DEF_ROWS);
            fullrowBlinkDalayMs = FULL_ROW_BLNK_DL;
            gridRenderer = new GridRenderer(gameGrid, BOARD_X, BOARD_Y, true, BRICKSIZE);
            canvasRenderer = new GridRenderer(previewCanvas, CANVS_X, CANVS_Y, false, BRICKSIZE);
            mainForm.Size = new System.Drawing.Size(DEF_XRES, DEF_YRES);
        }

        /** Redraw the scene */
        public void RenderScene(System.Drawing.Graphics g)
        {
            String scoreText = String.Concat(Score);

            mainForm.getScoreBoard().Text = scoreText;

            gridRenderer.Update(g);
            canvasRenderer.Update(g);
        }

        /** Revert to previous piece position / orientation */
        public void UndoMovePiece()
        {
            gameGrid.CurrentPiece.Undo();
            _ = gameGrid.GetPlacePiece();
        }

        /** Take a new piece from catalog */
        public void SelectNewPiece()
        {
            previewCanvas.MovePieceToGrid(gameGrid);

            int catalog_size = pFactory.PieceCatalogSize;

            previewCanvas.SetCurrentPiece(
                pFactory.Make(randomGenerator.Next(catalog_size)));

            previewCanvas.Clear();
            _ = previewCanvas.GetPlacePiece();
        }

        /** Acknowledge last input event */
        public void AckInputEvent()
        {
            lastInput = InputEvent.NONE;
        }

        /** Remove the piece from the game area */
        private void RemovePiece() => gameGrid.RemovePiece();

        public void TimerTick() => inputMgr.Tick();

        /** Process any new input event */
        void ProcessInput()
        {
            InputManager.EventType ev = inputMgr.Poll();

            switch (ev)
            {
                case InputManager.EventType.DOWN:
                    lastInput = InputEvent.ROTATE_ACW;
                    break;
                case InputManager.EventType.ESCAPE:
                    break;
                case InputManager.EventType.LEFT:
                    lastInput = InputEvent.MOVE_LEFT;
                    break;
                case InputManager.EventType.RIGHT:
                    lastInput = InputEvent.MOVE_RIGHT;
                    break;
                case InputManager.EventType.SPACE:
                    pieceDropped = true;
                    lastInput = InputEvent.MOVE_DOWN;
                    break;
                case InputManager.EventType.TIMERTICK:
                    lastInput = InputEvent.MOVE_DOWN;
                    break;
                case InputManager.EventType.UNKNOWN:
                    break;
                case InputManager.EventType.UP:
                    lastInput = InputEvent.ROTATE_CW;
                    break;
                default:
                    lastInput = InputEvent.NONE;
                    break;
            }
        }

        //! Returns and acknowledges last input event
        public InputEvent Input
        {
            get
            {
                InputEvent input = lastInput;
                lastInput = InputEvent.NONE;
                return input;
            }
        }

        /**
         * Set / reset pieceDropped state which causes a series of move down event in
         * order to speed up piece falling
         */
        public void DropPiece(bool st)
        {
            pieceDropped = st;

            if (!st)
                AckInputEvent();
        }

        /** Gets a list of completed rows */
        public HashSet<int> FullRows => gameGrid.GetFullRows();

        /** Fills the cells of a whole row using a given color attribute */
        public void FillRow(int rowIdx, int attr) => gameGrid.FillRow(rowIdx, attr);

        /** Remove the completed rows, moving down the other cells */
        public void RemoveFullRows() => gameGrid.RemoveFullRows();

        /** Processes an input and handles it ! if it is related to piece movement */
        public InputEvent HandlePieceMovements()
        {
            InputEvent input = Input;

            // Check if no other input is present then
            // if the piece is released create MOVE_DOWN event
            if (pieceDropped && input == InputEvent.NONE)
                input = InputEvent.MOVE_DOWN;

            switch (input)
            {
                case InputEvent.MOVE_RIGHT:
                    gameGrid.CurrentPiece.MoveRight();
                    break;

                case InputEvent.MOVE_LEFT:
                    gameGrid.CurrentPiece.MoveLeft();
                    break;

                case InputEvent.MOVE_DOWN:
                    gameGrid.CurrentPiece.MoveDown();
                    break;

                case InputEvent.ROTATE_CW:
                    gameGrid.CurrentPiece.RotateCw();
                    break;

                case InputEvent.ROTATE_ACW:
                    gameGrid.CurrentPiece.RotateAcw();
                    break;

                case InputEvent.DROP_PIECE:
                    DropPiece(true);
                    break;
                default:
                    break;
            }

            return input;
        }

        /** Implement the PLAYING state */
        public void Play(System.Drawing.Graphics g)
        {
            // Input is processed using chain-of-responsibility pattern
            InputEvent input = HandlePieceMovements();

            switch (input)
            {
                case InputEvent.NONE:
                    ProcessInput();
                    return;

                case InputEvent.EXIT:
                    break;

                case InputEvent.PAUSE_GAME:
                    break;

                default:
                    break;
            }

            Grid.PlaceSt placeStatus = gameGrid.GetPlacePiece();

            HashSet<int> fullRows;

            if (placeStatus == Grid.PlaceSt.NO_ROOM_FOR_PIECE)
            {
                // Game over
                gameState = GameState.GAMEOVER;

            }
            else if (placeStatus == Grid.PlaceSt.TOUCH_DOWN)
            {
                // Revert to last (valid) position
                UndoMovePiece();

                // Get the full rows list
                fullRows = FullRows;

                if (fullRows.Count > 0)
                {
                    int scoreK = 1;

                    foreach (int row in fullRows)
                    {
                        FillRow(row, -1);
                        scoreK *= 2;
                    }

                    Score += scoreK * FULL_ROW_SCORE_ODM;
                }

                AckInputEvent();

                RenderScene(g);
                SelectNewPiece();

                Thread.Sleep(fullrowBlinkDalayMs);

                RemoveFullRows();
                RenderScene(g);

                // Turn-off release mode
                DropPiece(false);

                return;
            }
            else
            {
                if (placeStatus != Grid.PlaceSt.OK)
                    UndoMovePiece();

                RenderScene(g);

                // Remove the piece from game area
                RemovePiece();
                ProcessInput();
            }
        }

        /** Implement the BEING state */
        public void Setup()
        {
            gameGrid.Clear();
            previewCanvas.Clear();

            int catalogSize = pFactory.PieceCatalogSize;

            gameGrid.SetCurrentPiece(
                pFactory.Make(randomGenerator.Next(catalogSize)));

            gameGrid.CurrentPiece.MoveCenter(
                gameGrid.ColsCount);

            previewCanvas.SetCurrentPiece(
                pFactory.Make(randomGenerator.Next(catalogSize)));

            _ = previewCanvas.GetPlacePiece();

            DropPiece(false);

            gameState = GameState.PLAYING;
        }

        /** Implement the GAMEOVER state */
        public void GameOver(System.Drawing.Graphics g)
        {
            // Input is processed using chain-of-responsibility pattern
            InputEvent input = Input;

            RenderScene(g);

            if (input == InputEvent.EXIT)
                gameState = GameState.BEGIN;

            ProcessInput();

            String title = "Game Over";
            String message = "Do you want to restart the game ?";

            if (MessageBox.Show(message, title, MessageBoxButtons.YesNo) != DialogResult.Yes)
                System.Environment.Exit(0);
            else
                gameState = GameState.BEGIN;
        }

        /** Runs the game */
        public void Run(System.Drawing.Graphics g)
        {
            switch (gameState)
            {
                case GameState.BEGIN:
                    Setup();
                    break;

                case GameState.PLAYING:
                    Play(g);
                    break;

                case GameState.GAMEOVER:
                    GameOver(g);
                    break;
            }
        }

        public InputManager InputManager => inputMgr;

        public long Score { get => score; set => score = value; }

        private readonly int fullrowBlinkDalayMs = FULL_ROW_BLNK_DL;

        /** Reference to piece factory class */
        private readonly PieceFactory pFactory = new PieceFactory();

        /** Reference to input manager */
        public InputManager inputMgr = new InputManager();

        /** Preview canvas */
        private readonly Grid previewCanvas = new Grid(Piece.COLS, Piece.ROWS);

        /** Game grid instance */
        private readonly Grid gameGrid = new Grid(DEF_COLS, DEF_ROWS);

        /** Last input event */
        private InputEvent lastInput = InputEvent.NONE;

        /** Set to speed up falling of dropped piece */
        bool pieceDropped = false;

        private long score = 0;

        private readonly Random randomGenerator = new Random();
        readonly GridRenderer gridRenderer;
        readonly GridRenderer canvasRenderer;

        /** Holds current game status */
        private GameState gameState = GameState.BEGIN;

        private readonly MainForm mainForm = null;
    }
}

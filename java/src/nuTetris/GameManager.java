/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import java.awt.Font;
import java.awt.GridLayout;
import java.util.Random;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import nuTetris.Grid.PlaceSt;

/**  
 * Builds game components.
 * Processes any input event from Input Manager.
 * Executes the game state machine.
 * Calls the Renderer in order to draw the game scene.
 **/
public class GameManager {

    /** Game states */
    enum GameState {
        BEGIN, PLAYING, GAMEOVER
    };

    /** Game input events */
    public enum InputEvent {
        NONE, MOVE_RIGHT, MOVE_LEFT, MOVE_DOWN, ROTATE_CW, ROTATE_ACW, DROP_PIECE, EXIT, PAUSE_GAME
    };

    /** Default game area columns */
    private final static int DEF_COLS = 10;

    /** Default game area rows */
    private final static int DEF_ROWS = 20;

    /** Default game area width */
    private final static int DEF_XRES = 640;

    /** Default game area height */
    private final static int DEF_YRES = 480;

    /** Initial falling idle timeout (milliseconds) */
    private final static int FALLING_IDLE_INTV = 1000;

    /** 'Full-row blink' delay */
    private final static int FULL_ROW_BLNK_DL = 250;

    /** Score order of magnitude */
    private final static int FULL_ROW_SCORE_ODM = 10;

    protected GameManager(int defCols, int defRows, int fullRowBlinkDalayMs, int defXRes, int defYRes) {

        gameGrid = new Grid(defCols, defRows);
        fullrowBlinkDalayMs = fullRowBlinkDalayMs;
        gridRenderer = new GridRenderer(gameGrid, 0, 0);
        canvasRenderer = new GridRenderer(previewCanvas, 0, 0);

        frame = new JFrame("nuTetris");
        mainPanel = new JPanel(new GridLayout(1, 3));
        frame.add(mainPanel);

        scorePanel = new JPanel();

        scoreLabel = new JLabel("Score:");
        scoreLabel.setFont(new Font("Verdana", 1, 14));
        scorePanel.add(scoreLabel);

        mainPanel.add(scorePanel);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(defXRes, defYRes);

        frame.addKeyListener(inputMgr);
    }

    public GameManager() {
        this(DEF_COLS, DEF_ROWS, FULL_ROW_BLNK_DL, DEF_XRES, DEF_YRES);
    }

    /** Redraw the scene */
    public void renderScene() {

        String scoreText = "Score:" + String.valueOf(score);

        scoreLabel.setText(scoreText);

        gridRenderer.update(mainPanel);
        canvasRenderer.update(mainPanel);

        if (frame.isVisible()) {
            frame.invalidate();
            frame.validate();
            frame.repaint();
        } else {
            frame.setVisible(true);
        }

        try {
            Thread.sleep(pieceDropped ? 10 : 100);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    /** Revert to previous piece position / orientation */
    public void undoMovePiece() {
        gameGrid.currentPiece().undo();
        gameGrid.placePiece();
    }

    /** Take a new piece from catalog */
    public void selectNewPiece() {
        previewCanvas.movePieceToGrid(gameGrid);

        int catalog_size = pFactory.getPieceCatalogSize();

        previewCanvas.setCurrentPiece(pFactory.make(randomGenerator.nextInt(catalog_size)));

        previewCanvas.clear();
        previewCanvas.placePiece();
    }

    /** Acknowledge last input event */
    public void ackInputEvent() {
        lastInput = InputEvent.NONE;
    }

    /** Remove the piece from the game area */
    void removePiece() {
        gameGrid.removePiece();
    }

    /** Process any new input event */
    void processInput() {
        InputManager.EventType ev = inputMgr.poll();

        switch (ev) {
        case DOWN:
            lastInput = InputEvent.ROTATE_ACW;
            break;
        case ESCAPE:
            break;
        case LEFT:
            lastInput = InputEvent.MOVE_LEFT;
            break;
        case RIGHT:
            lastInput = InputEvent.MOVE_RIGHT;
            break;
        case SPACE:
            pieceDropped = true;
            lastInput = InputEvent.MOVE_DOWN;
            break;
        case TIMERTICK:
            lastInput = InputEvent.MOVE_DOWN;
            break;
        case UNKNOWN:
            break;
        case UP:
            lastInput = InputEvent.ROTATE_CW;
            break;
        default:
            lastInput = InputEvent.NONE;
            break;
        }

    }

    // ! Returns and acknowledges last input event
    public InputEvent getInput() {
        InputEvent input = lastInput;
        lastInput = InputEvent.NONE;
        return input;
    }

    /**
     * Set / reset pieceDropped state which causes a series of move down event in
     * order to speed up piece falling
     */
    public void dropPiece(boolean st) {
        pieceDropped = st;

        if (!st)
            ackInputEvent();
    }

    /** Gets a list of completed rows */
    public Set<Integer> getFullRows() {
        return gameGrid.getFullRows();
    }

    /** Fills the cells of a whole row using a given color attribute */
    public void fillRow(int rowIdx, int attr) {
        gameGrid.fillRow(rowIdx, attr);
    }

    /** Remove the completed rows, moving down the other cells */
    public void removeFullRows() {
        gameGrid.removeFullRows();
    }

    /** Processes an input and handles it ! if it is related to piece movement */
    public InputEvent handlePieceMovements() {

        InputEvent input = getInput();

        // Check if no other input is present then
        // if the piece is released create MOVE_DOWN event
        if (pieceDropped && input == InputEvent.NONE)
            input = InputEvent.MOVE_DOWN;

        switch (input) {
        case MOVE_RIGHT:
            gameGrid.currentPiece().moveRight();
            break;

        case MOVE_LEFT:
            gameGrid.currentPiece().moveLeft();
            break;

        case MOVE_DOWN:
            gameGrid.currentPiece().moveDown();
            break;

        case ROTATE_CW:
            gameGrid.currentPiece().rotateCw();
            break;

        case ROTATE_ACW:
            gameGrid.currentPiece().rotateAcw();
            break;

        case DROP_PIECE:
            dropPiece(true);
            break;
        default:
            break;
        }

        return input;
    }

    /** Implement the PLAYING state */
    public void play() {
        // Input is processed using chain-of-responsibility pattern
        InputEvent input = handlePieceMovements();

        switch (input) {
        case NONE:
            processInput();
            return;

        case EXIT:
            break;

        case PAUSE_GAME:
            break;

        default:
            break;
        }

        PlaceSt placeStatus = gameGrid.placePiece();
        Set<Integer> fullRows;

        switch (placeStatus) {
        case NO_ROOM_FOR_PIECE:
            // Game over
            gameState = GameState.GAMEOVER;
            break;

        case TOUCH_DOWN:
            // Revert to last (valid) position
            undoMovePiece();

            // Get the full rows list
            fullRows = getFullRows();

            if (!fullRows.isEmpty()) {
                int scoreK = 1;

                for (int row : fullRows) {
                    fillRow(row, -1);
                    scoreK *= 2;
                }

                score += scoreK * FULL_ROW_SCORE_ODM;
            }

            ackInputEvent();

            renderScene();
            selectNewPiece();

            try {
                Thread.sleep(fullrowBlinkDalayMs);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            removeFullRows();
            renderScene();

            // Turn-off release mode
            dropPiece(false);

            return;

        default:
            if (placeStatus != PlaceSt.OK)
                undoMovePiece();

            renderScene();

            // Remove the piece from game area
            removePiece();
            processInput();
        }
    }

    /** Implement the BEING state */
    public void setup() {
        setIdleIntv(fallingIdleIntv);

        gameGrid.clear();
        previewCanvas.clear();

        int catalogSize = pFactory.getPieceCatalogSize();

        gameGrid.setCurrentPiece(pFactory.make(randomGenerator.nextInt(catalogSize)));

        gameGrid.currentPiece().moveCenter(gameGrid.getColsCount());

        previewCanvas.setCurrentPiece(pFactory.make(randomGenerator.nextInt(catalogSize)));

        previewCanvas.placePiece();

        dropPiece(false);

        gameState = GameState.PLAYING;
    }

    /** Implement the GAMEOVER state */
    public void gameOver() {
        // Input is processed using chain-of-responsibility pattern
        InputEvent input = getInput();

        renderScene();

        if (input == InputEvent.EXIT)
            gameState = GameState.BEGIN;

        processInput();

        String title = "Game Over";
        String message = "Do you want to restart the game ?";

        int reply = JOptionPane.showConfirmDialog(null, message, title, JOptionPane.YES_NO_OPTION);

        if (reply != JOptionPane.YES_OPTION) {
            JOptionPane.showMessageDialog(null, "GOODBYE");
            System.exit(0);
        } else {
            gameState = GameState.BEGIN;
        }

    }

    /** Updates falling timer interval */
    public void setIdleIntv(int intv) {
        inputMgr.changeTick(intv);
    }

    /** Runs the game */
    public void run() {
        switch (gameState) {
        case BEGIN:
            setup();
            break;

        case PLAYING:
            play();
            break;

        case GAMEOVER:
            gameOver();
            break;
        }
    }

    private int fullrowBlinkDalayMs = FULL_ROW_BLNK_DL;

    /** Reference to piece factory class */
    private PieceFactory pFactory = new PieceFactory();

    /** Reference to input manager */
    private InputManager inputMgr = new InputManager(FALLING_IDLE_INTV);

    /** Preview canvas */
    private Grid previewCanvas = new Grid(Piece.COLS, Piece.ROWS);

    /** Game grid instance */
    private Grid gameGrid = new Grid(DEF_COLS, DEF_ROWS);

    /** Last input event */
    private InputEvent lastInput = InputEvent.NONE;

    /** Falling idle timeout (determines the speed of the game) */
    private int fallingIdleIntv = FALLING_IDLE_INTV;

    /** Set to speed up falling of dropped piece */
    boolean pieceDropped = false;

    private long score = 0;

    private Random randomGenerator = new Random();

    GridRenderer gridRenderer;
    GridRenderer canvasRenderer;

    /** Holds current game status */
    private GameState gameState = GameState.BEGIN;

    private JFrame frame;
    private JPanel mainPanel;
    private JPanel scorePanel;
    private JLabel scoreLabel;
}

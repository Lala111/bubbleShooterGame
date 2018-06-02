import acm.program.GraphicsProgram;
import acm.graphics.*;

import java.awt.Color;
import java.awt.event.*;
import java.util.Random;

import javax.swing.JButton;

public class TestGame extends GraphicsProgram {
	private static final long serialVersionUID = 1L;
	boolean isBallMoving = false;
	boolean isMovingLeft = true;
	boolean isMovingRight = true;
	private boolean accelOn;
	private boolean gameStarted;
	private int accel;

	public void init() {
		GImage image = new GImage("java_game1.jpg");
		image.scale(1.3, 1.5);
		add(image);
		add(new JButton("New Game"), SOUTH);
		add(new JButton("How to play?"), SOUTH);
		add(new JButton("EXIT"), SOUTH);
		addMouseListeners();
		addActionListeners();
		addKeyListeners();
	}

	public void run() {
		while (true) {
			moveMainBall();
			checkForCollisions();
			pause(DELAY);
		}
	}

	/*
	 * when mouse is clicked create ball, unless a ball already exists.
	 */
	public void mouseClicked(MouseEvent e) {
		if (!gameStarted)
			return;

		if (mainBall == null) {
			mainBall = new GOval(30, 30);
			((GOval) mainBall).setFilled(true);
			nextRandomColor((GOval) mainBall);
			add(mainBall, (RECT_WIDTH - 30) / 2, RECT_HEIGHT);
		}
	}

	/* moves ball */
	private void moveMainBall() {
		if (mainBall != null) {
			if (isBallMoving) {
				accel = accelOn ? accel + 1 : 0;
				mainBall.move(0, -2 - accel);
			}
		}
	}

	/* Called when any action event is generated */
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("New Game")) {
			removeAll();
			GImage image = new GImage("java_game.jpg");
			image.scale(1.58, 0.54);
			add(image);
			GRect rect = new GRect(30, 30, RECT_WIDTH - 62, RECT_HEIGHT);
			rect.setFilled(false);
			rect.setColor(Color.BLUE);
			add(rect);
			GOval[][] circles = new GOval[MAX_SIZE][MAX_SIZE2];
			for (int i = 0; i < MAX_SIZE; i++) {
				for (int j = 0; j < MAX_SIZE2; j++) {
					oval = new GOval(30, 30);
					((GOval) oval).setFilled(true);
					nextRandomColor((GOval) oval);
					add(oval, (i * 30) + 30, j * 30 + 30);
				}
			}

			gameStarted = true;
		} else if (e.getActionCommand().equals("How to play?")) {
			removeAll();
			GImage image = new GImage("project.png");
			image.scale(0.95, 0.9);
			add(image);
		} else if (e.getActionCommand().equals("EXIT")) {
			removeAll();
			System.exit(0);
		}
	}

	/*
	 * So it checks to see if mainBall and ball collide, if so ball and mainBall
	 * are removed and both variables are set to null. Otherwise, ball and
	 * mainBall should stop to move.
	 */
	private void checkForCollisions() {
		if (mainBall != null) {
			GObject topBall = getElementAt(mainBall.getX() + mainBall.getWidth() / 2, mainBall.getY() - 1);
			GObject leftBall = getElementAt(mainBall.getX() - 1, mainBall.getY() + mainBall.getHeight() / 2);
			GObject rightBall = getElementAt(mainBall.getX() + mainBall.getWidth() - 1, mainBall.getY() + 2);
			if (topBall.getClass() == GOval.class) {
				if (((GOval) topBall).getFillColor().equals(mainBall.getFillColor())) {
					remove(topBall);
					remove(mainBall);
					topBall = null;
					mainBall = null;
				} else {
					isBallMoving = false;
					mainBall = null;
				}
			} else if (leftBall.getClass() == GOval.class) {
				if (((GOval) leftBall).getFillColor().equals(mainBall.getFillColor())) {
					remove(leftBall);
					remove(mainBall);
					leftBall = null;
					mainBall = null;
				}

			} else if (rightBall.getClass() == GOval.class) {
				if (((GOval) rightBall).getFillColor().equals(mainBall.getFillColor())) {
					remove(rightBall);
					remove(mainBall);
					rightBall = null;
					mainBall = null;
				}
			}
		}
	}

	/* give 9 random color. */
	private void nextRandomColor(GOval ov) {
		Random rgen = new Random();
		switch (rgen.nextInt(9)) {
		case 0:
			ov.setFillColor(Color.MAGENTA);
			break;
		case 1:
			ov.setFillColor(Color.GRAY);
			break;
		case 2:
			ov.setFillColor(Color.GREEN);
			break;
		case 3:
			ov.setFillColor(Color.BLUE);
			break;
		case 4:
			ov.setFillColor(Color.ORANGE);
			break;
		case 5:
			ov.setFillColor(Color.YELLOW);
			break;
		case 6:
			ov.setFillColor(Color.PINK);
			break;
		case 7:
			ov.setFillColor(Color.CYAN);
			break;
		case 8:
			ov.setFillColor(Color.RED);
			break;
		}
	}

	/* Called when a key is PRESSED in the window */
	public void keyPressed(KeyEvent e) {
		if (mainBall != null) {
			switch (e.getKeyCode()) {
			case KeyEvent.VK_UP:
				isBallMoving = true;
				accelOn = true;
				break;
			case KeyEvent.VK_LEFT:
				if (mainBall.getX() - mainBall.getWidth() > 0)
					mainBall.move(-3, 0);
				break;
			case KeyEvent.VK_RIGHT:
				if (mainBall.getX() + mainBall.getWidth() < RECT_WIDTH - 35)
					mainBall.move(+3, 0);
				break;
			}
		}
	}

	/* Called when a key is RELEASED in the window */
	public void keyReleased(KeyEvent e) {
		switch (e.getKeyCode()) {
		case KeyEvent.VK_UP:
			accelOn = false;
			break;
		}
	}

	/* Private constants */
	public static final int MAX_SIZE = 23;
	public static final int MAX_SIZE2 = 6;
	public static final int RECT_WIDTH = 754;
	public static final int RECT_HEIGHT = 370;
	private static final int DELAY = 100; // Animation cycle delay

	/* Private instance variables */
	private GOval mainBall;
	private GOval oval;

	public static void main(String[] args) {
		new TestGame().start();
	}
}

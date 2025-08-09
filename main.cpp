#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <tchar.h>
#include <sstream>

// Screen size
const int WIDTH = 480;
const int HEIGHT = 640;

// Player airplane class
class Player {
public:
    int x, y;
    int width, height;
    int speed;
    int lives;

    Player() {
        width = 60;
        height = 80;
        x = WIDTH / 2 - width / 2;
        y = HEIGHT - height - 30;
        speed = 10;
        lives = 3;
    }

    void moveLeft() {
        x -= speed;
        if (x < 0) x = 0;
    }
    void moveRight() {
        x += speed;
        if (x + width > WIDTH) x = WIDTH - width;
    }
    void moveUp() {
        y -= speed;
        if (y < 0) y = 0;
    }
    void moveDown() {
        y += speed;
        if (y + height > HEIGHT) y = HEIGHT - height;
    }

    void draw() {
        setfillcolor(RGB(0, 191, 255)); // DeepSkyBlue
        fillrectangle(x, y, x + width, y + height);
        setlinecolor(RGB(255, 255, 255));
        rectangle(x, y, x + width, y + height);
    }

    RECT getRect() {
        RECT r = { x, y, x + width, y + height };
        return r;
    }
};

// Enemy airplane class
class Enemy {
public:
    int x, y;
    int width, height;
    int speed;

    Enemy(int speed_) {
        width = 50;
        height = 70;
        speed = speed_;
        x = rand() % (WIDTH - width);
        y = -height;
    }

    void update() {
        y += speed;
    }

    void draw() {
        setfillcolor(RGB(255, 69, 0)); // OrangeRed
        fillrectangle(x, y, x + width, y + height);
        setlinecolor(RGB(0, 0, 0));
        rectangle(x, y, x + width, y + height);
    }

    RECT getRect() {
        RECT r = { x, y, x + width, y + height };
        return r;
    }
};

// Check collision between two rectangles
bool isColliding(RECT a, RECT b) {
    return !(a.right < b.left || a.left > b.right || a.bottom < b.top || a.top > b.bottom);
}

// Draw text with Unicode support helper
void drawText(int x, int y, const std::wstring& text, int fontSize = 24, COLORREF color = RGB(255, 255, 255)) {
    settextcolor(color);
    settextstyle(fontSize, 0, _T("Consolas"));
    outtextxy(x, y, text.c_str());
}

// Draw start screen
void drawStartScreen() {
    cleardevice();
    drawText(50, 150, L"Welcome to Airplane Battle Game!", 32, RGB(255, 215, 0));
    drawText(50, 250, L"Arrow Keys to move", 28);
    drawText(50, 300, L"Press SPACE to shoot (not implemented)", 28);
    drawText(50, 350, L"Press P to Pause, ESC to Exit", 28);
    drawText(50, 400, L"Press Enter to Start", 28, RGB(173, 216, 230));
}

// Draw game over screen
void drawGameOverScreen(int score) {
    cleardevice();
    drawText(150, 200, L"Game Over!", 48, RGB(255, 0, 0));

    std::wstringstream ss;
    ss << L"Your score: " << score;
    drawText(150, 300, ss.str(), 36);

    drawText(100, 400, L"Press Enter to Restart or ESC to Quit", 28);
}

// Main game loop
void gameLoop() {
    Player player;
    std::vector<Enemy> enemies;

    int score = 0;
    int enemySpawnInterval = 50;  // frames
    int enemySpeed = 3;
    int frameCount = 0;
    bool paused = false;

    cleardevice();

    while (true) {
        if (kbhit()) {
            char ch = _getch();

            if (ch == 27) {  // ESC key to pause/exit
                paused = !paused;
                if (paused) {
                    drawText(150, 300, L"Game Paused. Press ESC to Resume.", 28, RGB(255, 255, 0));
                }
                else {
                    cleardevice();
                }
                continue;
            }
            if (paused) continue;

            if (ch == 75) player.moveLeft();  // Left arrow
            else if (ch == 77) player.moveRight();  // Right arrow
            else if (ch == 72) player.moveUp();    // Up arrow
            else if (ch == 80) player.moveDown();  // Down arrow
        }

        if (paused) {
            Sleep(100);
            continue;
        }

        // Spawn enemies every interval
        frameCount++;
        if (frameCount % enemySpawnInterval == 0) {
            enemies.push_back(Enemy(enemySpeed));
        }

        // Clear background
        setbkcolor(RGB(0, 0, 20));
        cleardevice();

        // Draw player
        player.draw();

        // Update and draw enemies
        for (size_t i = 0; i < enemies.size(); ) {
            enemies[i].update();

            // Remove enemy if out of screen
            if (enemies[i].y > HEIGHT) {
                enemies.erase(enemies.begin() + i);
                score++;
                // Increase difficulty every 10 points
                if (score % 10 == 0 && enemySpawnInterval > 10) {
                    enemySpawnInterval -= 5;
                    enemySpeed++;
                }
            }
            else {
                enemies[i].draw();
                i++;
            }
        }

        // Collision detection
        RECT playerRect = player.getRect();
        bool collisionDetected = false;
        for (const auto& enemy : enemies) {
            if (isColliding(playerRect, enemy.getRect())) {
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected) {
            player.lives--;
            enemies.clear();
            if (player.lives <= 0) {
                break;  // Game over
            }
        }

        // Draw score and lives
        std::wstringstream ss;
        ss << L"Score: " << score;
        drawText(10, 10, ss.str());

        std::wstringstream ss2;
        ss2 << L"Lives: " << player.lives;
        drawText(350, 10, ss2.str());

        Sleep(30);
    }

    drawGameOverScreen(score);

    while (true) {
        if (_kbhit()) {
            char c = _getch();
            if (c == 13) { // Enter to restart
                gameLoop();
                return;
            }
            else if (c == 27) { // ESC to exit
                return;
            }
        }
    }
}

int main() {
    srand((unsigned)time(nullptr));
    initgraph(WIDTH, HEIGHT);

    drawStartScreen();

    while (true) {
        if (_kbhit()) {
            char c = _getch();
            if (c == 13) {  // Enter key starts game
                gameLoop();
                drawStartScreen();
            }
            else if (c == 27) { // ESC key exits
                break;
            }
        }
        Sleep(50);
    }

    closegraph();
    return 0;
}

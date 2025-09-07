#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h> 

struct point {
    int x;
    int y;
};

class snake {
private:
    std::vector<point> body;
    int dx, dy;

public:
    snake(int startx, int starty) {
        body.push_back({ startx, starty });
        dx = 1;
        dy = 0;
    }

    void changedir(char input) {
        if (input == 'w' && dy == 0) { dx = 0; dy = -1; }
        else if (input == 's' && dy == 0) { dx = 0; dy = 1; }
        else if (input == 'a' && dx == 0) { dx = -1; dy = 0; }
        else if (input == 'd' && dx == 0) { dx = 1; dy = 0; }
    }

    void movement(bool grow = false) {
        point newhead = { body[0].x + dx, body[0].y + dy };
        body.insert(body.begin(), newhead);
        if (!grow) body.pop_back();  // ✅ don’t pop if growing
    }

    void grow() {
        body.push_back(body.back());
    }

    point getHead() const {
        return body[0];
    }

    const std::vector<point>& getBody() const {
        return body;
    }

    bool checkCollision(int width, int height) {
        point head = getHead();

        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return true;
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i].x == head.x && body[i].y == head.y)
                return true;
        }
        return false;
    }
};

class Game {
private:
    int width, height;
    snake Snake;
    point fruit;
    bool gameOver;
    int score;

public:
    Game(int w, int h) : width(w), height(h), Snake(w / 2, h / 2) {
        srand(time(0));
        spawnFruit();
        gameOver = false;
        score = 0;
    }

    void spawnFruit() {
        while (true) {
            fruit = { rand() % width, rand() % height };
            bool onSnake = false;
            for (auto& p : Snake.getBody()) {
                if (p.x == fruit.x && p.y == fruit.y) {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake) break;
        }
    }

    void draw() {
        system("cls");

        for (int i = 0; i < width + 2; i++) std::cout << "#";
        std::cout << "\n";

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == 0) std::cout << "#";

                point head = Snake.getHead();
                if (head.x == x && head.y == y) std::cout << "O";
                else if (fruit.x == x && fruit.y == y) std::cout << "F";
                else {
                    bool printed = false;
                    for (size_t k = 1; k < Snake.getBody().size(); k++) {
                        if (Snake.getBody()[k].x == x && Snake.getBody()[k].y == y) {
                            std::cout << "o";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) std::cout << " ";
                }

                if (x == width - 1) std::cout << "#";
            }
            std::cout << "\n";
        }

        for (int i = 0; i < width + 2; i++) std::cout << "#";
        std::cout << "\n";

        std::cout << "Score: " << score << "\n";
    }

    void input() {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'x') gameOver = true;
            else Snake.changedir(key);
        }
    }

    void logic() {
        bool ateFruit = (Snake.getHead().x == fruit.x && Snake.getHead().y == fruit.y);

        Snake.movement(ateFruit); 

        if (ateFruit) {
            score += 10;
            spawnFruit();
        }

        if (Snake.checkCollision(width, height)) {
            gameOver = true;
        }
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(100); 
        }
        std::cout << "Game Over! Final Score: " << score << "\n";
    }
};

int main() {
    Game game(20, 20);
    game.run();
    return 0;
}

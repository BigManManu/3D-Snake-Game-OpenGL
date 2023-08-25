#include "Bunny.h"

Bunny::Bunny(Snake snake)
{
    bunnyColor = { 1.0, 0.0, 0.0 };
	for (int i = 0; i < NUMBER_OF_BUNNIES+1; i++)
		bunnyLocation[i] = generateRandomLocation(2, 2, FIELD_DEPTH, i, i, snake);
}

Point Bunny::generateRandomLocation(int x, int y, int z, int max, int except, Snake& snake)
{
    while (true) {
        Point loc = { (x - 2 * BUNNY_SIZE) * ((double)rand() / RAND_MAX - .5),
            (y - 2 * BUNNY_SIZE) * ((double)rand() / RAND_MAX - .5),
            (z - 2 * BUNNY_SIZE) * ((double)rand() / RAND_MAX - .3) };
        bool acceptable = true;
        for (int i = 0; i <= snake.bodySegments - 1; i++) {
            int current = (i + snake.firstIndex) % MAX_SEGMENTS;
            int next = (current + 1) % MAX_SEGMENTS;
            Point p = diff(snake.snakeBody[next], snake.snakeBody[current]);
            if (p.x != 0 && (loc.x - snake.snakeBody[current].x) * (loc.x - snake.snakeBody[next].x) <= 0 &&
                (loc.y - snake.snakeBody[current].y) * (loc.y - snake.snakeBody[current].y)
                + (loc.z - snake.snakeBody[current].z) * (loc.z - snake.snakeBody[current].z)
                <= (THICKNESS + BUNNY_SIZE) * (THICKNESS + BUNNY_SIZE)) {
                acceptable = false;
                break;
            }
            if (p.y != 0 && (loc.y - snake.snakeBody[current].y) * (loc.y - snake.snakeBody[next].y) <= 0 &&
                (loc.x - snake.snakeBody[current].x) * (loc.x - snake.snakeBody[current].x)
                + (loc.z - snake.snakeBody[current].z) * (loc.z - snake.snakeBody[current].z)
                <= (THICKNESS + BUNNY_SIZE) * (THICKNESS + BUNNY_SIZE)) {
                acceptable = false;
                break;
            }
            if (p.z != 0 && (loc.z - snake.snakeBody[current].z) * (loc.z - snake.snakeBody[next].z) <= 0 &&
                (loc.x - snake.snakeBody[current].x) * (loc.x - snake.snakeBody[current].x)
                + (loc.y - snake.snakeBody[current].y) * (loc.y - snake.snakeBody[current].y)
                <= (THICKNESS + BUNNY_SIZE) * (THICKNESS + BUNNY_SIZE)) {
                acceptable = false;
                break;
            }
        }
        if (!acceptable)
            continue;
        for (int i = 0; i <= snake.bodySegments; i++) {
            int current = (i + snake.firstIndex) % MAX_SEGMENTS;
            if ((snake.snakeBody[current].x - loc.x) * (snake.snakeBody[current].x - loc.x) +
                (snake.snakeBody[current].y - loc.y) * (snake.snakeBody[current].y - loc.y) +
                (snake.snakeBody[current].z - loc.z) * (snake.snakeBody[current].z - loc.z) <=
                (THICKNESS + BUNNY_SIZE) * (THICKNESS + BUNNY_SIZE)) {
                acceptable = false;
                break;
            }
        }
        if (!acceptable)
            continue;
        for (int i = 0; i < max; i++) {
            if (i == except)
                continue;
            if (euclideanDistanceSquare(loc, bunnyLocation[i]) <= 4 * BUNNY_SIZE * BUNNY_SIZE) {
                acceptable = false;
                break;
            }
        }
        if (acceptable)
            return loc;
    }
}

void Bunny::render(double size, Point loc, bool isGolden)
{
    glPushMatrix();
    glTranslatef(loc.x, loc.y, loc.z);
    glScalef(size, size, size);
    if (isGolden)
        glColor3f(1.0, 0.83, 0.0);
    else
        glColor3f(bunnyColor.r, bunnyColor.g, bunnyColor.b);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i += 3) {
        glVertex3f(vertices[3 * faces[i]], vertices[3 * faces[i] + 1], vertices[3 * faces[i] + 2]);
        glVertex3f(vertices[3 * faces[i + 1]], vertices[3 * faces[i + 1] + 1], vertices[3 * faces[i + 1] + 2]);
        glVertex3f(vertices[3 * faces[i + 2]], vertices[3 * faces[i + 2] + 1], vertices[3 * faces[i + 2] + 2]);
    }
    glColor3f(1.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();
}

void Bunny::load()
{
	loader.load_model(filename, vertices, faces, normals);
}
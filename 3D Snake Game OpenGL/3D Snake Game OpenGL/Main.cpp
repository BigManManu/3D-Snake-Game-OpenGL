#include "Resource.h"


void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, EYE_Z, //< eye position
        0.0f, 0.0f, 0.0f,  //< aim position
        0.0f, 1.f, 0.0f); //< up direction
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);


    GLfloat mat_specular[] = { 0.0, 1.0, 0.0,1 };
    GLfloat mat_specularback[] = { 1.0, 0.0, 0.0, 0.0 };
    GLfloat mat_shininess[] = { .2 };
    GLfloat mat_shininessback[] = { .5 };
    GLfloat light_position0[] = { -1, -1.0, 1.0, 0 };
    GLfloat light_position1[] = { 0.5, 0.5, 0.5, 0 };
    GLfloat ambient[] = { 1,1, 1, 0 };
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_BACK, GL_SPECULAR, mat_specularback);
    glMaterialfv(GL_BACK, GL_SHININESS, mat_shininessback);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);



    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_START, DNEAR);
    glFogf(GL_FOG_END, EYE_Z);
    glFogf(GL_FOG_DENSITY, .14);

    color = snake.color;
    up = snake.snakeUp;
    snake.snakeBody[0] = { 0,0,INITIAL_Z };
    snake.snakeBody[1] = { INITIAL_LENGTH, 0, INITIAL_Z };
    bunny.load();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (defaultCamera) {
        camera.WorldCamera(x, y, EYE_Z, x, y);
    }
    if (gameover) {
        glColor4f(1, 0, 0, ((double)blinking) / BLINKING_PERIOD);
        Gui::GameHud(0.4, 0.5, (void*)font, "GAME OVER");
    }
    if (!moving) {
        if (playing) {
            glColor4f(0, 0, 1, ((double)blinking) / BLINKING_PERIOD);
            Gui::GameHud(0.43, 0.5, (void*)font, "PAUSED");
        }
        else {
            glColor4f(0, 0, 1, ((double)blinking) / BLINKING_PERIOD);
            Gui::GameHud(0.33, 0.5, (void*)font, "PRESS SPACE TO START");
        }
    }
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateZ, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthMask(GL_FALSE);
    border.cube(3);
    glDepthMask(GL_TRUE);
    glPolygonMode(GL_FRONT, GL_FILL);
    snake.render(THICKNESS, TAIL_THICKNESS, color, up);
    for (int i = 0; i < NUMBER_OF_BUNNIES; i++) {
        double brightness = 1.0;
        glColor4f(brightness, .3 * brightness, .3 * brightness, .9);
        glPushMatrix();
        glTranslatef(bunny.bunnyLocation[i].x, bunny.bunnyLocation[i].y, bunny.bunnyLocation[i].z);
        glRotatef(bunnyRotDegree + (i + 1) * 360.0 / NUMBER_OF_BUNNIES, 0, 1, 0);
        glTranslatef(-bunny.bunnyLocation[i].x, -bunny.bunnyLocation[i].y, -bunny.bunnyLocation[i].z);
        bunny.render(BUNNY_SIZE, bunny.bunnyLocation[i], false);
        glPopMatrix();
    }
    if (spawnGoldenBunny) {
        double brightness = 1.0;
        glColor4f(brightness, .3 * brightness, .3 * brightness, .9);
        glPushMatrix();
        glTranslatef(bunny.bunnyLocation[NUMBER_OF_BUNNIES].x, bunny.bunnyLocation[NUMBER_OF_BUNNIES].y, bunny.bunnyLocation[NUMBER_OF_BUNNIES].z);
        glRotatef(bunnyRotDegree + (NUMBER_OF_BUNNIES + 1) * 360.0 / NUMBER_OF_BUNNIES, 0, 1, 0);
        glTranslatef(-bunny.bunnyLocation[NUMBER_OF_BUNNIES].x, -bunny.bunnyLocation[NUMBER_OF_BUNNIES].y, -bunny.bunnyLocation[NUMBER_OF_BUNNIES].z);
        bunny.render(BUNNY_SIZE, bunny.bunnyLocation[NUMBER_OF_BUNNIES], true);
        glPopMatrix();
    }
    Gui::GameHud((void*)font, snake.score);
    if (debug)
        Gui::DebugHud((void*)font, snake);
    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, SPEED, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, EYE_Z, 0, 0, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    glMatrixMode(GL_MODELVIEW);
    switch (key) {
    case 'd':
    case 'D':
        debug = !debug;
        break;
    case 'x'://rotate the shape about x-axis
    case 'X':
        rotateX += key > 'a' ? -3. : 3;
        glutPostRedisplay();
        break;
    case 'y'://rotate the shape about y-axis
    case 'Y':
        rotateY += key > 'a' ? -3. : 3;
        glutPostRedisplay();
        break;
    case 'z'://rotate the shape about z-axis
    case 'Z':
        rotateZ += key > 'a' ? -3. : 3;
        glutPostRedisplay();
        break;
    case '+'://scaling up the shape uniformly
        scaleFactor *= 1.05;
        glutPostRedisplay();
        break;
    case '-'://scaling down the shape uniformly
        scaleFactor *= .95;
        glutPostRedisplay();
        break;
    case 'i':
    case 'I':
        glLoadIdentity();
        gluLookAt(0, 0, EYE_Z, 0, 0, 0, 0, 1, 0);
        x = 0.0, y = 0.0, scaleFactor = 1, rotateX = 0, rotateY = 0, rotateZ = 0;
        glutPostRedisplay();
        break;
    case ' ':
        if (!gameover)
            moving = !moving;
        playing = true;
        break;
    case '1':
        defaultCamera = true;
        break;
    case '2':
        defaultCamera = false;
        break;
    case 27:
        exit(0);
        break;
    }
}

void pressSpecialKey(int key, int xx, int yy)
{
    int current = (snake.bodySegments + snake.firstIndex - 1) % (MAX_SEGMENTS);
    int next = (current + 1) % (MAX_SEGMENTS);
    Point p = snake.diff(snake.snakeBody[next], snake.snakeBody[current]);
    double len = (p.x < 0 ? -p.x : p.x) + (p.y < 0 ? -p.y : p.y) + (p.z < 0 ? -p.z : p.z);
    Point change = { 0,0,0 };
    switch (key) {
    case GLUT_KEY_UP:
        if (len >= 6 * THICKNESS && moving) {
            snake.bodySegments++;
            if (p.x != 0) {
                if (defaultCamera) {
                    change.y = SPEED;
                    if (snake.snakeUp.y != 0)
                        snake.snakeUp = { p.x > 0 ? -1.0 : 1.0,0,0 };
                }
                else {
                    if (snake.snakeUp.z != 0)
                        change.z = snake.snakeUp.z > 0 ? SPEED : -SPEED;
                    else
                        change.y = snake.snakeUp.y > 0 ? SPEED : -SPEED;
                    snake.snakeUp = { p.x > 0 ? -1.0 : 1.0, 0, 0 };
                }
            }
            else if (p.y != 0) {
                if (defaultCamera)
                    change.z = SPEED;
                else {
                    if (snake.snakeUp.z != 0)
                        change.z = snake.snakeUp.z > 0 ? SPEED : -SPEED;
                    else
                        change.x = snake.snakeUp.x > 0 ? SPEED : -SPEED;
                }
                snake.snakeUp = { 0, p.y > 0.0 ? -1.0 : 1, 0 };
            }
            else {
                if (defaultCamera)
                    change.y = SPEED;
                else {
                    if (snake.snakeUp.y != 0)
                        change.y = snake.snakeUp.y > 0 ? SPEED : -SPEED;
                    else
                        change.x = snake.snakeUp.x > 0 ? SPEED : -SPEED;
                }
                snake.snakeUp = { 0, 0, p.z > 0 ? -1.0 : 1.0 };
            }
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS] =
            { snake.snakeBody[next].x + change.x, snake.snakeBody[next].y + change.y, snake.snakeBody[next].z + change.z };
        }
        break;
    case GLUT_KEY_DOWN:
        if (len >= 6 * THICKNESS && moving) {
            snake.bodySegments++;
            if (p.x != 0) {
                if (defaultCamera) {
                    change.y = -SPEED;
                    if (snake.snakeUp.y != 0)
                        snake.snakeUp = { p.x > 0 ? 1.0 : -1.0,0,0 };
                }
                else {
                    if (snake.snakeUp.z != 0)
                        change.z = snake.snakeUp.z > 0 ? -SPEED : SPEED;
                    else
                        change.y = snake.snakeUp.y > 0 ? -SPEED : SPEED;
                    snake.snakeUp = { p.x > 0 ? 1.0 : -1.0, 0, 0 };
                }
            }
            else if (p.y != 0) {
                if (defaultCamera)
                    change.z = -SPEED;
                else {
                    if (snake.snakeUp.z != 0)
                        change.z = snake.snakeUp.z > 0 ? -SPEED : SPEED;
                    else
                        change.x = snake.snakeUp.x > 0 ? -SPEED : SPEED;
                }
                snake.snakeUp = { 0, p.y > 0 ? 1.0 : -1.0, 0 };
            }
            else {
                if (defaultCamera)
                    change.y = -SPEED;
                else {
                    if (snake.snakeUp.y != 0)
                        change.y = snake.snakeUp.y > 0 ? -SPEED : SPEED;
                    else
                        change.x = snake.snakeUp.x > 0 ? -SPEED : SPEED;
                }
                snake.snakeUp = { 0, 0, p.z > 0 ? 1.0 : -1.0 };
            }
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS] =
            { snake.snakeBody[next].x + change.x, snake.snakeBody[next].y + change.y, snake.snakeBody[next].z + change.z };
        }
        break;
    case GLUT_KEY_RIGHT:
        if (len >= 6 * THICKNESS && moving) {
            snake.bodySegments++;
            if (p.x != 0) {
                if (defaultCamera) {
                    change.z = SPEED;
                    snake.snakeUp = { p.x > 0 ? -1.0 : 1.0, 0, 0 };
                }
                else {
                    if (snake.snakeUp.z != 0)
                        change.y = snake.snakeUp.z * p.x > 0 ? -SPEED : SPEED;
                    else
                        change.z = snake.snakeUp.y > 0 * p.x ? SPEED : -SPEED;
                }
            }
            else if (p.y != 0) {
                if (defaultCamera)
                    change.x = SPEED;
                else {
                    if (snake.snakeUp.z != 0)
                        change.x = snake.snakeUp.z * p.y > 0 ? SPEED : -SPEED;
                    else
                        change.z = snake.snakeUp.x * p.y > 0 ? -SPEED : SPEED;
                }

            }
            else {
                if (defaultCamera)
                    change.x = SPEED;
                else {
                    if (snake.snakeUp.y != 0)
                        change.x = p.z * snake.snakeUp.y > 0 ? -SPEED : SPEED;
                    else
                        change.y = p.z * snake.snakeUp.x > 0 ? SPEED : -SPEED;
                }
            }
        }
        snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS] =
        { snake.snakeBody[next].x + change.x, snake.snakeBody[next].y + change.y, snake.snakeBody[next].z + change.z };
        break;
    case GLUT_KEY_LEFT:
        if (len >= 6 * THICKNESS && moving) {
            snake.bodySegments++;
            if (p.x != 0) {
                if (defaultCamera) {
                    change.z = -SPEED;
                    snake.snakeUp = { p.x > 0 ? 1.0 : -1.0, 0, 0 };
                }
                else {
                    if (snake.snakeUp.z != 0)
                        change.y = snake.snakeUp.z * p.x > 0 ? SPEED : -SPEED;
                    else
                        change.z = snake.snakeUp.y > 0 * p.x ? -SPEED : SPEED;
                }
            }
            else if (p.y != 0) {
                if (defaultCamera)
                    change.x = -SPEED;
                else {
                    if (snake.snakeUp.z != 0)
                        change.x = snake.snakeUp.z * p.y > 0 ? -SPEED : SPEED;
                    else
                        change.z = snake.snakeUp.x * p.y > 0 ? SPEED : -SPEED;
                }
            }
            else {
                if (defaultCamera) {
                    change.x = -SPEED;
                }
                else {
                    if (snake.snakeUp.y != 0)
                        change.x = p.z * snake.snakeUp.y > 0 ? SPEED : -SPEED;
                    else
                        change.y = p.z * snake.snakeUp.x > 0 ? -SPEED : SPEED;
                }
                if (snake.snakeUp.x != 0)
                    snake.snakeUp = { 0, 0, snake.snakeUp.x > 0 ? -1.0 : 1.0 };
            }
        }
        snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS] =
        { snake.snakeBody[next].x + change.x, snake.snakeBody[next].y + change.y, snake.snakeBody[next].z + change.z };
        break;
    case GLUT_KEY_HOME: deltaYMove = 1.0; break;
    case GLUT_KEY_END: deltaYMove = -1.0; break;
    case GLUT_KEY_PAGE_UP: deltaXMove = 1.0; break;
    case GLUT_KEY_INSERT: deltaXMove = -1.0; break;
    }
}

void releaseSpecialKey(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_HOME: deltaYMove = 0.0; break;
        case GLUT_KEY_END: deltaYMove = 0.0; break;
        case GLUT_KEY_PAGE_UP: deltaXMove = 0.0; break;
        case GLUT_KEY_INSERT: deltaXMove = 0.0; break;
    }
}

void update(void)
{
    x += deltaXMove * 0.003 * scaleFactor;
    y += deltaYMove * 0.003 * scaleFactor;
    bunnyRotDegree = bunnyRotDegree > 360 ? 1 : bunnyRotDegree + 1;
    blinking = (blinking + 1) % BLINKING_PERIOD;
    if (moving && !gameover) {
        Point dTail = snake.diff(snake.snakeBody[(1 + snake.firstIndex) % (MAX_SEGMENTS)], snake.snakeBody[snake.firstIndex]);
        Point dHead = snake.diff(snake.snakeBody[(snake.bodySegments + snake.firstIndex) % (MAX_SEGMENTS)],
            snake.snakeBody[(snake.firstIndex + snake.bodySegments - 1) % (MAX_SEGMENTS)]);
        double val = abs(dTail.x + dTail.y + dTail.z);
        if (val <= 2 * THICKNESS) {
            if (dHead.x != 0)
                snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].x += dHead.x > 0 ? SPEED * (M_PI - 2) / 2 : -SPEED * (M_PI - 2) / 2;
            else if (dHead.y != 0)
                snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].y += dHead.y > 0 ? SPEED * (M_PI - 2) / 2 : -SPEED * (M_PI - 2) / 2;
            else
                snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z += dHead.z > 0 ? SPEED * (M_PI - 2) / 2 : -SPEED * (M_PI - 2) / 2;
        }
        if (val <= SPEED) {
            snake.bodySegments--;
            snake.firstIndex = (snake.firstIndex + 1) % (MAX_SEGMENTS);
            dTail = snake.diff(snake.snakeBody[(1 + snake.firstIndex) % (MAX_SEGMENTS)], snake.snakeBody[snake.firstIndex]);
            if (dTail.x != 0)
                snake.snakeBody[snake.firstIndex].x += dTail.x > 0 ? (M_PI - 2) * THICKNESS : -(M_PI - 2) * THICKNESS;
            else if (dTail.y != 0)
                snake.snakeBody[snake.firstIndex].y += dTail.y > 0 ? (M_PI - 2) * THICKNESS : -(M_PI - 2) * THICKNESS;
            else
                snake.snakeBody[snake.firstIndex].z += dTail.z > 0 ? (M_PI - 2) * THICKNESS : -(M_PI - 2) * THICKNESS;
        }
        else if (eaten == 0)
            if (dTail.x != 0)
                snake.snakeBody[snake.firstIndex].x += dTail.x > 0 ? SPEED : -SPEED;
            else if (dTail.y != 0)
                snake.snakeBody[snake.firstIndex].y += dTail.y > 0 ? SPEED : -SPEED;
            else
                snake.snakeBody[snake.firstIndex].z += dTail.z > 0 ? SPEED : -SPEED;
        else
            eaten--;
        if (dHead.x != 0)
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].x += dHead.x > 0 ? SPEED : -SPEED;
        else if (dHead.y != 0)
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].y += dHead.y > 0 ? SPEED : -SPEED;
        else
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z += dHead.z > 0 ? SPEED : -SPEED;

        if (abs(snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].x) >= 1 ||
            abs(snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].y) >= 1 ||
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z >= EYE_Z - 1 ||
            snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z <= -1 ||
            snake.snakeCrossesItself()) {
            gameover = true;
        }
        int ate = snake.eatsBunny(bunny.bunnyLocation, spawnGoldenBunny, snake);
        if (ate >= 0) {
            int chance = rand() % 100;
            if (chance >= 80 && !spawnGoldenBunny)
                spawnGoldenBunny = true;
            eaten = GROW_WHEN_EAT;
            bunny.bunnyLocation[ate] = bunny.generateRandomLocation(2, 2, FIELD_DEPTH, NUMBER_OF_BUNNIES, ate, snake);
        }
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	argc = 1;
	argv[1] = { (char*)"3D Snake" };
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 200);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutIdleFunc(update); 
    glutMainLoop();
	return 0;
}
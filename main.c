#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 100

#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

typedef struct {
    int type;      // 1=Line, 2=Rectangle, 3=Circle, 4=Triangle

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;

    int active;
} Object;

Object objects[MAX_OBJECTS];
int objectCount = 0;

/* ---------------- Canvas Functions ---------------- */

void clearPicture() {
    int y, x;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            picture[y][x] = EMPTY;
        }
    }
}

void displayPicture() {
    int y, x;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            printf("%c", picture[y][x]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH &&
        y >= 0 && y < HEIGHT) {
        picture[y][x] = PIXEL;
    }
}

/* ---------------- Line ---------------- */

void drawLine(int x1, int y1, int x2, int y2) {

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1) {

        setPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/* ---------------- Rectangle ---------------- */

void drawRectangle(int x1, int y1, int x2, int y2) {

    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

/* ---------------- Circle ---------------- */

void drawCircle(int cx, int cy, int radius) {

    int x = 0;
    int y = radius;
    int d = 1 - radius;

    while (x <= y) {

        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);

        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }

        x++;
    }
}

/* ---------------- Triangle ---------------- */

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3) {

    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

/* ---------------- Object Drawing ---------------- */

void drawObject(Object obj) {

    if (!obj.active)
        return;

    switch (obj.type) {

    case 1:
        drawLine(
            obj.x1, obj.y1,
            obj.x2, obj.y2
        );
        break;

    case 2:
        drawRectangle(
            obj.x1, obj.y1,
            obj.x2, obj.y2
        );
        break;

    case 3:
        drawCircle(
            obj.x1,
            obj.y1,
            obj.radius
        );
        break;

    case 4:
        drawTriangle(
            obj.x1, obj.y1,
            obj.x2, obj.y2,
            obj.x3, obj.y3
        );
        break;
    }
}

/* ---------------- Redraw Picture ---------------- */

void redrawPicture() {

    clearPicture();

    for (int i = 0; i < objectCount; i++) {
        drawObject(objects[i]);
    }
}

/* ---------------- Add Object ---------------- */

void addObject() {

    Object obj;

    printf("\nChoose shape type:\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");

    printf("Enter shape type: ");
    scanf("%d", &obj.type);

    obj.active = 1;

    switch (obj.type) {

    case 1:
        printf("Enter x1 y1 x2 y2: ");
        scanf("%d %d %d %d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2);
        break;

    case 2:
        printf("Enter top-left x y and bottom-right x y: ");
        scanf("%d %d %d %d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2);
        break;

    case 3:
        printf("Enter center x y and radius: ");
        scanf("%d %d %d",
              &obj.x1,
              &obj.y1,
              &obj.radius);
        break;

    case 4:
        printf("Enter x1 y1 x2 y2 x3 y3: ");
        scanf("%d %d %d %d %d %d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2,
              &obj.x3, &obj.y3);
        break;

    default:
        printf("Invalid shape type.\n");
        return;
    }

    if (objectCount < MAX_OBJECTS) {

        objects[objectCount] = obj;

        printf("Object added with index %d.\n",
               objectCount);

        objectCount++;

        redrawPicture();
    }
}

/* ---------------- Delete Object ---------------- */

void deleteObject() {

    int index;

    printf("Enter object index: ");
    scanf("%d", &index);

    if (index >= 0 &&
        index < objectCount &&
        objects[index].active) {

        objects[index].active = 0;

        printf("Object deleted.\n");

        redrawPicture();
    }
    else {
        printf("Invalid object index.\n");
    }
}

/* ---------------- Modify Object ---------------- */

void modifyObject() {

    int index;

    printf("Enter object index: ");
    scanf("%d", &index);

    if (index < 0 ||
        index >= objectCount ||
        !objects[index].active) {

        printf("Invalid object index.\n");
        return;
    }

    Object *obj = &objects[index];

    switch (obj->type) {

    case 1:
        printf("Enter new x1 y1 x2 y2: ");
        scanf("%d %d %d %d",
              &obj->x1, &obj->y1,
              &obj->x2, &obj->y2);
        break;

    case 2:
        printf("Enter new top-left x y and bottom-right x y: ");
        scanf("%d %d %d %d",
              &obj->x1, &obj->y1,
              &obj->x2, &obj->y2);
        break;

    case 3:
        printf("Enter new center x y and radius: ");
        scanf("%d %d %d",
              &obj->x1,
              &obj->y1,
              &obj->radius);
        break;

    case 4:
        printf("Enter new x1 y1 x2 y2 x3 y3: ");
        scanf("%d %d %d %d %d %d",
              &obj->x1, &obj->y1,
              &obj->x2, &obj->y2,
              &obj->x3, &obj->y3);
        break;
    }

    printf("Object modified.\n");

    redrawPicture();
}

/* ---------------- List Objects ---------------- */

void listObjects() {

    printf("\nObjects:\n");

    for (int i = 0; i < objectCount; i++) {

        if (!objects[i].active)
            continue;

        printf("Index %d : ", i);

        switch (objects[i].type) {

        case 1:
            printf("Line\n");
            break;

        case 2:
            printf("Rectangle\n");
            break;

        case 3:
            printf("Circle\n");
            break;

        case 4:
            printf("Triangle\n");
            break;
        }
    }
}

/* ---------------- Main ---------------- */

int main() {

    int choice;

    clearPicture();

    while (1) {

        printf("\n2D Graphics Editor\n");
        printf("Canvas size: %d x %d\n",
               WIDTH, HEIGHT);

        printf("1. Add object\n");
        printf("2. Delete object\n");
        printf("3. Modify object\n");
        printf("4. Display picture\n");
        printf("5. List objects\n");
        printf("0. Exit\n");

        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {

        case 1:
            addObject();
            break;

        case 2:
            deleteObject();
            break;

        case 3:
            modifyObject();
            break;

        case 4:
            displayPicture();
            break;

        case 5:
            listObjects();
            break;

        case 0:
            printf("Goodbye.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
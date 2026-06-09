#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

/* Initialize canvas */
void initCanvas()
{
    int i, j;
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

/* Display canvas */
void displayCanvas()
{
    int i, j;

    printf("\n");
    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

/* Plot a point */
void plot(int x, int y, char ch)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
        canvas[y][x] = ch;
}

/* Draw Rectangle */
void drawRectangle(int x, int y, int width, int height, char ch)
{
    int i;

    for(i = x; i <= x + width; i++)
    {
        plot(i, y, ch);
        plot(i, y + height, ch);
    }

    for(i = y; i <= y + height; i++)
    {
        plot(x, i, ch);
        plot(x + width, i, ch);
    }
}

/* Draw Line - Bresenham */
void drawLine(int x1, int y1, int x2, int y2, char ch)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        plot(x1, y1, ch);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/* Draw Circle - Midpoint Circle */
void drawCircle(int xc, int yc, int r, char ch)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    while(x <= y)
    {
        plot(xc + x, yc + y, ch);
        plot(xc - x, yc + y, ch);
        plot(xc + x, yc - y, ch);
        plot(xc - x, yc - y, ch);

        plot(xc + y, yc + x, ch);
        plot(xc - y, yc + x, ch);
        plot(xc + y, yc - x, ch);
        plot(xc - y, yc - x, ch);

        if(d < 0)
            d += 2 * x + 3;
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

/* Draw Triangle */
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3,
                  char ch)
{
    drawLine(x1, y1, x2, y2, ch);
    drawLine(x2, y2, x3, y3, ch);
    drawLine(x3, y3, x1, y1, ch);
}

int main()
{
    int choice;

    initCanvas();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Delete Rectangle\n");
        printf("6. Delete Line\n");
        printf("7. Delete Circle\n");
        printf("8. Delete Triangle\n");
        printf("9. Display Canvas\n");
        printf("10. Clear Canvas\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int x, y, w, h;
                printf("Enter x y width height: ");
                scanf("%d%d%d%d", &x, &y, &w, &h);
                drawRectangle(x, y, w, h, '*');
                break;
            }

            case 2:
            {
                int x1, y1, x2, y2;
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &x1, &y1, &x2, &y2);
                drawLine(x1, y1, x2, y2, '*');
                break;
            }

            case 3:
            {
                int xc, yc, r;
                printf("Enter centerX centerY radius: ");
                scanf("%d%d%d", &xc, &yc, &r);
                drawCircle(xc, yc, r, '*');
                break;
            }

            case 4:
            {
                int x1,y1,x2,y2,x3,y3;
                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d%d%d%d%d%d",
                      &x1,&y1,&x2,&y2,&x3,&y3);

                drawTriangle(x1,y1,x2,y2,x3,y3,'*');
                break;
            }

            /* Delete operations */
            case 5:
            {
                int x,y,w,h;
                printf("Enter rectangle details: ");
                scanf("%d%d%d%d",&x,&y,&w,&h);
                drawRectangle(x,y,w,h,'_');
                break;
            }

            case 6:
            {
                int x1,y1,x2,y2;
                printf("Enter line details: ");
                scanf("%d%d%d%d",
                      &x1,&y1,&x2,&y2);

                drawLine(x1,y1,x2,y2,'_');
                break;
            }

            case 7:
            {
                int xc,yc,r;
                printf("Enter circle details: ");
                scanf("%d%d%d",&xc,&yc,&r);

                drawCircle(xc,yc,r,'_');
                break;
            }

            case 8:
            {
                int x1,y1,x2,y2,x3,y3;

                printf("Enter triangle details: ");
                scanf("%d%d%d%d%d%d",
                      &x1,&y1,&x2,&y2,&x3,&y3);

                drawTriangle(x1,y1,x2,y2,x3,y3,'_');
                break;
            }

            case 9:
                displayCanvas();
                break;

            case 10:
                initCanvas();
                printf("Canvas cleared.\n");
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
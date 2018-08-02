#include "TXLib.h"

struct Otvet
{
    int x;
    int y;
    const char* text;
    COLORREF color;
};

struct Vopros
{
    const char* text;
    HDC* fon;
    Otvet otvet1;
    Otvet otvet2;
    Otvet otvet3;
};

void drawOtvet(Otvet* otvet)
{
    txSetFillColor(otvet->color);
    txRectangle(otvet->x, otvet->y, otvet->x + 150, otvet->y + 100);
    txDrawText (otvet->x, otvet->y, otvet->x + 150, otvet->y + 100, otvet->text);
}

void drawFormulirovkaVoprosa(const char* text)
{
    txSetFillColor(TX_GRAY);
    txRectangle(100, 100, 500, 200);
    txDrawText (100, 100, 500, 200, text);
}

void drawVopros(Vopros* vopros)
{
    txBitBlt (txDC(), 0, 0, txGetExtentX(), txGetExtentY(), *vopros->fon, 0, 0);

    drawFormulirovkaVoprosa(vopros->text);
    drawOtvet(&vopros->otvet1);
    drawOtvet(&vopros->otvet2);
}

void drawNextQuestionButton()
{
    txSetFillColor(TX_BLACK);
    txRectangle(500, 50, 550, 100);
    txDrawText (500, 50, 550, 100, ">>>>");
}

void drawPrevQuestionButton()
{
    txSetFillColor(TX_BLACK);
    txRectangle(50, 50, 100, 100);
    txDrawText (50, 50, 100, 100, "<<<<");
}

int main()
{
    txCreateWindow(600, 400);

    Vopros voprosy[20];
    HDC fon = txLoadImage ("1.bmp");
    voprosy[1] = {"Учителъ - это?!", &fon, {100, 250, "Гитлер!", TX_ORANGE},{350, 250, "Абрамов!", TX_GREEN}};
    voprosy[2] = {"Вася - это?!", &fon, {100, 250, "Пупкин!", TX_RED},{350, 250, "Пупок!", TX_ORANGE},{200, 10, "ВОРОНИН!!!!", TX_ORANGE}};
    voprosy[3] = {"Винни - это?!", &fon, {100, 250, "Пух!", TX_ORANGE},{350, 250, "Медведь!", TX_GREEN}};
    voprosy[4] = {"Пеппа - это?!", &fon, {100, 250, "Свинка!", TX_ORANGE},{350, 250, "Хрюшка!", TX_GREEN}};
    voprosy[5] = {"Люся - это?!", &fon, {100, 250, "Леня!", TX_RED},{350, 250, "Костя!", TX_GREEN},{200, 0, "Даня!", TX_PINK}}; //BRUTAL COLOUR

    int nomerVoprosa = 1;
    Vopros vopros = voprosy[nomerVoprosa];

    while (!GetAsyncKeyState(VK_ESCAPE)) {

        drawVopros(&vopros);
        drawNextQuestionButton();
        drawPrevQuestionButton();

        //Предыдущий вопрос
        if (txMouseButtons() & 1) {
            if (txMouseX() >= 50 and txMouseX() <= 100 and
                txMouseY() >= 50 and txMouseY() <= 100) {
                nomerVoprosa = nomerVoprosa - 1;
                if (nomerVoprosa >= 1 and nomerVoprosa <= 5) {
                    vopros = voprosy[nomerVoprosa];
                }
                txSleep(1000);
            }
        }

        //Следующий вопрос
        if (txMouseButtons() & 1) {
            if (txMouseX() >=500 and txMouseX() <= 550 and
                txMouseY() >= 50 and txMouseY() <= 100) {
                nomerVoprosa = nomerVoprosa + 1;
                if (nomerVoprosa >= 1 and nomerVoprosa <= 5) {
                    vopros = voprosy[nomerVoprosa];
                }
                txSleep(1000);
            }
        }

        txSleep(10);
    }

    return 0;
}

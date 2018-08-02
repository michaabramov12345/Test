#include "TXLib.h"

void drawQuestion(const char* text)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, text);
}

void drawAnswer(int x1, int y1, int x2, int y2, const char* text)
{
    txRectangle(x1, y1, x2, y2);
    txDrawText(x1, y1, x2, y2, text);
}

int main()
{
    txCreateWindow(900, 600);

    //Текст вопроса
    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос");
    drawAnswer(100, 250, 300, 350, "Это ответ1");
    drawAnswer(600, 250, 800, 350, "Это ответ2");
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос2");
    drawAnswer(100, 250, 300, 350, " ответ1");
    drawAnswer(600, 250, 800, 350, " ответ2");
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос3");
    drawAnswer(100, 250, 300, 350, "Это ответ1");
    drawAnswer(600, 250, 800, 350, "Это ответ2");
    txSleep(3000);


    return 0;
}

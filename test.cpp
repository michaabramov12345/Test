#include "TXLib.h"

struct Answer
{
    int x1;
    int y1;
    int x2;
    int y2;
    const char* text;
};

void drawQuestion(const char* text)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, text);
}

void drawAnswer(Answer ans)
{
    txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

int main()
{
    txCreateWindow(900, 600);

    //Текст вопроса
    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос");
    Answer ans1 = {100, 250, 300, 350, "Это ответ1"};
    Answer ans2 = {600, 250, 800, 350, "Это ответ2"};
    drawAnswer(ans1);
    drawAnswer(ans2);
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос2");
    ans1 = {100, 250, 300, 350, " ответ1"};
    ans2 = {600, 250, 800, 350, " ответ2"};
    drawAnswer(ans1);
    drawAnswer(ans2);
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("Это вопрос3");
    ans1 = {100, 250, 300, 350, "Это ответ1"};
    ans2 = {600, 250, 800, 350, "Это ответ2"};
    drawAnswer(ans1);
    drawAnswer(ans2);
    txSleep(3000);


    return 0;
}

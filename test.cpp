#include "TXLib.h"

struct Answer
{
    //Обязательные
    const char* text;
    bool pravilnyi;
    //Необязательные
    HDC pic;
    int x1;
    int y1;
    int x2;
    int y2;
};

void drawAnswer(Answer ans)
{
    txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    if (ans.pic != nullptr)
    {
        txBitBlt (txDC(), ans.x1, ans.y1, ans.x2 - ans.x1, ans.y2 - ans.y1, ans.pic, 130, 150);
    }
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

struct Question
{
    //Обязательные
    const char* text;
    Answer ans[100];
    //Необязательные
    int count_answers;
};

void drawQuestion(Question que)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, que.text);

    for (int nomer = 0; nomer < que.count_answers; nomer++)
    {
        drawAnswer(que.ans[nomer]);
    }
}

int main()
{
    txCreateWindow(900, 500);

    Question que[100];
    int count_questions = 0;
    int kolichestvo_pravilnyh = 0;
    char stroka_dlya_kolichestvo_pravilnyh[100];

    //Заполняем вопросы нормально
    {
    que[count_questions++] = {"Выберите число",
        {{"1", true, txLoadImage("Бузова.bmp")},
         {"Курица", false},
         {"g", false},
         {"456", false},
         {"dfg", false}}
    };
    que[count_questions++] = {"Это невопрос. Все ответы правильные",
        {{"Это ответ1", true, que[0].ans[0].pic},
         {"Это ответ2", true},
         {"Это ответ3", true}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"Вася", false},
         {"Вася", false},
         {"15", true}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"15", true}}
    };
    }


    //Считаем количество ответов и расставляем их
    for (int nomer = 0; nomer < count_questions; nomer++)
    {
        for (int otvet = 0; otvet < 100; otvet++)
        {
            if (que[nomer].ans[otvet].text == nullptr)
            {
                que[nomer].count_answers = otvet;
                break;
            }
        }

        for (int otvet = 0; otvet < que[nomer].count_answers; otvet++)
        {
            //900 - ширина экрана
            int shirina_otveta = 900 / que[nomer].count_answers;

            que[nomer].ans[otvet].x1 = 10 + otvet * shirina_otveta;
            que[nomer].ans[otvet].x2 = que[nomer].ans[otvet].x1 + shirina_otveta - 20;

            que[nomer].ans[otvet].y1 = 300;
            que[nomer].ans[otvet].y2 = 400;
        }
    }

    //Рисуем вопросы
    int nomer_voprosa = 0;
    while (nomer_voprosa < count_questions)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();
        drawQuestion(que[nomer_voprosa]);

        sprintf(stroka_dlya_kolichestvo_pravilnyh,
            "Количество правильных ответов %d из %d",
            kolichestvo_pravilnyh,
            nomer_voprosa);
        txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

        for (int nomer = 0; nomer < que[nomer_voprosa].count_answers; nomer++)
        {
            if (
                txMouseX() >= que[nomer_voprosa].ans[nomer].x1 and
                txMouseX() <= que[nomer_voprosa].ans[nomer].x2 and
                txMouseY() >= que[nomer_voprosa].ans[nomer].y1 and
                txMouseY() <= que[nomer_voprosa].ans[nomer].y2
            )
            {
                txSetFillColor(TX_YELLOW);
                txFloodFill(que[nomer_voprosa].ans[nomer].x1 + 10,
                            que[nomer_voprosa].ans[nomer].y1 + 10);
                txSleep(10);

                if (txMouseButtons() & 1)
                {
                    if (que[nomer_voprosa].ans[nomer].pravilnyi)
                    {
                        kolichestvo_pravilnyh = kolichestvo_pravilnyh + 1;
                    }
                    nomer_voprosa = nomer_voprosa + 1;
                    txSleep(1000);
                }
            }
        }

        txSleep(3);
        txEnd();
    }

    //Результат
    {
    txSetFillColor(TX_BLACK);
    txClear();
    sprintf(stroka_dlya_kolichestvo_pravilnyh,
        "Количество правильных ответов %d из %d",
        kolichestvo_pravilnyh,
        nomer_voprosa);
    txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

    if ((100 * kolichestvo_pravilnyh) / nomer_voprosa > 80)
    {
        txTextOut(30, 400, "Вы гений");
    }
    else
    {
        txTextOut(30, 400, "Вы идиот");
    }
    }

    return 0;
}

#include "main.h"
#include "functions.h"
#include "timer.h"
#include "menu.h"

Menu::Menu(void)
{
    this->state = 0;
    this->option[0] = "Signle Player";
    this->option[1] = "Multi Player";
    this->option[2] = "Options";
    this->option[3] = "Exit";

    font = new FTPixmapFont("data/SDS_6x6.ttf");
    infoFont = new FTPixmapfont("data/SDS_6x6.ttf");
    infoFont->FaceSize(18);
}

Menu::~Menu(void)
{
    delete font;
    delete infoFont;
}

void render(void)
{
    FTBBox bbox = font->BBox("TEST");
    float x1 = bbox.Lower().Xf();
    float x2 = bbox.Upper().Xf();
    float y1 = bbox.Lower().Yf();
    float y2 = bbox.Upper().Yf();

    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
    glEnd();
}

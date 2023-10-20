#ifndef __LCD_H__
#define __LCD_H__


class lcd
{
private:
    int fd;//文件描述符
    int * plcd;//映射首地址
    int width;//屏幕宽度
    int height;//屏幕高度
    int pixel_bit;//一个像素点占多少bit

    lcd(const char * pathname = "/dev/fb0");

public:
    lcd(const lcd &other) = delete;

    ~lcd();

    void display_point(int x0,int y0,int color);

    //......

    static lcd l;
};

#endif


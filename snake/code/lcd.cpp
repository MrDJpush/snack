#include<stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <iostream>
#include "lcd.h"
using namespace std;
lcd lcd::l{"/dev/fb0"};

lcd::lcd(const char * pathname)
{
    cout << "lcd 构造函数" <<endl;
    //打开文件
    fd = open(pathname,O_RDWR);
    if(fd == -1)
    {
        perror("open lcd error");
        return ;
    }
    //获取屏幕信息
    struct fb_var_screeninfo var;
    ioctl(fd,FBIOGET_VSCREENINFO,&var);// 失败返回-1，同时errno被设置

    //如果成功了，那么屏幕的参数信息就保存在 var中了
    width = var.xres;//这个是赋值，不是初始化
    height = var.yres;
    pixel_bit = var.bits_per_pixel;

    //映射
    plcd = (int *)mmap(NULL,height*width*pixel_bit/8,PROT_READ | PROT_WRITE,
            MAP_SHARED,fd,0);
    if(plcd == NULL)
    {
        perror("mmap error");
    }

}

lcd::~lcd()
{
    cout << "lcd 析构函数" <<endl;
    munmap(plcd,height*width*pixel_bit/8);
    close(fd);
}

void lcd::display_point(int x0,int y0,int color)
{
    if(x0>=0 && x0<width && y0>=0 && y0<height)
        *(plcd+width*y0+x0) = color;
}

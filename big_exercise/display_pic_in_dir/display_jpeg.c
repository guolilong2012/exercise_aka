/* disp-jpeg.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#define BLIND_Y_NUM 5
#define BLIND_X_NUM 6

#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////
/* display jpeg */
int display_jpeg(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for (yres = 0; yres < fb_inf.h; yres++)
    {
        for (xres = 0; xres < fb_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg blind y */
int display_jpeg_blind_y(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(yloop = 0; yloop < fb_inf.h / BLIND_Y_NUM; yloop++)
    {
        for (yres = yloop; yres < fb_inf.h; yres += fb_inf.h / BLIND_Y_NUM)
        {
            for(xres = 0; xres < fb_inf.w; xres++)
            {
                if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                 {
                    fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
                 }
            }            
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg blind x */
int display_jpeg_blind_x(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xloop = 0; xloop < fb_inf.w / BLIND_X_NUM; xloop++)
    {
        for (xres = xloop; xres < fb_inf.w; xres += fb_inf.w / BLIND_X_NUM)
        {
            for (yres = 0; yres < fb_inf.h; yres++)
            {
                if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                 {
                    fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
                 } 
            }            
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg cross */
int display_jpeg_cross(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xres_temp;
    int yres_temp;
    int t_sum = 0;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xres = 0; xres < fb_inf.w; xres++)
    {
        for(yres = 0; yres < fb_inf.h; yres++)
        {
            if ((yres / (fb_inf.h /5)) % 2 == 0)
            {
                fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
            }
            else
            {
                xres_temp = fb_inf.w - 1 - xres;
                yres_temp = yres;
                fb_pixel(fb_inf, xres_temp, yres_temp, buf32[xres_temp + (yres_temp * fb_inf.w)]);
            }
        }  

        t_sum++;
        if (t_sum % 3 == 0)
        {
            usleep(1);
        }          
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg door */
int display_jpeg_door(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xloop = 0; xloop < fb_inf.w / 2; xloop++)
    {
        for(yres = 0; yres < fb_inf.h; yres++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 - xloop, yres, buf32[fb_inf.w / 2 - xloop + (yres * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + xloop, yres, buf32[fb_inf.w / 2 + xloop + (yres * fb_inf.w)]);
        }  
        usleep(1);          
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg circle */
int display_jpeg_circle(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int x_loop;
    int y_loop;
    int r_len;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < sqrt(fb_inf.w * fb_inf.w + fb_inf.h * fb_inf.h) / 2 + 1; r_len++)
    {
        for (x_loop = 0; x_loop <= r_len; x_loop++)
        {
            for (y_loop = 0; y_loop <= r_len; y_loop++)
            {
                if (((x_loop * x_loop + y_loop * y_loop) <= r_len * r_len)
                   && ((x_loop * x_loop + y_loop * y_loop) >= (r_len - 1) * (r_len - 1)))
                 { 
                    xres = fb_inf.w / 2 + x_loop;
                    yres = fb_inf.h / 2 + y_loop;
                    if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                      {
                        fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                      }

                    xres = fb_inf.w / 2 + x_loop;
                    yres = fb_inf.h / 2 - y_loop;
                    if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                      {
                        fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                      }

                    xres = fb_inf.w / 2 - x_loop;
                    yres = fb_inf.h / 2 + y_loop;
                    if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                      {
                        fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                      }

                    xres = fb_inf.w / 2 - x_loop;
                    yres = fb_inf.h / 2 - y_loop;
                    if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                      {
                        fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                      }
                }
            }            
        }
       usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg diagonal close */
int display_jpeg_diagonal_c(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int xloop;
    int xres1;
    int xres2;
    int yres1;
    int yres2;
    float h_div_w = (float)fb_inf.h / fb_inf.w;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
//    for (xloop = fb_inf.w - 1; xloop >= 0; xloop--)
    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres < xloop; xres++)
        {
            xres1 = xres;
            yres1 = h_div_w * (xloop - xres1);
            xres2 = fb_inf.w - 1 - xres1;
            yres2 = fb_inf.h - 1 - yres1;
            fb_pixel(fb_inf, xres1, yres1, buf32[xres1 + (yres1 * fb_inf.w)]);
            fb_pixel(fb_inf, xres2, yres2, buf32[xres2 + (yres2 * fb_inf.w)]);          
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg circle area */
int display_jpeg_circle_area(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int r_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < fb_inf.w / 2; r_len++)
    {
        for (x_loop = 0; x_loop < fb_inf.w / 2; x_loop++)
        {
            for (y_loop = 0; y_loop < fb_inf.h / 2; y_loop++)
            {
                if ((x_loop * y_loop <= (float)(fb_inf.h) / fb_inf.w * r_len * r_len)
                   && (x_loop * y_loop >= ((float)(fb_inf.h) / fb_inf.w * r_len - 1)* (r_len - 1)))
                { 
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                }
            }            
        }
       usleep(100);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg point */
int display_jpeg_point(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int iloop;
    int jloop;
    int x_flag = 4;
    int y_flag = 4;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for (iloop = 0; iloop < x_flag; iloop++)
    {
        for (jloop = y_flag - 1; jloop >= 0; jloop--)
        {
            for (xres = 0; xres < fb_inf.h; ++xres)
             {
                for (yres = 0; yres < fb_inf.w; ++yres)
                  {
                    if (((xres % x_flag) == iloop) && ((yres % y_flag) == jloop))
                        {
                        fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
                        }
                   }
             }
            usleep(200000);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg square */
int display_jpeg_square(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int x_len;
    int y_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
//    for (x_len = 0; x_len < fb_inf.w / 2 ; x_len++)
    for (x_len = fb_inf.w / 2 - 1; x_len >= 0; x_len--)
    {
        y_len = (float)fb_inf.h / fb_inf.w *x_len;
        for (x_loop = 0; x_loop <= x_len; x_loop++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_len, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_len, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_len, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_len, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_len) * fb_inf.w)]);
        }
        for (y_loop = 0; y_loop <= y_len; y_loop++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 + x_len, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_len + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + x_len, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_len + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_len, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_len + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_len, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_len + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
        }
        usleep(100);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

/* display jpeg some circle */
int display_jpeg_circle_num(const char *jpegname, fb_info fb_inf, int x_num, int y_num)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xres_center;
    int yres_center;
    int x_loop;
    int y_loop;
    int r_len;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len <= sqrt((fb_inf.w / x_num) * (fb_inf.w / x_num) + (fb_inf.h / y_num) * (fb_inf.h / y_num)) / 2 + 10; r_len++)
    {
        for (x_loop = 0; x_loop <= r_len; x_loop++)
        {
            for (y_loop = 0; y_loop <= r_len; y_loop++)
            {
                if (((x_loop * x_loop + y_loop * y_loop) <= r_len * r_len)
                   && ((x_loop * x_loop + y_loop * y_loop) >= (r_len - 1) * (r_len - 1)))
                { 
                    for (xres_center = fb_inf.w / (x_num * 2); xres_center < fb_inf.w; xres_center += fb_inf.w / x_num )
                      {
                        for (yres_center = fb_inf.h / (y_num * 2); yres_center < fb_inf.h; yres_center += fb_inf.h / y_num ) 
                           {       
                            xres = xres_center + x_loop;
                            yres = yres_center + y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center + x_loop;
                            yres = yres_center - y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center - x_loop;
                            yres = yres_center + y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center - x_loop;
                            yres = yres_center - y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }
                         } 
                    }
                }
            }            
        }
       usleep(500 * x_num * y_num);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

#if 1
/* display jpeg diagonal open */
int display_jpeg_diagonal_o(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int xloop;
    int xres1;
    int xres2;
    int yres1;
    int yres2;
    float h_div_w = (float)fb_inf.h / fb_inf.w;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for (xloop = fb_inf.w - 1; xloop >= 0; xloop--)
//    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres < xloop; xres++)
        {
            xres1 = xres;
            yres1 = h_div_w * (xloop - xres1);
            xres2 = fb_inf.w - 1 - xres1;
            yres2 = fb_inf.h - 1 - yres1;
            fb_pixel(fb_inf, xres1, yres1, buf32[xres1 + (yres1 * fb_inf.w)]);
            fb_pixel(fb_inf, xres2, yres2, buf32[xres2 + (yres2 * fb_inf.w)]);          
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg inset */
int display_jpeg_inset(const char *jpeg_big, const char *jpeg_small, int x, int y, float value, fb_info small_inf, fb_info fb_inf)
{
    fb_info jpeg_inf1;
    fb_info jpeg_inf2;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24_big = decode_jpeg(jpeg_big, &jpeg_inf1);
    u8_t *scale_buf_big = scale24(buf24_big, fb_inf, jpeg_inf1);
    u32_t *buf32_big = rgb24to32(scale_buf_big, fb_inf);
    
    u8_t *buf24_small = decode_jpeg(jpeg_small, &jpeg_inf2);
    u8_t *scale_buf_small = scale24(buf24_small, small_inf, jpeg_inf2);
    u32_t *buf32_small = rgb24to32(scale_buf_small, small_inf);
    
    for (yloop = 0; yloop < small_inf.h; yloop++)
    {
        for (xloop = 0; xloop < small_inf.w; xloop++)
        {

            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 2) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 2)) * (1 - value) 
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * small_inf.w)] + 2)) * value;
            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 1) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 1)) * (1 - value)
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * small_inf.w)] + 1)) * value;
            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 0) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 0)) * (1 - value) 
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * small_inf.w)] + 0)) * value;

        }
    }

    for (yres = 0; yres < fb_inf.h; yres++)
    {
        for (xres = 0; xres < fb_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, buf32_big[xres + (yres * fb_inf.w)]);
        }
    }
    
    free(buf24_small);
    free(scale_buf_small);
    free(buf32_small);

    free(buf24_big);
    free(scale_buf_big);
    free(buf32_big);
    
    return 0;
}
#endif

#if 0
/* display jpeg down */
int display_jpeg_down(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (yloop = 0; yloop < fb_inf.h; yloop += 3)
    {
        for (yres = 0; yres <= yloop; yres++)
        {
            for (xres = 0; xres < fb_inf.w / 2; xres += 2)
             {
                fb_pixel(fb_inf, xres, yres, buf32[xres + ((fb_inf.h - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, xres + 1, yres, buf32[xres + 1 + ((fb_inf.h - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, fb_inf.w - 1 - xres, yres, buf32[fb_inf.w - 1 - xres + ((fb_inf.h - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, fb_inf.w - 1 - xres - 1, yres, buf32[fb_inf.w - 1 - xres - 1 + ((fb_inf.h - yloop + yres) * fb_inf.w)]);
             }
        }
//        usleep(1);
    }
    display_jpeg(jpegname, fb_inf);
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 0
/* display jpeg down */
int display_jpeg_down(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (yloop = 0; yloop < fb_inf.h / 2; yloop++)
    {
        for (yres = 0; yres < yloop; yres++)
        {
            for (xres = 0; xres < fb_inf.w; xres++)
            {
                fb_pixel(fb_inf, xres, yres + 1, buf32[xres + ((fb_inf.h / 2 - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, xres, fb_inf.h - 1 - yloop + yres, buf32[xres + ((fb_inf.h / 2 + yres) * fb_inf.w)]);
            }
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

/* display jpeg down */
int display_jpeg_down(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (yloop = 0; yloop < fb_inf.h / 2; yloop += 2)
    {
        for (yres = 0; yres < yloop; yres++)
        {
            for (xres = 0; xres < fb_inf.w / 2; xres++)
            {
                fb_pixel(fb_inf, xres, yres + 2, buf32[xres + ((fb_inf.h / 2 - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, fb_inf.w / 2 + xres, yres + 2, buf32[fb_inf.w / 2 + xres + ((fb_inf.h / 2 - yloop + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, xres, fb_inf.h - 2 - yloop + yres, buf32[xres + ((fb_inf.h / 2 + yres) * fb_inf.w)]);
                fb_pixel(fb_inf, fb_inf.w / 2 + xres, fb_inf.h - 2 - yloop + yres, buf32[fb_inf.w / 2 + xres + ((fb_inf.h / 2 + yres) * fb_inf.w)]);
            }
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

#if 0
/* display jpeg right */
int display_jpeg_right(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres <= xloop; xres++)
        {
            for (yres = 0; yres < fb_inf.h; yres++)
            {
                fb_pixel(fb_inf, xres, yres, buf32[fb_inf.w - 1 - xloop + xres + yres * fb_inf.w]);
//                fb_pixel(fb_inf, xres, fb_inf.h - 1 - yloop + yres, buf32[xres + ((fb_inf.h / 2 + yres) * fb_inf.w)]);
            }
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg mosaic*/
int display_jpeg_mosaic(const const char *jpegname, fb_info fb_inf, int size)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (; size > 0; size--) 
    {   
        for (yres = 0; yres < fb_inf.h; yres++)
        {
            for (xres = 0; xres < fb_inf.w; xres++)
            {
                fb_pixel(fb_inf, xres, yres, buf32[(xres / size) * size + ((yres / size) * size * fb_inf.w)]);
            }
        }
        usleep(10000);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

#else

/* display jpeg mosaic*/
int display_jpeg_mosaic(const const char *jpegname, fb_info fb_inf, int size)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    u32_t *buf_mosaic_r = (u32_t *)malloc((fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);
    u32_t *buf_mosaic_g = (u32_t *)malloc((fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);
    u32_t *buf_mosaic_b = (u32_t *)malloc((fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);

    memset(buf_mosaic_r, 0, (fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);
    memset(buf_mosaic_g, 0, (fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);
    memset(buf_mosaic_b, 0, (fb_inf.w / size + 1) * (fb_inf.h / size + 1) * 4);

    for (yloop = 0; yloop < fb_inf.h; yloop++)
    {
        for (xloop = 0; xloop < fb_inf.w; xloop++)
        {

            buf_mosaic_r[xloop / size + (yloop / size) * (fb_inf.w / size + 1)] += (u32_t)*((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 2);
            buf_mosaic_g[xloop / size + (yloop / size) * (fb_inf.w / size + 1)] += (u32_t)*((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 1);
            buf_mosaic_b[xloop / size + (yloop / size) * (fb_inf.w / size + 1)] += (u32_t)*((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 0);
        }
    }

    for (xloop = 0; xloop < (fb_inf.h / size + 1) * (fb_inf.h / size + 1); xloop++)
    {
        buf_mosaic_r[xloop] /= size * size;
        buf_mosaic_g[xloop] /= size * size;
        buf_mosaic_b[xloop] /= size * size;
    }

    for (yloop = 0; yloop < fb_inf.h; yloop++)
    {
        for (xloop = 0; xloop < fb_inf.w; xloop++)
        {

            *((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 2) = (u8_t)buf_mosaic_r[xloop / size + (yloop / size) * (fb_inf.w / size + 1)];
            *((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 1) = (u8_t)buf_mosaic_g[xloop / size + (yloop / size) * (fb_inf.w / size + 1)];
            *((u8_t *)&buf32[xloop + yloop * fb_inf.w] + 0) = (u8_t)buf_mosaic_b[xloop / size + (yloop / size) * (fb_inf.w / size + 1)];
        }
    }

    for (yres = 0; yres < fb_inf.h; yres++)
    {
        for (xres = 0; xres < fb_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
    }

    free(buf_mosaic_r);
    free(buf_mosaic_g);
    free(buf_mosaic_b);
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#endif    /* FRAME_SUPPORT_JPEG */

/*   point.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:45:34
*/
#ifndef POINT_H
#define POINT_H

typedef struct{
    char *id;
    float x,y;
}point;

point pointCreate(char *id, float x, float y);
float distance(point a, point b);
#endif

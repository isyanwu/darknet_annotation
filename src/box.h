#ifndef BOX_H
#define BOX_H
#include "darknet.h"

typedef struct{
    float dx, dy, dw, dh;
} dbox;

float box_rmse(box a, box b);
dbox diou(box a, box b);
box decode_box(box b, box anchor); 

/*box的定义在/include/darknet.h中，定义如下：
typedef struct{
    float x,y,w,h;
} box;
*/

box encode_box(box b, box anchor);

#endif

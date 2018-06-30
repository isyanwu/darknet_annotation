#ifndef ACTIVATIONS_H  //不是很懂这是要干什么？？有什么好处吗？？
#define ACTIVATIONS_H
#include "darknet.h"
#include "cuda.h"
#include "math.h"

ACTIVATION get_activation(char *s);//ACTIVATION是激活函数的枚举类型，包括relu、sigmoid等，具体详见include/darnnet.h

char *get_activation_string(ACTIVATION a);  //该函数返回激活函数名的字符串形式，例如："relu"、"sigmoid"等
//作者这样写，是为了激活函数的枚举类型和字符串类型的互相转换

float activate(float x, ACTIVATION a);//返回激活函数运算之后的值，x是输入
float gradient(float x, ACTIVATION a);//顾名思义，返回在点x处的梯度值
void gradient_array(const float *x, const int n, const ACTIVATION a, float *delta);/*上述gradient函数的数组形式，x是输入，delta是输出，
即梯度值。为了减少不必要的bug，专门写了const*/
void activate_array(float *x, const int n, const ACTIVATION a);/*上述activate函数的数组形式，n是数组长度，x是待激活值，
作者把激活值重新赋给了x 。这样写是为了节省空间，在前向传播时，计算完激活值之后，输入值没必要保存了*/

//上述函数代码都在src/activations.c中，代码非常简单，就不在activations.c中添加注释了

#ifdef GPU//目前还不懂cuda，日后再回顾。还没搞清楚这部分代码在哪里？
void activate_array_gpu(float *x, int n, ACTIVATION a);
void gradient_array_gpu(float *x, int n, ACTIVATION a, float *delta);
#endif


//下面都是各种激活函数的具体实现过程,过于简单，略
static inline float stair_activate(float x)
{
    int n = floor(x);
    if (n%2 == 0) return floor(x/2.);
    else return (x - n) + floor(x/2.);
}
static inline float hardtan_activate(float x)
{
    if (x < -1) return -1;
    if (x > 1) return 1;
    return x;
}
static inline float linear_activate(float x){return x;}
static inline float logistic_activate(float x){return 1./(1. + exp(-x));}
static inline float loggy_activate(float x){return 2./(1. + exp(-x)) - 1;}
static inline float relu_activate(float x){return x*(x>0);}
static inline float elu_activate(float x){return (x >= 0)*x + (x < 0)*(exp(x)-1);}
static inline float relie_activate(float x){return (x>0) ? x : .01*x;}
static inline float ramp_activate(float x){return x*(x>0)+.1*x;}
static inline float leaky_activate(float x){return (x>0) ? x : .1*x;}
static inline float tanh_activate(float x){return (exp(2*x)-1)/(exp(2*x)+1);}
static inline float plse_activate(float x)
{
    if(x < -4) return .01 * (x + 4);
    if(x > 4)  return .01 * (x - 4) + 1;
    return .125*x + .5;
}

static inline float lhtan_activate(float x)
{
    if(x < 0) return .001*x;
    if(x > 1) return .001*(x-1) + 1;
    return x;
}
static inline float lhtan_gradient(float x)
{
    if(x > 0 && x < 1) return 1;
    return .001;
}

static inline float hardtan_gradient(float x)
{
    if (x > -1 && x < 1) return 1;
    return 0;
}
static inline float linear_gradient(float x){return 1;}
static inline float logistic_gradient(float x){return (1-x)*x;}
static inline float loggy_gradient(float x)
{
    float y = (x+1.)/2.;
    return 2*(1-y)*y;
}
static inline float stair_gradient(float x)
{
    if (floor(x) == x) return 0;
    return 1;
}
static inline float relu_gradient(float x){return (x>0);}
static inline float elu_gradient(float x){return (x >= 0) + (x < 0)*(x + 1);}
static inline float relie_gradient(float x){return (x>0) ? 1 : .01;}
static inline float ramp_gradient(float x){return (x>0)+.1;}
static inline float leaky_gradient(float x){return (x>0) ? 1 : .1;}
static inline float tanh_gradient(float x){return 1-x*x;}
static inline float plse_gradient(float x){return (x < 0 || x > 1) ? .01 : .125;}

#endif


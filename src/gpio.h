#ifndef GPIO_H_
#define GPIO_H_

// gpio macros
// Note: Always use INP_GPIO(g, p) before using OUT_GPIO(g, p) or SET_GPIO_ALT(g, p, a)
#define INP_GPIO(g,p) *(g+((p)/10)) &= ~(7<<(((p)%10)*3))
#define OUT_GPIO(g,p) *(g+((p)/10)) |=  (1<<(((p)%10)*3))
#define SET_GPIO_ALT(g,p,a) *(g+(((p)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((p)%10)*3))

#define GPIO_SET(g,p) *(g+7) = (1<<p)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR(g,p) *(g+10) = (1<<p) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g,p) ((*(g+13)&(1<<p))>>p) // 0 if LOW, 1 if HIGH

#define GPIO_PULL(g,p) *(g+37) = (1<<p)     // Pull up/pull down
#define GPIO_PULLCLK0(g,p) *(g+38) = (1<<p) // Pull up/pull down clock

#define EDGE_RISING 1
#define EDGE_FALLING 2

#define RPI_V1 1
#define RPI_V2 2

typedef volatile unsigned int* gpio_t;

gpio_t gpio_setup(int version);

#endif // GPIO_H_


#ifndef DELAY_H_
#define DELAY_H_

#define   F_CPU 16000000UL

#define delay_s(s)		(__delay_cycles((s  * F_CPU));
#define delay_ms(ms)	(__delay_cycles((ms * F_CPU) / 1000UL));
#define delay_us(us)	(__delay_cycles((us * F_CPU) / 1000000UL));

#endif

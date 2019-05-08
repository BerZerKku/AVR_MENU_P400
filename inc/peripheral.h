/** Работа с периферией МК.
 *
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

extern void PERIF_intrEnable(void);

extern void PERIF_setup(void);

extern void PERIF_timer0Start(void);
extern void PERIF_timer1Start(void);
extern void PERIF_timer2Start(void);

extern void PERIF_wdReset(void);
extern void PERIF_wdStart(void);

#endif


#ifndef QEI_H
#define	QEI_H

#define DISTROUES 0.281
#define FREQ_ECH_QEI 250
#define COEFF_SPEED_TO_PERCENT 40
#define POSITION_DATA 0x0061

void InitQEI1();
void InitQEI2();
void QEIUpdateData();
void SendPositionData();

#endif	/* QEI_H */


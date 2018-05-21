
#include "../../iodefine.h"
#include "debug.h"

void initializeADConverter()
{
	SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;	//AD0ユニットモジュールスタンバイ解除(AD1はMSTPA22)

	PORT4.DDR.BIT.B0 = 0;
	PORT4.ICR.BIT.B0 = 1;

	AD0.ADCSR.BIT.ADST = 0; // AD変換停止
	AD0.ADCR.BIT.MODE = 2;	//連続スキャンモード（0だとシングルモード）

	// select AN0
	AD0.ADCSR.BIT.CH = 1;

	// AD clock is 6MHz
	AD0.ADCR.BIT.CKS = 0;		//クロック選択

	AD0.ADDPR.BIT.DPSEL = 0;	//LSB詰め

	AD0.ADCSR.BIT.ADST = 1; // AD変換開始
}

int getADConvertValue(char number)
{
	return AD0.ADDRA;
}

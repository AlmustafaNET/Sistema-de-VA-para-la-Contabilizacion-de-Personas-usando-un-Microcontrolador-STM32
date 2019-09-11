#include "SCCB.h"
#include "dwt_delay.h"
//#define DWT_Delay(x) HAL_Delay(1)
#include "main.h"

void SCCB_GPIO_Config(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Pin = CAM_SIOC_Pin | CAM_SIOD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void SCCB_SID_GPIO_OUTPUT(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = CAM_SIOD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SCCB_SID_GPIO_INPUT(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = CAM_SIOD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void startSCCB(void) {
	SCCB_SID_H();
	DWT_Delay(500);

	SCCB_SIC_H();
	DWT_Delay(500);

	SCCB_SID_L();
	DWT_Delay(500);

	SCCB_SIC_L();
	DWT_Delay(500);
}
void stopSCCB(void) {
	SCCB_SID_L();
	DWT_Delay(500);

	SCCB_SIC_H();
	DWT_Delay(500);

	SCCB_SID_H();
	DWT_Delay(500);
}

void noAck(void) {
	SCCB_SID_H();
	DWT_Delay(500);

	SCCB_SIC_H();
	DWT_Delay(500);

	SCCB_SIC_L();
	DWT_Delay(500);

	SCCB_SID_L();
	DWT_Delay(500);
}

unsigned char SCCBwriteByte(unsigned char m_data) {
	unsigned char j, tem;

	for (j = 0; j < 8; j++) {
		if ((m_data << j) & 0x80) {
			SCCB_SID_H();
		} else {
			SCCB_SID_L();
		}
		DWT_Delay(10);
		SCCB_SIC_H();
		DWT_Delay(10);
		SCCB_SIC_L();
		DWT_Delay(10);
	}
	DWT_Delay(10);
	SCCB_SID_IN;
	DWT_Delay(10);
	SCCB_SIC_H();
	DWT_Delay(10);
	if (SCCB_SID_STATE) {
		tem = 0;
	} else {
		tem = 1;
	}
	SCCB_SIC_L();
	DWT_Delay(10);
	SCCB_SID_OUT;

	return (tem);
}

unsigned char SCCBreadByte(void) {
	unsigned char read, j;
	read = 0x00;

	SCCB_SID_IN;
	DWT_Delay(100);
	for (j = 8; j > 0; j--) {
		DWT_Delay(10);
		SCCB_SIC_H();
		DWT_Delay(10);
		read = read << 1;
		if (SCCB_SID_STATE) {
			read = read + 1;
		}
		SCCB_SIC_L();
		DWT_Delay(10);
	}
	return (read);
}

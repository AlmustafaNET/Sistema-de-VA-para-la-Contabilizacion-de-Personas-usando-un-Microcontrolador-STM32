#ifndef _SCCB_H
#define _SCCB_H

#define SCCB_SIC_BIT     CAM_SIOC_Pin
#define SCCB_SID_BIT     CAM_SIOD_Pin

#define SCCB_SIC_H()     HAL_GPIO_WritePin(CAM_SIOC_GPIO_Port, CAM_SIOC_Pin, GPIO_PIN_SET)
#define SCCB_SIC_L()     HAL_GPIO_WritePin(CAM_SIOC_GPIO_Port, CAM_SIOC_Pin, GPIO_PIN_RESET)

#define SCCB_SID_H()     HAL_GPIO_WritePin(CAM_SIOD_GPIO_Port, CAM_SIOD_Pin, GPIO_PIN_SET)
#define SCCB_SID_L()     HAL_GPIO_WritePin(CAM_SIOD_GPIO_Port, CAM_SIOD_Pin, GPIO_PIN_RESET)
/**/
#define SCCB_SID_IN      SCCB_SID_GPIO_INPUT()
#define SCCB_SID_OUT     SCCB_SID_GPIO_OUTPUT()


#define SCCB_SID_STATE	 (HAL_GPIO_ReadPin(CAM_SIOD_GPIO_Port, CAM_SIOD_Pin) == GPIO_PIN_SET)

///////////////////////////////////////////	 
void SCCB_GPIO_Config(void);
void SCCB_SID_GPIO_OUTPUT(void);
void SCCB_SID_GPIO_INPUT(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);


#endif /* _SCCB_H */



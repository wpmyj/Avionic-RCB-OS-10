#ifndef _CFG_H_
#define _CFG_H_

#include "stm32f10x.h"

#define PARAM_TXSYS_ADDRESS 		0x0801A800 	//(0x08000000 + (STM32_FLASH_SIZE-22)*1024)
#define PARAM_MODEL_BASE_ADDRESS	0x0801A850	

//语言
#define CHINESE			0
#define ENGLISH			1

//开机检测时的安全油门
#define	THRSAFE			-485

#define MODELIDL	6	//ID字符长度

typedef struct{
	u8  StkCalied;		//摇杆是否校准
	u32	RfId;//ID
	char RfIdStr[MODELIDL+1];//ID字符
	s16 ModelNo;		//模型号
	s16	TrimStep;	    //微调步长
	s16 StkType;		//手型
	s16 StkCali[4][3];  //摇杆校准值
	s16 StkDa;			//摇杆死区
	s16	Vibrator;		//震动马达开关
	s16	Music;			//音乐开关
	s16 KeyBeep;		//按键音开关
	s16 KeyTone;		//按键音调
	s16 Light;			//LCD背光
	s16 Contrast;		//LCD对比度
	s16 LightOff;		//LCD背光时间
	s16 BatType;		//电池类型
	s16 BatWarn;		//电压报警值
	s16 Language;		//语言
	u16	BatTime;		//电池使用时间
	u16	BatVoltRec;		//电池电压记录
	u32	crc;			//CRC校验值
}TXSYS;

extern const TXSYS TxSysDef;
extern TXSYS TxSys;

/*********************************************************************/
//模型关参数
#define MODELNL		9	//模型名的长度
#define MODCFG_NUM	30	//最多支持的模型数

//模型类型
typedef enum{
	MT_AERO,
	MT_HELI,
	MT_WING,
	MT_VTAIL,
	MT_NUM
}MODELTYPE;
/*********************************/

/*********************************************************************/
//电池电压参数
#define VOLTAGE_NUMERATOR 	210			//Compute voltage from y = 2.1592x + 0.2493
#define VOLTAGE_OFFSET    	249
/*********************************/

/*********************************************************************/
//定时器相关参数
//定时器类型
#define TMR_INH		0	//禁止
#define TMR_CLK		1	//正时器
#define TMR_DCK		2	//倒计时

//定时器控制开关
#define TMRSW_THR	0	
#define TMRSW_SA	1
#define TMRSW_SB	2
#define TMRSW_SC	3
#define TMRSW_SD	4

typedef struct{
	s16 Type;
	s16	Sw;
	s16 Thr;
	s16 Time;
}TIMER;

typedef struct{
	s32	Cnt;
	u8	Run;
	u8	Alert;
	u8  Reset;
	TIMER *Cfg;
}TIMERRUN;

extern TIMERRUN TxTimer;	//定时计数器
/*********************************/

/*********************************************************************/
//混控相关参数
#define	MAX_EPA				120
#define EPA_SIZE			100			//EPA满幅
#define	NEU_STEP			2			//中立点步长
#define	MAX_DLT				100			//三角翼混控行程
#define	MAX_VTL				100			//V尾混控行程
#define	MAX_FAM				100			//襟翼副翼混控行程
#define	MAX_THM				100			//油门混控行程
#define	MAX_YWM				100			//转向混控行程
#define MAX_ARM				100			//副翼方向混控行程
#define	DELAY_MAX			99			//通道减速上限
#define	MAX_AUX				100			//AUX通道上限
#define	TRV_AUX				120			//AUX通道上限
#define	MAX_GYRO			100
#define	TRV_GYRO			120
#define CURVE_TRV			1000

typedef struct{
	s16	Enable;
	s16 A2A,E2A,A2E,E2E;
}DELTAMIX;

typedef struct{
	s16	Enable;
	s16 E2E,R2E,E2R,R2R;
}VTAILMIX;

typedef struct{
	s16	Enable;
	s16 A2A,A2F,F2A,F2F;
}FLAPAILMIX;

typedef struct{
	s16 Rl2E,Rr2E,Al2E,Ar2E;
}YAWMIX;

typedef struct{
	s16 Enable;
	s16 A2A,A2R,R2A,R2R;
}AILRUDMIX;
/*********************************/

/*********************************************************************/
//摇杆相关参数
#define STKMOVTST	6	//摇杆静止检测阈值,数值越大越迟钝

#define	STK_TRV		512	//摇杆行程
#define STK_AIL		0
#define STK_ELE		1
#define	STK_THR		2
#define STK_RUD		3
#define STK_NUM		4
extern u16 StickRaw[STK_NUM];
extern s16 StickCal[STK_NUM];
extern s16 StickValue[STK_NUM];
/*********************************/

/*********************************************************************/
#define ICONNL		8	//图标名称的最大长度
#define ICON_NUM	20	//最多支持的图标�
/*********************************/

/*********************************************************************/
//摇杆曲线相关参数
#define CURVE_NUM	9	//摇杆曲线的点数	
#define CURVE_DS	(CURVE_NUM+3)//数据存储空间大小（曲线上9个点的数据以及额外的3个参数）
/*********************************/

/*********************************************************************/
//开关定义(SwDef)
#define SWD_HOLD	0
#define SWD_IDLE	1
#define SWD_DR		2
#define SWD_GEAR	3
#define SWD_FLAP	4
#define SWD_AUX1	5
#define SWD_AUX2	6
#define SWD_TRAINER	7
/*********************************/

typedef struct{
	char 	Name[MODELNL+1];
	char 	Icon[ICONNL+1];
	s16		Type;
	s8		Trim[4];
	s16		Protocol;
	s16		RfPwr;
	s16		ChMap[10];				//通道映射
	s16		TrChMap[10];			//教练功能通道映射
	TIMER	Timer;
	s16		Rev[10];
	s16		Epa[10][2];
	s16		Neu[10];
	s16		ThrHold;
	DELTAMIX Delta;
	VTAILMIX Vtail;
	FLAPAILMIX	FlpAil;
	YAWMIX		YawMix;
	s16			ThrMix[3];
	AILRUDMIX	AilRud;
	s16		StkCurve[3][3][CURVE_DS];
	s16		ThrCurve[3][CURVE_DS];
	s16		PitCurve[4][CURVE_DS];
	s16		Gyro[4];
	s16		SwashType;
	s16		Swash[3];
	s16		Gear[3];
	s16		Flap[3];
	s16		Aux[6][3];
	s16		Delay[10];
	s16		SwDef[8];
	s16		PpmIn;
	u8 		StillSeed;
	s16		RxBatType;
	s16		RxBatWarn;
	s16		VirtualSwStk[2];
	s16		VirtualSwVal[2];
	u32		crc;//CRC校验值
}MODEL;

extern MODEL Model;
extern const MODEL ModelDef;

void LoadCfg(void);
void SaveCfg(void);

int32_t MODEL_checkValid(const MODEL *param);
void ModelLoad(u16 id,u8 txopen);
void ModelSave(u16 id);
void ModelCopy(u8 from,u8 to);
void ModelFormat(void);

#endif


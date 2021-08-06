#pragma once
#ifndef __TCPClient_H_INCLUDED__   
#define __TCPClient_H_INCLUDED__
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <direct.h> 
#include <Windows.h>
#include<iomanip>
#include<fstream>
#define TARGETNUM (3)
//#include"lib\CreatFold.h"
using namespace std;

//ָ����̬���lib�ļ�
#pragma comment(lib,"ws2_32.lib")
//#pragma comment(lib,"lib\CreatFold.lib")

//16
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	char Head[4];
	uint8_t RDType;
	uint8_t Cmd;
	uint32_t Length;
	uint16_t Version;
	uint16_t FrameID;
} FrameHeader;
typedef struct
{
	uint16_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Hour;
	uint8_t Min;
	uint8_t Sec;
	uint8_t Reserved;
}BJtime;
typedef struct
{
	uint8_t ExistStatus;
	float Range;
	float Velocity;
	float Azimuth;
	float Pitch;
	uint8_t SeatOccupidStaus;
	uint8_t TargetType;
	float BreathingPhase;
	float HeartPhase;
	float BreathingRate;
	float HeartRate;
	float Power;
	float SNR;
	uint8_t Reserved;
}ObjectTarget;
//��126�ֽ�
typedef struct
{
	uint8_t ModeType;//1
	BJtime BeiJingTime;//8
	uint32_t TimeStamp;//4
	uint16_t CycleDuration;//2
	uint8_t DetectStatus;//1
	uint16_t TarNum;//2
	ObjectTarget Target[TARGETNUM];//32
}FrameData;
typedef struct
{
	uint8_t ModeType;
	uint8_t StartAndStop;//0��ʾֹͣ����,1��ʾ�����״�
	uint32_t reserved;
}FrameCMDData;
typedef struct
{
	FrameHeader frameHead;
	FrameData frameData;
}RadarACMData;
typedef struct
{
	FrameHeader frameHead;
	FrameCMDData frameCmdData;
}FrameCMD;
#pragma pack(pop)
static SOCKET clientSocket;
static fstream *Outfile;
extern "C" __declspec(dllexport) int tcpConnect(char * ip, int port);//-1��ȡsocketʧ��,-2����socketʧ�ܣ�-3����ʧ�ܣ�1���ӳɹ�
extern "C" __declspec(dllexport) int tcpReceive(RadarACMData *radarData);
extern "C" __declspec(dllexport) void tcpSend(int flag);//flag = 0��ʾֹͣ�״flag = 1����ʾ�����״�
extern "C" __declspec(dllexport) void tcpClose();
void creatfile();
string getTime();
#endif

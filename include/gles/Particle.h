#pragma once

namespace nb{ namespace gl{

//粒子系统
class ParticleSystem
{
public:
};

//粒子
class Particle
{

};

//粒子发射器
class ParticleEmitter
{
public:
	int particleCount;		//最大粒子数
	int emiteRate;			//每次发射粒子个数
	int life;				//粒子生命周期
	float emiteSpeed;		//发射初始速度
};

//粒子运动效果
class ParticleAffector
{

};

}}
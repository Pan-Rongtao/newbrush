/**************************************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2017-03

 * 简要描述: 拓扑图中的通行令牌

 * 修改记录:

 **************************************************************************************************/

#pragma once

#include "../../core/Object.h"

namespace nb { namespace System { namespace Topology {

class NB_API Token : public nbObject
{
public:
	Token(void);
	virtual ~Token(void);
};

class KeyTokenBase : public Token
{
public:
	//virtual bool Is
};

template<class KeyT>
class KeyToken : public KeyTokenBase
{
public:
	KeyToken(const KeyT &key) : m_key(key) {}
	KeyToken() {}
	const KeyT & GetKey() const {return m_key;}
private:
	KeyT m_key;
};

}}}

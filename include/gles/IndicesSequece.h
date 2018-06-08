#pragma once

//顶点序列只能用byte和short，不能用int，未找到原因；网上说int可以的
namespace nb{ namespace gl{ namespace Gles{

class IndicesSequece
{
public:
	IndicesSequece(unsigned short *data, unsigned short size);
	~IndicesSequece();

	unsigned short *Data() const;
	unsigned short GetSize() const;
	
	unsigned short operator[] (int index);

public:
	IndicesSequece(const IndicesSequece &other);
	void operator = (const IndicesSequece &other);


private:
	unsigned short		*m_Head;
	unsigned short		m_Size;
};

}}}
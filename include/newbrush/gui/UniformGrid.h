#pragma once
#include "newbrush/gui/Panel.h"

namespace nb {
namespace gui{

class NB_API UniformGrid : public Panel
{
public:
	UniformGrid();

	static DependencyProperty	RowsProperty();			//��������������
	static DependencyProperty	ColumnsProperty();		//��������������
	static DependencyProperty	FirstColumnProperty();	//��һ�пհ������������ԣ�����ʽָ����Colums����Ч��������ڵ���ColumsҲ��Ч��

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
}
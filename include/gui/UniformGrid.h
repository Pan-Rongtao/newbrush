#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class NB_API UniformGrid : public Panel
{
public:
	UniformGrid();

	Property_rw<int>					Rows;					//行数
	Property_rw<int>					Columns;				//列数
	Property_rw<int>					FirstColumn;			//第一行中前导空白单元格数量，需显式指定了Colums才有效，如果大于等于Colums也无效

	static const DependencyProperty		RowsProperty();			//行数的依赖属性
	static const DependencyProperty		ColumnsProperty();		//列数的依赖属性
	static const DependencyProperty		FirstColumnProperty();	//第一行空白数的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
}
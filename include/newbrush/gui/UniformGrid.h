#pragma once
#include "newbrush/gui/Panel.h"

namespace nb {

class NB_API UniformGrid : public Panel
{
	RTTR_ENABLE(Panel)
public:
	UniformGrid();

	static DependencyPropertyPtr RowsProperty();			//行数的依赖属性
	static DependencyPropertyPtr ColumnsProperty();		//列数的依赖属性
	static DependencyPropertyPtr FirstColumnProperty();	//第一行空白数的依赖属性（需显式指定了Colums才有效，如果大于等于Colums也无效）

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
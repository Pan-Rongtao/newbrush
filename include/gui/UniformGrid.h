#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class NB_API UniformGrid : public Panel
{
public:
	UniformGrid();

	core::Property_rw<int32_t>		Rows;		//行数
	core::Property_rw<int32_t>		Columns;	//列数
	core::Property_rw<int32_t>		FirstColumn;//第一行中前导空白单元格数量，需显式指定了Colums才有效，如果大于等于Colums也无效

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
}
#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class UniformGrid : public Panel
{
public:
	core::Property_rw<uint32_t>		Rows;		//行数
	core::Property_rw<uint32_t>		Columns;	//列数
	core::Property_rw<uint32_t>		FirstColumn;//第一行中前导空白单元格数量

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}
}
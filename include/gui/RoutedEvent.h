#pragma once

namespace nb{
namespace gui{

enum class RoutingStrategy
{
	tunnel,		//隧道方式，事件由元素树的根到源元素传递
	bubble,		//冒泡方式，与tunnel相反
	direct,		//直达，
};

class RoutedEventManager
{
public:
};

}
}
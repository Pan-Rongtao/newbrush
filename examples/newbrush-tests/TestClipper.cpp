#include "catch2/catch.hpp"
#include "clipper.hpp"

using namespace ClipperLib;

TEST_CASE("Test Clipper", "[Clipper]")
{
	Path subj;
	Paths solution;
	subj <<
		IntPoint(0, 0) << IntPoint(100, 0) << IntPoint(100, 100) <<
		IntPoint(0, 100);
	ClipperOffset co;
	co.AddPath(subj, jtSquare, etOpenSquare);
	co.Execute(solution, 5);
	

}
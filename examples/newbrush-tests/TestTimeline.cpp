#include "media/Timeline.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("test Timeline", "[Timeline]")
{
	SECTION("timeline1")
	{
		Timeline tl1;
		tl1.setBeginTime(TimeSpan::fromSeconds(0));
		tl1.setDuration(TimeSpan::fromSeconds(1));
		CHECK(tl1.getCurrentTime() == TimeSpan::zero());
		CHECK(tl1.getCurrentProgress() == 0);
		tl1.setAutoReversel(true);
		tl1.setRepeatBehavior(RepeatBehavior::fromDuration(TimeSpan::fromSeconds(3)));
		tl1.StateChanged += [](const EventArgs &args) {
			auto tl = static_cast<Timeline *>(args.sender);
			auto state = tl->currentState();
			printf("timeline state chaged = %d\n", state);
		};
		tl1.Process += [](const EventArgs &args) {
			auto tl = static_cast<Timeline *>(args.sender);
			auto time = tl->getCurrentTime();
			auto progress = tl->getCurrentProgress();
			printf("timeline procesing: time[%s], progress[%.5f]\n", time.toString().data(), progress);
		};
		tl1.Completed += [](const EventArgs &args) {
			printf("timeline complete\n");
		};
		tl1.begin();
		
		while (true)
		{
			Timer::driveInLoop();
		}
	}

}

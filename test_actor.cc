#include "actor.h"
#include "util.h"

using namespace scoa;

class foo : public actor<foo> {
public:
	auto
	be()
	{
		return match{
			[] {}
		};
	}
};

#ifdef SCOA_TEST_SINGLE
int
main()
#else
void
test_actor()
#endif /* SCOA_TEST_SINGLE */
{
	foo a;
}

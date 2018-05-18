#include "actor.h"
#include "match.h"

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

int
main()
{
	foo a;
	return 0;
}

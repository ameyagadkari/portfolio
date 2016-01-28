#include"bit_array.h"

#if defined _DEBUG
#define _CRTDEBUG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>
#else
#include<cstdlib>
#endif //_DEBUG

void main(int i_argc, char ** i_argl)
{
	Engine::Containers::bit_array_UnitTest();

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
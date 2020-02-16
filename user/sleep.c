#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("error, must give sleep time.\n");
		exit();
	}
	sleep(atoi(argv[1]));
	exit();
}

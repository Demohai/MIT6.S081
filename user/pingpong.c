#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
	char buf[10];
	int p1[2];
	int p2[2];
	pipe(p1);
	pipe(p2);
	if (fork() == 0)
	{
		close(p1[1]);
		close(p2[0]);
		write(p2[1], "pong", 4);
		read(p1[0], buf, sizeof(buf));
		printf("%d: received %s\n", getpid(), buf);
		close(p2[1]);
		close(p1[0]);
	}
	else
	{
		close(p1[0]);
		close(p2[1]);
		write(p1[1], "ping", 4);
		read(p2[0], buf, sizeof(buf));
		printf("%d: received %s\n", getpid(), buf);
		close(p1[1]);
		close(p2[0]);
	}
	exit();
}

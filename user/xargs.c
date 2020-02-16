#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char* argv[]){
	char buf[100];
	char tmp[50][50];
	char* cmd[50];
	int i, p, j;
	j = 0;
	gets(buf, sizeof(buf));
	for (p = 0; p < argc - 1; p++) {
		cmd[p] = argv[p+1];
	}
	for (i = 0; i < strlen(buf); i++) {
		if (buf[i] != ' ') {
			tmp[p][j] = buf[i];
			j++;
		}
		else {
			tmp[p][j] = '\0';
			cmd[p] = tmp[p];
			p++;
			j = 0;
		}
	}
	tmp[p][j] = '\0';
	cmd[p] = tmp[p];

	if (fork() == 0) {
		exec(cmd[0], cmd);
	}
	wait();
	exit();
}

#include "kernel/types.h"
#include "user/user.h"

void redirect(int k, int p[2]){
	close(k);
	dup(p[k]);
	close(p[0]);
	close(p[1]);
}

void primeprocess(){
	int p;
	int pfd[2];
	while (read(0, &p, sizeof(int))) {
		printf("prime: %d\n", p);
		pipe(pfd);
		if (fork() == 0) {
			redirect(0, pfd);
			continue;
		}
		else {
			int i;
			redirect(1, pfd);
			while (read(0, &i, sizeof(int))) {
				if (i % p) 
					write(1, &i, sizeof(int));
			}
		}
	}
}

void source() {
	int n;
	for (n = 2; n <= 35; n++) {
		write(1, &n, sizeof(int));
	}
}

void main(int argc, char* argv[]){
	int p[2];
	pipe(p);
	if (fork() == 0){
		redirect(0, p);
		primeprocess();
	}
	else {
		redirect(1, p);
		source();
	}
	exit();
}

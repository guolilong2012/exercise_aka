#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1024

int main(void)
{
	pid_t pid;
	char buf[MAX];

	if(getcwd(buf, MAX) == NULL){ /* 得到修改后的工作目录 */
		perror("fail to get pwd");
		exit(1);
	}

	printf("the parent’s pwd is : %s\n", buf);

	pid = fork(); /* 创建一个子进程 */

	if(pid == -1){
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		printf("the child\n");

		if(chdir("/home/akaedu/") == -1){ /* 改变进程的工作目录 */
			perror("fail to change dir");
			exit(1);
		}

		if(getcwd(buf, MAX) == NULL){ /* 得到子进程的工作目录 */
			perror("fail to get pwd");
			exit(1);
		}

		printf("the child’s pwd is : %s\n", buf); /* 打印子进程修改后的工作目录 */
	}else{
		if(wait(NULL) == -1){ /* 避免僵尸进程 */
			perror("fail to wait");
			exit(1);
		}

		if(getcwd(buf, MAX) == NULL){ /* 再次得到父进程的工作目录 */
			perror("fail to get pwd");
			exit(1);
		}

		printf("the parent’s pwd is : %s\n", buf); /* 输出提示信息 */
	}

	return 0;
}

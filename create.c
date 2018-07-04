#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

#define BUFSIZE 100

int main(int argc, char ** argv)
{

	int fd;
	int count;
	char wbuf[BUFSIZE];
	char rbuf[BUFSIZE];
	
	printf("argv[0]=%s\n",argv[0]);
	printf("argv[1]=%s\n",argv[1]);

	fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC, \
		0764);
	if(fd <0)
	{
		printf("usage : %s filename \n", argv[0]);
		return -1;
	}
//	printf("fd=%d\n",fd);
	
	sprintf(wbuf, "Do not count the before they hatch");
	printf("%s\n", wbuf);
	count = write(fd, wbuf, strlen(wbuf));
	
	if(count < 1)
	{
		printf("file write error!\n");
		return -1;
	}
	// offset을 0으로 커서를 가장 처음의 위치로 이동	
	lseek(fd,0,SEEK_SET);
	
	// 배열의 값을 0으로 세팅
	memset(rbuf,0,BUFSIZE);
	count = read(fd,rbuf,BUFSIZE);
	if(count <1)
	{
		printf("file read error!\n");
		return -1;
	}
	printf("%s\n",rbuf);

	close(fd);
	return 0;
}

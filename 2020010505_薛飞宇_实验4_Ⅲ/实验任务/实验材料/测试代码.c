#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
main()
{
    int fd, num;
    char buf[10];

                                                                                                              //��"/dev/demo"
    fd = open("/dev/demo", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd != -1 )
  	{	                                                                                                        //���ζ�demo
	  read(fd, buf, 10);
	  printf("The demo is %s\n", buf);    
   //дdemo
    printf("Please input the string written to demo\n");
    scanf("%s", &buf);
    write(fd, buf, 10);
    read(fd, buf, 10);
    printf("The demo is %s\n", buf);
    
    ioctl(fd, 1, 1); 
    close(fd);
    }
    else
	{
	printf("Device open failure\n");
	}
}

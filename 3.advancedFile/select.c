#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stddef.h>
int main(int argc, char**argv){
	
	int fd;
	int wd1, wd2;
	int ret;
	
	struct timeval timeout;
	fd_set fds;
	char buf[1024];

	struct inotify_event* event;

	fd = inotify_init();
	if (fd == -1){
		printf("inotify_init() fail\n");
		return -1;
	}
	
	wd1 = inotify_add_watch(fd, ".", IN_CREATE | IN_DELETE);
	if (wd1 == -1){
		printf("add watch() fail\n");
		goto err;
	}

	wd2 = inotify_add_watch(fd, "../1.fileOpen", IN_CREATE | IN_DELETE);
        if (wd2 == -1){
                printf("add watch() fail\n");
                goto err; 
        }
	





	while(1){
		/*
		ret = read(fd,buf,sizeof(buf));
		if (ret == -1 ){
			printf("read() fail\n");
			goto err;
		}
		*/
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		FD_SET(STDIN_FILENO, &fds);
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;


		ret = select(fd > STDIN_FILENO ? fd + 1 : STDIN_FILENO + 1,
			&fds, NULL, NULL, &timeout	
				);
		if (ret == -1){
			goto err;
		}
		else if (ret == 0){
			printf("select() timeout occurred\n");
			break;
		}else if (ret > 0){
			if (FD_ISSET(fd, &fds)){
				ret = read(fd,buf,sizeof(buf));
				if (ret == -1){
					printf("read() fail\n");
					break;
				}
				event = (struct inotify_event *)buf;
                  		while( ret > 0){
                          
                          		if (event -> mask & IN_CREATE){
                                 		 printf("file %s created\n",event->name);
                         		 }               
                          		if (event -> mask & IN_DELETE){
                                  		printf("file %s deleted\n",event->name);
                          		}
                          		event = (char *)event + sizeof(struct inotify_event) + event->len;
                          		ret -= (sizeof(struct inotify_event) + event->len);
  
                 		 }
			}else if(FD_ISSET(STDIN_FILENO,&fds)){
				memset(buf,0,sizeof(buf));
				ret = read(STDIN_FILENO,buf,sizeof(buf));
				if (ret == -1){
					printf("read() fail\n");
					break;
				}
				printf("user input [%s]\n",buf);
			}
		}
		

	}
	close(wd1);
	close(wd2);
	close(fd);

	
 		

	return 0;

	err:
	if (fd >= 0){
		close(fd);
	}
	if (wd1 >= 0){
		close(wd1);
	}
	if (wd2 >= 0){
		close(wd2);
	}
}	

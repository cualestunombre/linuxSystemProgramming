#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <stddef.h>
// epoll_create -> epoll 인스턴스 생성
// epoll_ctl -> epoll에 I/O 등록
// epoll_wait -> epoll 감시 시작 
int main(int argc, char**argv){
	
	int fd;
	int wd1, wd2;
	int ret;
	int epfd = -1;
	char buf[1024];

	struct inotify_event* event;
    struct epoll_event epvent;

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
	
    epfd = epoll_create1(0);
    if (epfd == -1){
        printf("epoll_create() fail\n");
        goto err;
    }
    memset(&event,0,sizeof(event));
    epvent.events = EPOLLIN;
    epvent.data.fd = fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd,&epvent) == -1){
        printf("epoll_ctl() fail\n");
        goto err;
    }

    memset(&event,0,sizeof(event));
    epvent.events = EPOLLIN;
    epvent.data.fd = STDIN_FILENO;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO,&epvent) == -1){
        printf("epoll_ctl() fail\n");
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
        memset(&epvent,0,sizeof(epvent));
		ret = epoll_wait(epfd,&epvent, 1,5000);

		if (ret == -1){
			goto err;
		}
		else if (ret == 0){
			printf("epoll_Wait() timeout occurred\n");
			break;
		}else if (ret > 0){
			if (event.data.fd == fd){
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
			}else if(event.data.fd == STDIN_FILENO){
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
    close(epfd);
	close(wd1);
	close(wd2);
	close(fd);

	
 		

	return 0;

	err:
	if (fd >= 0){
		close(fd);
	}
    if (epfd >= 0){
		close(epfd);
	}
	if (wd1 >= 0){
		close(wd1);
	}
	if (wd2 >= 0){
		close(wd2);
	}
}	

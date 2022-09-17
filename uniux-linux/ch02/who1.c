#include	<stdio.h>
#include	<utmp.h>
#include	<fcntl.h>
#include    <stdlib.h>
#include	<unistd.h>
#define	SHOWHOST	/* include remote machine on output */
#define UTMPX_FILE "/var/run/utmpx"
// 代码里show_info 并没有在main函数中提前声明。
void show_info(struct utmp *utbufp ){
	printf("%-8.8s", utbufp->ut_name);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");				/* a space	*/
	printf("%10ld", utbufp->ut_time);	/* login time	*/
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/
}
int main(){
	struct utmp	current_record;	/* read info into here       */
	int		utmpfd;		/* read from this descriptor */
	int		reclen = sizeof(current_record);

	if ( (utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1 ){
		
        perror( UTMPX_FILE );	/* UTMP_FILE is in utmp.h，在macos中UTMP_FILE 是没有定义的，    */
		exit(1); // 这个需要导入stdlib.h 头文件
	}

	while ( read(utmpfd, &current_record, reclen) == reclen ){
		show_info(&current_record);
    }
	close(utmpfd);
	return 0;			/* went ok */
}


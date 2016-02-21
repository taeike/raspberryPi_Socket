#include "tstlib.h"

#define LISTEN_BLOCK 20	// 한번에 20개의 접속 요청 처리
#define THIS_IP "192.168.10.40" 
// IP는 각자 Pi 에 지정한 것을 사용한다. 난 192.168.10.40 이다. 고정 IP로 사용하는게
// 정신건강에 좋다.

void setGpio(int pino, int value);

main()
{
	int	sock, ret, c_fd;

	int	c_sock_size;
	int	rec_len;
	int	m_sw = 0;

	char	recv_buf[1024];
	char	send_buf[1024];
	
	struct sockaddr_in serv_sock;
	struct sockaddr_in c_sock;

	c_sock_size = sizeof(struct sockaddr);

	printf("Initialze GPIO Socket Server.....................\r");
	fflush(stdout);
	printf("wiringPi Setup........................\n");
	sleep(2);
	if(wiringPiSetup() == -1)	{
		printf("GPIO Setup error\n");
		exit(0);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)	{
		switch(errno)	{
			case EAFNOSUPPORT :
				printf("이 버전에서는 특정 주소 집합을 지원하지 않습니다.\n");
				//printf("구현버전에서  특정주소 집합(address family)를 지원하지 않는다.\n");
				break;
			case EMFILE :
				printf("현재 프로세스는 FD(File Descriptor)를 생성 할 수 없습니다.\n");
				//printf("해당 프로세스에서 더이상 파일 디스크립터(file descriptor)를 생성할 수 없다..\n");
				break;
			case ENFILE :
				printf("시스템에서 FD(File Descriptor)를 생성할 수 없습니다\n");
				//printf("시스템에서 더이상 파일 디스크립터를 생성할 수 없다.\n");
				break;
			case EPROTONOSUPPORT :
				printf("현재 버전은 지원하지 않는 프로토콜 입니다.\n");
				//printf("주소집합 혹은 구현버전에서 지원하지 않는 프로토콜이다.\n");
				break;
			case EPROTOTYPE :
				printf("프로토복이 지원하지 않는 소켓 타입 입니다|n");
				//printf("프로토콜에서 지원하지 않는 소켓 타입이다.\n");
				break;
		}
		printf("Socket createion error\n");
		exit(0);
		// 혹은 오류시 처리할 내용을 넣어준다.
	}
	// socket 이 이제 준비 되었으니
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_addr.s_addr = inet_addr(THIS_IP);
	serv_sock.sin_port = htons(6666);
	bzero(&(serv_sock.sin_zero), 8);
	
	ret = bind(sock, (struct sockaddr *)&serv_sock, sizeof(serv_sock));
	if(ret < 0) {
		printf("Bind 시 오류 발생 : (%d)\n", errno);
		exit(1);
	}
	
	// bind 가 성공 했으면 그냥 listen 을 하면 접속 대기 상태로 들어간다.
	printf("GPIO Server Start.............\n");
	while(1)	{
		ret = listen(sock, LISTEN_BLOCK);
		if(ret < 0) {
		    printf("listen(serv_fd, LISTEN_BLOCK) Error...\n");
		    return(ret);
		}
	
		c_fd = accept(sock, (struct sockaddr *)&c_sock, &c_sock_size);
	
		printf("connect IP : (%s)\n", inet_ntoa(c_sock.sin_addr));
	
		while(1)	{
			memset(recv_buf, 0x00, 1024);
			memset(send_buf, 0x00, 1024);
			if(c_fd == -1)	{
				printf("client connect error...\n");
				break;
			}
	
			rec_len = recv(c_fd, (char *)recv_buf,sizeof(recv_buf), 0);
			if(rec_len < 1)	{
				//printf("receive length error \n");
				printf("client disconnected...\n");
				break;
			}

			if(strncmp(recv_buf, "/exit", 5) == 0)	{
				printf("Client request exit server message ...\n");
				printf("disconnect & server down....\n");
				strcpy(send_buf, "I'm going down your request...\n");
				send(c_fd, (char *)&send_buf, strlen(send_buf), 0);
				m_sw = 1;
				break;
			}
			recv_buf[rec_len - 1] = 0x00;
			printf("Receive : [%s]\n", recv_buf);
			GPIO_CONTROL(recv_buf, c_fd);

			recv_buf[rec_len - 1] = 0x00;
			send(c_fd, (char *)&send_buf, strlen(send_buf), 0);
		}
		if(m_sw == 1)
			break;
	}
	close(sock);
	sleep(2);
}
/** ---------------------------------------------------------------------- **/
GPIO_CONTROL(char *ControlStr)
{
	int	gpio_rst;
	char	Head[128];
	char	Tail[128];

	memset(Head, 0x00, sizeof(Head));
	memset(Tail, 0x00, sizeof(Tail));
	
	char	c_pino[10],	c_mode[10], c_value[10];
	int	i_pino, i_mode, i_value;

	fnToken(ControlStr, Head, Tail, ',');
	strcpy(c_pino, Head);

	fnToken(Tail, Head, Tail, ',');
	strcpy(c_mode, Head);

	strcpy(c_value, Tail);


	i_pino = atoi(c_pino);
	i_mode = atoi(c_mode);
	i_value = atoi(c_value);

/**	debug
	printf("Pi No : [%s][%d]\n", c_pino, i_pino);
	printf("Mode  : [%s][%d]\n", c_mode, i_mode);
	printf("Value : [%s][%d]\n", c_value, i_value);
	gpio_rst = GPIOFnc[i_pino].FuncPnt(i_value);
**/
	setGpio(i_pino, i_value);

}

void setGpio(int pino, int value)
{
    printf("Pin : %d, Value : %d\n", 4, value);
    pinMode(pino, OUTPUT);
    digitalWrite(pino, value);
}

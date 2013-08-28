#include <iostream>

const int MESSAGE_CONTENT_LENTH = 150 ;
const int ID_LENTH = 7;
const int DATE_LENTH = 15;
const int LIST_LENTH = 1200;

class MESSAGE{
private:
    char send_ID[ID_LENTH];
    char recv_ID[ID_LENTH];
    char date[DATE_LENTH];
    char content[MESSAGE_CONTENT_LENTH];
public:
    MESSAGE();
    ~MESSAGE();
    void Set_send_ID();
    void Set_recv_ID();
    void Set_date();     
    void Set_content();
    char * Get_send_ID();
    char * Get_recv_ID();
    char * Get_date();
    char * Get_content();
};
class MESSAGE_RECEIVCE:public MESSAGE{
private:
	bool read;                        //标记短信状态，true为已读，false为未读
public:
	bool is_read();
	void set_read();
};
class MESSAGE_SEND:public MESSAGE{
public :
	int ToString(char *);
};

template <class T>
class DATABASE{
private:
    char location[50];					
	T * list[LIST_LENTH];	
    int list_count;
public:
	void add(T)
    void delet();
    void gai();
    void select();
};
template<class T>
void DATABASE<T>::add(T message)
{
	T * tmessage = new T(message);
	list[list_count++] = tmessage;
}



void Recieve_In_Thread()
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息

	if (!err)
	{
		printf("客户端嵌套字已经打开!\n");
	}
	else
	{
		printf("客户端的嵌套字打开失败!\n");
		return;//结束
	}
	while(1)
	{
		SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
		SOCKADDR_IN clientsock_in;
		clientsock_in.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
		clientsock_in.sin_family=AF_INET;
		clientsock_in.sin_port=htons(6000);

		Sleep(1000);
		int s = connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接
		if(s == SOCKET_ERROR) 
		{
			//printf("connect error!\n");
			continue;
		}
		char receiveBuf[1200];
		recv(clientSocket,receiveBuf,1201,0);
		printf("%s\n",receiveBuf);

		send(clientSocket,"hello,this is client",strlen("hello,this is client") + 1,0);
		closesocket(clientSocket);		
	}
	WSACleanup();
}
class CLIENT{
private:
    char ID[ID_LENTH];
    MESSAGE * search_list[LIST_LENTH];	//搜索结果列表
    int sch_list;						//搜索结果数量
    char host[16];						//服务器ip
	u_short port;						//服务器端口
	DATABASE<MESSAGE_RECEIVCE> * db_rec;
	DATABASE<MESSAGE_SEND> * db_send;
public:
	int Send(MESSAGE_SEND);
    void Recieve();
    void Show_List();
    void Show_Message();
    bool Sch();
    void Get_Datebase();
    void Save_Datebase();
	friend void Recieve_In_Thread();
};
int CLIENT::Send(MESSAGE_SEND message)
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息

	if(err)
	{
		return err;//结束
	}
	SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr=inet_addr(host);
	clientsock_in.sin_family=AF_INET;
	clientsock_in.sin_port=htons(port);
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接

	char buffer[1024];
	int length = message.ToString(buffer);
	
	int status = send(clientSocket,buffer,length + 1,0);
	if(status != SOCKET_ERROR)
	{
		closesocket(clientSocket);
		WSACleanup();
		if(db_send == NULL) return 404;
		else db_send->add(message);
	}
	else
	{
		return status;
	}
}
void CLIENT::Recieve()
{
	HANDLE h1;
	h1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Recieve_In_Thread,NULL,0,NULL);
}

int main()
{

    return 0;
}

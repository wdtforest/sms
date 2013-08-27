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
    bool read;                        //标记短信状态，true为已读，false为未读
    void Set_send_ID();
    void Set_recv_ID();
    void Set_date();
    void Set_content();
    char * Get_send_ID();
    char * Get_recv_ID();
    char * Get_date();
    char * Get_content();
    char * ToString();
};

class CLIENT{
private:
    char ID[ID_LENTH];
    MESSAGE * recieve_list[LIST_LENTH];
    int rcv_list;
    MESSAGE * send_list[LIST_LENTH];
    int snd_list;
    MESSAGE * search_list[LIST_LENTH];
    int sch_list;
    char host[16];
    char database_location[50];
public:
    int Send();
    void Recieve_In_Thread();
    void Recieve();
    void Show_List();
    void Show_Message();
    bool Sch();
    void Get_Datebase();
    void Save_Datebase();
};

class DATABASE{
private:
    char location[50];
public:
    void add();
    void delet();
    void gai();
    void select();

};

int main()
{

    return 0;
}

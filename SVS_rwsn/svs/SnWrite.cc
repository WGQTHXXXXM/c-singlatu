#include "SnWrite.h"


CSnWrite::CSnWrite(int connect,char *accept)
{
    m_iconnet_accept = connect;
    strcpy(m_chAccept,accept);
}

bool CSnWrite::doSend()
{
	char cmd[MAXLINE] = "/usr/local/bin/fw_setenv sn ";
	strcat(cmd,&m_chAccept[3]);
	char sendData[MAXLINE]={0};
	sendData[0]=2;
	sendData[1]=CMD_WRITE_SN_I;

	FILE* fstream = NULL;
	fstream = popen(cmd,"r");
	if(fstream==NULL)
	{
	    sendData[2]=0;
	    send(m_iconnet_accept, sendData, MAXLINE,0);
		pclose(fstream);
	    return true;
	}
	pclose(fstream);
	sendData[2]=1;
	send(m_iconnet_accept, sendData, 3,0);
    
    return true;
}

/*
[��� ���]
-Visual Studio 2019 ���� ����-
1. ���ο� ������Ʈ�� ���弼��.
2. ���� >> NuGet ��Ű�� ������ >> �ַ�ǿ� NuGet ��Ű�� ����
3. ã�ƺ��� Ŭ��
4. �ش� ��Ű���� �˻��� ��ġ ���ּ���. (�ݵ�� �ش� ������Ʈ�� üũ�ϰ� ��ġ) 
    boost 
    cpprestsdk.v142
    openssl-vc142
	JsonCpp.Windows
5. CodeCatch.cpp ������ �����ɴϴ�. 
6. CodeCatch.cpp �ڵ忡�� �� ��ȣ�� �Է����ּ���.
7. Ctrl + F5 ����
*/
#include <iostream>
#include <cpprest/ws_client.h>
#include <json/json.h>
using namespace std;
using namespace web;
using namespace web::websockets::client;
#pragma warning(disable: 4996)

#define PINNUMBER "95514048" //���⿡ �ɳѹ��� �Է����ּ���

websocket_client client;
class CatchObj {
public:
	float x;
	float y;
	int type;
};
void play(CatchObj* catchobj, int objsize);
void PlaySend();

// ���������� ������ �Դϴ�. -----------------
bool attack = true;  // boolean : false or true
float angle = 90.0f;  // float : 0~360.0
int type = 1; // int : 0,1,2,3
// -----------------------------------
 
// �����Ͻø� �ȵ˴ϴ�! -------------------------------------------------------------------------
int main()
{
	bool IsConnect = false;
	try {
		client.connect(U("ws://k7c106.p.ssafy.io:8080")).wait();
		cout << "�������� ���ῡ �����ϼ̽��ϴ�." << endl;
		cout << "---------------------------------" << endl;
	}

	catch (std::exception const& e)
	{
		cout << "�������� ���ῡ �����ϼ̽��ϴ�."<<endl;
		cout << "---------------------------------" << endl;
		exit(1);
	}

	//�� ��ȣ ����
	websocket_outgoing_message msg;

	Json::Value Data;
	Data["action"] = "CodeInit";
	Data["pinnumber"] = PINNUMBER;

	Json::StyledWriter writer;
	string str = writer.write(Data);

	msg.set_utf8_message(str);
	try {
		client.send(msg).wait();
	}
	catch(std::exception const& e)
	{
		cout << "�� ��ȣ ���޿� �����ϼ̽��ϴ�."<<endl;
		cout << "---------------------------------" << endl;
		exit(1);
	}

	while (true) {
		try {
			client.receive().then([](websocket_incoming_message in_msg)
				{
					return in_msg.extract_string();
				}).then([](string body) {
					Json::Reader _reader;
					Json::Value _data;
					
					_reader.parse(body, _data);

					if (_data["action"] == "ConnectFail")
					{
						
						cout << "�����͸� ���� ���� ���߽��ϴ�."<<endl;
						cout << "---------------------------------" << endl;
						exit(1);
					}
					else 	if (_data["action"] == "ConnectSuccess")
					{
						cout << _data["log"].asString()<<endl;
					}
					else if (_data["action"] == "exeData")
					{
						CatchObj *catchobj = new CatchObj[_data["catchobj"].size()];
						int size = _data["catchobj"].size();
						for (int i = 0; i < _data["catchobj"].size(); ++i)
						{
							catchobj[i].x = _data["catchobj"][i][0].asFloat();
							catchobj[i].y = _data["catchobj"][i][1].asFloat();
							catchobj[i].type = _data["catchobj"][i][2].asInt();
						}
						play(catchobj,size);
					}
					
					}).wait();
		}
		catch (std::exception const& e)
		{
			cout << "�������� ������ ���������ϴ�." << endl;
			cout << "---------------------------------" << endl;
			exit(1);
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------------------
void play(CatchObj *catchobj,int objsize)
// catchobj : ���� �޴� ������Ʈ ����
// CatchObj[i][0] -> ��ü x ��ġ ��ǥ
// CatchObj[i][1] -> ��ü y ��ġ ��ǥ
// CatchObj[i][2] -> ��ü Ÿ�� ����

// objsize : ��ü ������
{

	//���⼭ ���� �ڵ� ���ּ���-------------------------------------------------
	for (int i = 0; i < objsize; ++i)
		cout << catchobj[i].x << " " << catchobj[i].y << " " << catchobj[i].type << endl;







	//------------------------------------------------------------------
	PlaySend();
}

void PlaySend()
{
	Json::Value CodeData;

	CodeData["action"] = "codeData";
	CodeData["pinnumber"] = PINNUMBER;
	CodeData["attack"] = attack;
	CodeData["angle"] = angle;
	CodeData["type"] = type;

	Json::StyledWriter _writer;
	string str = _writer.write(CodeData);
	websocket_outgoing_message _msg;
	_msg.set_utf8_message(str);

	try {
		client.send(_msg).wait();
	}
	catch (std::exception const& e)
	{
		cout << "������ ���޿� �����߽��ϴ�." << endl;
		cout << "---------------------------------" << endl;
		exit(1);
	}
}

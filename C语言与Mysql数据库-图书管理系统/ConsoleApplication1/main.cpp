#include<Windows.h>
#include<mysql.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<cstring>
#include<string.h>

#pragma comment (lib,"libmysql.lib")
using namespace std;
MYSQL mysql;  //����mysql����
MYSQL_RES *result;//������������
MYSQL_ROW row;   //�����б���
char ch[2];



void showmenu()  //��ʾ����ͼ����Ϣ
{
	system("cls");// ����
	cout << "\n\n\n\n\n";
	cout << "\t||=================================================================||\n";
	cout << "\t||               welcome to lemon books system                     ||\n";
	cout << "\t||=================================================================||\n";
	cout << "\t||\t 1 - ��ʾ����ͼ����Ϣ                                      ||\n";
	cout << "\t||\t 2 - ���ͼ����Ϣ                                          ||\n";
	cout << "\t||\t 3 - �޸�ͼ����Ϣ                                          ||\n";
	cout << "\t||\t 4 - ɾ��ͼ����Ϣ                                          ||\n";
	cout << "\t||\t 5 - ��ѯͼ����Ϣ                                          ||\n";
	cout << "\t||\t 6 - �˳�                                                  ||\n";
	cout << "\t||=================================================================||\n";
	cout << "\n                          ENTER YOUR CHOICE (1 - 6):";
}


void inquire()    //ѯ���û��Ƿ���ʾ���˵�
{
	cout << "\t ��ʾ���˵�����y/n):";
	cin >> ch;
	if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		showmenu();  //��ʾ���˵�
	}
	else
	{
		exit(0);
	}
}


void showall()//  ��ʾ����ͼ����Ϣ
{
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t���ݿ�����ʧ��!" << endl;
	else
	{
		//cout << "���ݿ����ӳɹ�" << endl;
		if (mysql_query(&mysql, "select * from tb_book "))
		{
			cout << "��ѯtb_book���ݱ�ʧ��" << endl;
		}
		else
		{
			//cout << "��ѯ�ɹ�" << endl;
			result = mysql_store_result(&mysql);   //��ý����
			if (mysql_num_rows(result) != NULL)     //�������Ϊ�գ��м�¼�����
			{
				cout << "\t============================================================\n";
				cout << "\t                  ��ʾ����ͼ����Ϣ                          \n";
				cout << "\t============================================================\n";
				cout << "\tͼ����        ͼ����          ����          ������        \n";
				cout << "\t------------------------------------------------------------\n";
				while (row = mysql_fetch_row(result))    //ȡ��������м�¼
				{
					cout << "\t" << row[0] << "               "<<row[1]<<"               " << row[2]<<"           " << row[3] << endl;
					//fprintf(stdout, "\t     %s       %s       %s           %s\n", row[0], row[1], row[2], row[3]);
				}
				
				cout << "\t============================================================\n";
			}
			else
			{
				cout << "\n\tû�м�¼��Ϣ ��\n";
			}
			mysql_free_result(result);//�ͷŽ����

		}
		mysql_close(&mysql);  //�ͷ�����

	}
	inquire();    //ѯ���Ƿ���ʾ���˵�
}


void addbook()
{
	int rowcount;//������еĶ�����
	char id[10];
	char bookname[50];
	char author[50];
	char bookconcern[100];
	char *sql;
	char dest[230] = { "" };
	//�������ݿ�
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19",3306, NULL, 0))
		cout << "\n\t���ݿ�����ʧ��" << endl;
	else
	{
		//���ݿ����ӳɹ�
		cout << "\t=============================================================\n";
		cout << "\t                         ���ͼ����Ϣ                        \n";
		cout << "\t=============================================================\n";
		if (mysql_query(&mysql, "select * from tb_book"))
		{
			cout << "\n\t ��ѯ tb-book ���ݱ�ʧ�ܣ�\n";
		}
		else
		{
			result = mysql_store_result(&mysql);//��ý����
			rowcount = mysql_num_rows(result);    //�������
			row = mysql_fetch_row(result);//��ý��������
			//cout << "\t   ID :";
			printf("\t  ID:");
			scanf("%s", id);
		//	cin >> id;    //����ͼ����
			if (mysql_num_rows(result) != NULL)
			{
				//�ж�����ı���Ƿ����
				do
				{
					if (!strcmp(id, row[0]))
					{
						cout << "\t��¼���ڣ��������������";
						//getch();
			            system("pause");
						mysql_free_result(result);//�ͷŽ����
						mysql_close(&mysql);//�ͷ�����
						return;

					}
				} while (row = mysql_fetch_row(result));
			}
			//��������ͬ�ı��

			//cout << "\t  ͼ����:";
			printf("\t ͼ������");
			//cin >> bookname;
			scanf("%s", &bookname);
	
			//printf("\t ���ߣ�");
			////	cout << "\t Author:";// cin >> author;
			//scanf("%s", &author);
			//printf("\t  �����磺");
			////cout << "\t Bookconcern:"; //cin >> bookconcern;
			//scanf("%s", &bookconcern);
			sql = "insert into tb_book (ID,bookname,author,bookconcern) values (";
			strcat(dest,sql); 
			strcat(dest, "'");
			strcat(dest,id); 
			strcat(dest, "', '"); //strcat(dest, " sc");
			strcat(dest,bookname);
			printf("\t ���ߣ�");
		//	cout << "\t Author:";// cin >> author;
			scanf("%s",&author);
			strcat(dest,"', '");
			strcat(dest,author);
		    printf("\t  �����磺");
			//cout << "\t Bookconcern:"; //cin >> bookconcern;
			scanf("%s", &bookconcern);
			strcat(dest, "', '");
			strcat(dest,bookconcern);
			strcat(dest,"')");
			//cout << dest;
			
			printf("%s", dest);
		

			if (mysql_query(&mysql, dest) != 0)
				fprintf(stderr, "���ܲ����¼��", mysql_error(&mysql));
			//	cerr << "���ܲ����¼" << mysql_error(&mysql);
			else
				cout << "\t����ɹ�!" << endl;
			mysql_free_result(result);//�ͷŽ����
		}
		mysql_close(&mysql);//�ͷ�����
	}
	inquire();//ѯ���Ƿ���ʾ���˵�
}


void modifybook()  //�޸�ͼ����Ϣ
{
	char id[10];
	char *sql;
	char dest[230] = { " " };
	char dest1[230] = { " " };
	char bookname[50];
	char author[50];
	char bookconcern[100];


	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t���ݿ�����ʧ��" << endl;
	else
	{
		//���ݿ����ӳɹ�
		cout << "\t ����������Ҫ�޸ĵ�ͼ����.";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);  //��ͼ����׷�ӵ�sql������
		if (mysql_query(&mysql, dest))
			cout << "\n\t ��ѯ tb-book ���ݱ�ʧ�ܣ�\n";
		else
		{
			result = mysql_store_result(&mysql);  //��ý����
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t ���ּ�¼��Ϣ���Ƿ���ʾ�� ��y/n)\n";
				cin>>ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                 **** ��ʾͼ����Ϣ****                      \n";
					cout << "\t============================================================\n";
					cout << "\tͼ����        ͼ����          ����          ������        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //ȡ��������м�¼
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
					cout << "\t modify? (y/n)\n";
					cin >> ch;
					if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
					{
						//cout << "\t  ͼ������";
						//cin >> bookname;
						printf("\t ͼ������");
						scanf("%s",& bookname);
						sql = "update tb_book set  bookname= '";
						strcat(dest1, sql);
						strcat(dest1, bookname);
						//cout << "\t ���ߣ�";
						printf("\t ���ߣ�");
						//cin >> author;
						scanf("%s", &author);
						strcat(dest1, "', author = '");
						strcat(dest1, author);
						//cout << "\t �����磺";
						//cin >> bookconcern;	
						printf("\t �����磺");
						scanf("%s", &bookconcern);
						strcat(dest1, "', bookconcern = '");
						strcat(dest1, bookconcern);
						strcat(dest1, "'where id = ");
						strcat(dest1, id);
						if (mysql_query(&mysql, dest1) != 0)
						{
							cerr << "�����޸ļ�¼��\n" << mysql_error(&mysql);
						}
						else
							cout << "\t �޸ĳɹ���\n";
					}
				}
			}
			else
				cout << "\t û�з���Ҫ�޸ĵ���Ϣ��\n";
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}


void deletebook()
{
	char id[10];
	char *sql;
	char dest[100] = { " " };
	char dest1[100] = { " " };

	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t���ݿ�����ʧ��" << endl;
	else
	{
		cout << "\t ����������Ҫɾ����ͼ����.\n";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);  //��ͼ����׷�ӵ�sql������

		//��ѯͼ����Ϣ�Ƿ����
		if (mysql_query(&mysql, dest))
			cout << "\n\t ��ѯ tb-book ���ݱ�ʧ�ܣ�\n";
		else
		{
			result = mysql_store_result(&mysql);  //��ý����
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t ���ּ�¼��Ϣ���Ƿ���ʾ�� ��y/n)\n";
				cin>> ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                 **** ��ʾͼ����Ϣ****                      \n";
					cout << "\t============================================================\n";
					cout << "\tͼ����        ͼ����          ����          ������        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //ȡ��������м�¼
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
				}
				cout << "\t �Ƿ�ɾ���� ��y/n)\n";
				cin >> ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					sql = "delete from tb_book where id =";
					cout << dest1;
					strcat_s(dest1, sql);
					strcat_s(dest1, id);
					cout << dest1;
					if (mysql_query(&mysql, dest1) != 0)
					{
						cerr << "����ɾ����¼�� \n" << mysql_error(&mysql);
					}
					else
						cout << "\t ɾ���ɹ���\n";
				}
			}
			else
				cout << "\t û�з���Ҫɾ������Ϣ! \n";

		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}
void querybook()      //��ѯͼ����Ϣ
{
	char id[10];
	char *sql;
	char dest[100] = { " " };
	
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t���ݿ�����ʧ��" << endl;
	else
	{
		cout << "\t ����������Ҫ��ѯ��ͼ���ţ�";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);
		if (mysql_query(&mysql, dest))
		{
			cout << "\n ��ѯ tb_book ���ݱ�ʧ�ܣ�\n";
		}
		else
		{
			result = mysql_store_result(&mysql);  //��ý����
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t ���ּ�¼��Ϣ���Ƿ���ʾ�� ��y/n)\n";
				cout << ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                        ��ʾͼ����Ϣ                        \n";
					cout << "\t============================================================\n";
					cout << "\tͼ����        ͼ����          ����          ������        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //ȡ��������м�¼
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
				}
			}
			else
			{
				cout << "\t û�з���Ҫ��ѯ����Ϣ��\n";
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	inquire();
}


int main()
{

	int n;              //������� �洢�û�����ı��
	
	mysql_init(&mysql);  //��ʼ��mysql�ṹ
	showmenu();       //��ʾ�˵�
	cin >> n;  //����ѡ���ܵı��
	while (n)
	{
		switch (n)
		{
		case 1: showall();; break;   //������ʾ����ͼ�����ݵĹ���
		case 2: addbook(); break; //���ͼ����Ϣ
		case 3:modifybook(); break;//�޸�ͼ����Ϣ
		case 4:deletebook(); break;//ɾ��ͼ����Ϣ
		case 5:querybook(); break;//��ѯͼ����Ϣ
		case 6:exit(0);//�˳�
		default:break;
		}
		cin >> n;

	}




	mysql_init(&mysql);



	


	
	
	return 0;


}

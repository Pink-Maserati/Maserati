#include<Windows.h>
#include<mysql.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<cstring>
#include<string.h>

#pragma comment (lib,"libmysql.lib")
using namespace std;
MYSQL mysql;  //定义mysql对象
MYSQL_RES *result;//定义结果集变量
MYSQL_ROW row;   //定义行变量
char ch[2];



void showmenu()  //显示所有图书信息
{
	system("cls");// 清屏
	cout << "\n\n\n\n\n";
	cout << "\t||=================================================================||\n";
	cout << "\t||               welcome to lemon books system                     ||\n";
	cout << "\t||=================================================================||\n";
	cout << "\t||\t 1 - 显示所有图书信息                                      ||\n";
	cout << "\t||\t 2 - 添加图书信息                                          ||\n";
	cout << "\t||\t 3 - 修改图书信息                                          ||\n";
	cout << "\t||\t 4 - 删除图书信息                                          ||\n";
	cout << "\t||\t 5 - 查询图书信息                                          ||\n";
	cout << "\t||\t 6 - 退出                                                  ||\n";
	cout << "\t||=================================================================||\n";
	cout << "\n                          ENTER YOUR CHOICE (1 - 6):";
}


void inquire()    //询问用户是否显示主菜单
{
	cout << "\t 显示主菜单？（y/n):";
	cin >> ch;
	if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		showmenu();  //显示主菜单
	}
	else
	{
		exit(0);
	}
}


void showall()//  显示所有图书信息
{
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t数据库连接失败!" << endl;
	else
	{
		//cout << "数据库连接成功" << endl;
		if (mysql_query(&mysql, "select * from tb_book "))
		{
			cout << "查询tb_book数据表失败" << endl;
		}
		else
		{
			//cout << "查询成功" << endl;
			result = mysql_store_result(&mysql);   //获得结果集
			if (mysql_num_rows(result) != NULL)     //结果集不为空，有记录的情况
			{
				cout << "\t============================================================\n";
				cout << "\t                  显示所有图书信息                          \n";
				cout << "\t============================================================\n";
				cout << "\t图书编号        图书名          作者          出版社        \n";
				cout << "\t------------------------------------------------------------\n";
				while (row = mysql_fetch_row(result))    //取出结果集中记录
				{
					cout << "\t" << row[0] << "               "<<row[1]<<"               " << row[2]<<"           " << row[3] << endl;
					//fprintf(stdout, "\t     %s       %s       %s           %s\n", row[0], row[1], row[2], row[3]);
				}
				
				cout << "\t============================================================\n";
			}
			else
			{
				cout << "\n\t没有记录信息 ！\n";
			}
			mysql_free_result(result);//释放结果集

		}
		mysql_close(&mysql);  //释放连接

	}
	inquire();    //询问是否显示主菜单
}


void addbook()
{
	int rowcount;//结果集中的额行数
	char id[10];
	char bookname[50];
	char author[50];
	char bookconcern[100];
	char *sql;
	char dest[230] = { "" };
	//连接数据库
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19",3306, NULL, 0))
		cout << "\n\t数据库连接失败" << endl;
	else
	{
		//数据库连接成功
		cout << "\t=============================================================\n";
		cout << "\t                         添加图书信息                        \n";
		cout << "\t=============================================================\n";
		if (mysql_query(&mysql, "select * from tb_book"))
		{
			cout << "\n\t 查询 tb-book 数据表失败！\n";
		}
		else
		{
			result = mysql_store_result(&mysql);//获得结果集
			rowcount = mysql_num_rows(result);    //获得行数
			row = mysql_fetch_row(result);//获得结果集的行
			//cout << "\t   ID :";
			printf("\t  ID:");
			scanf("%s", id);
		//	cin >> id;    //输入图书编号
			if (mysql_num_rows(result) != NULL)
			{
				//判断输入的编号是否存在
				do
				{
					if (!strcmp(id, row[0]))
					{
						cout << "\t记录存在，按任意键继续！";
						//getch();
			            system("pause");
						mysql_free_result(result);//释放结果集
						mysql_close(&mysql);//释放连接
						return;

					}
				} while (row = mysql_fetch_row(result));
			}
			//不存在相同的编号

			//cout << "\t  图书名:";
			printf("\t 图书名：");
			//cin >> bookname;
			scanf("%s", &bookname);
	
			//printf("\t 作者：");
			////	cout << "\t Author:";// cin >> author;
			//scanf("%s", &author);
			//printf("\t  出版社：");
			////cout << "\t Bookconcern:"; //cin >> bookconcern;
			//scanf("%s", &bookconcern);
			sql = "insert into tb_book (ID,bookname,author,bookconcern) values (";
			strcat(dest,sql); 
			strcat(dest, "'");
			strcat(dest,id); 
			strcat(dest, "', '"); //strcat(dest, " sc");
			strcat(dest,bookname);
			printf("\t 作者：");
		//	cout << "\t Author:";// cin >> author;
			scanf("%s",&author);
			strcat(dest,"', '");
			strcat(dest,author);
		    printf("\t  出版社：");
			//cout << "\t Bookconcern:"; //cin >> bookconcern;
			scanf("%s", &bookconcern);
			strcat(dest, "', '");
			strcat(dest,bookconcern);
			strcat(dest,"')");
			//cout << dest;
			
			printf("%s", dest);
		

			if (mysql_query(&mysql, dest) != 0)
				fprintf(stderr, "不能插入记录！", mysql_error(&mysql));
			//	cerr << "不能插入记录" << mysql_error(&mysql);
			else
				cout << "\t插入成功!" << endl;
			mysql_free_result(result);//释放结果集
		}
		mysql_close(&mysql);//释放连接
	}
	inquire();//询问是否显示主菜单
}


void modifybook()  //修改图书信息
{
	char id[10];
	char *sql;
	char dest[230] = { " " };
	char dest1[230] = { " " };
	char bookname[50];
	char author[50];
	char bookconcern[100];


	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t数据库连接失败" << endl;
	else
	{
		//数据库连接成功
		cout << "\t 请输入您想要修改的图书编号.";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);  //将图书编号追加到sql语句后面
		if (mysql_query(&mysql, dest))
			cout << "\n\t 查询 tb-book 数据表失败！\n";
		else
		{
			result = mysql_store_result(&mysql);  //获得结果集
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t 发现记录信息，是否显示？ （y/n)\n";
				cin>>ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                 **** 显示图书信息****                      \n";
					cout << "\t============================================================\n";
					cout << "\t图书编号        图书名          作者          出版社        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //取出结果集中记录
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
					cout << "\t modify? (y/n)\n";
					cin >> ch;
					if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
					{
						//cout << "\t  图书名：";
						//cin >> bookname;
						printf("\t 图书名：");
						scanf("%s",& bookname);
						sql = "update tb_book set  bookname= '";
						strcat(dest1, sql);
						strcat(dest1, bookname);
						//cout << "\t 作者：";
						printf("\t 作者：");
						//cin >> author;
						scanf("%s", &author);
						strcat(dest1, "', author = '");
						strcat(dest1, author);
						//cout << "\t 出版社：";
						//cin >> bookconcern;	
						printf("\t 出版社：");
						scanf("%s", &bookconcern);
						strcat(dest1, "', bookconcern = '");
						strcat(dest1, bookconcern);
						strcat(dest1, "'where id = ");
						strcat(dest1, id);
						if (mysql_query(&mysql, dest1) != 0)
						{
							cerr << "不能修改记录！\n" << mysql_error(&mysql);
						}
						else
							cout << "\t 修改成功！\n";
					}
				}
			}
			else
				cout << "\t 没有发现要修改的信息！\n";
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
		cout << "\n\t数据库连接失败" << endl;
	else
	{
		cout << "\t 请输入您想要删除的图书编号.\n";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);  //将图书编号追加到sql语句后面

		//查询图书信息是否存在
		if (mysql_query(&mysql, dest))
			cout << "\n\t 查询 tb-book 数据表失败！\n";
		else
		{
			result = mysql_store_result(&mysql);  //获得结果集
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t 发现记录信息，是否显示？ （y/n)\n";
				cin>> ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                 **** 显示图书信息****                      \n";
					cout << "\t============================================================\n";
					cout << "\t图书编号        图书名          作者          出版社        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //取出结果集中记录
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
				}
				cout << "\t 是否删除？ （y/n)\n";
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
						cerr << "不能删除记录！ \n" << mysql_error(&mysql);
					}
					else
						cout << "\t 删除成功！\n";
				}
			}
			else
				cout << "\t 没有发现要删除的信息! \n";

		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}
void querybook()      //查询图书信息
{
	char id[10];
	char *sql;
	char dest[100] = { " " };
	
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "zsy0819..", "db_database19", 3306, NULL, 0))
		cout << "\n\t数据库连接失败" << endl;
	else
	{
		cout << "\t 请输入您想要查询的图书编号：";
		cin >> id;
		sql = "select * from tb_book where id = ";
		strcat_s(dest, sql);
		strcat_s(dest, id);
		if (mysql_query(&mysql, dest))
		{
			cout << "\n 查询 tb_book 数据表失败！\n";
		}
		else
		{
			result = mysql_store_result(&mysql);  //获得结果集
			if (mysql_num_rows(result) != NULL)
			{
				cout << "\t 发现记录信息，是否显示？ （y/n)\n";
				cout << ch;
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				{
					cout << "\t============================================================\n";
					cout << "\t                        显示图书信息                        \n";
					cout << "\t============================================================\n";
					cout << "\t图书编号        图书名          作者          出版社        \n";
					cout << "\t------------------------------------------------------------\n";
					while (row = mysql_fetch_row(result))    //取出结果集中记录
					{
						cout << "\t" << row[0] << "   " << row[1] << "   " << row[2] << "    " << row[3] << endl;
					}
					cout << "\t============================================================\n";
				}
			}
			else
			{
				cout << "\t 没有发现要查询的信息！\n";
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	inquire();
}


int main()
{

	int n;              //定义变量 存储用户输入的编号
	
	mysql_init(&mysql);  //初始化mysql结构
	showmenu();       //显示菜单
	cin >> n;  //输入选择功能的编号
	while (n)
	{
		switch (n)
		{
		case 1: showall();; break;   //调用显示所有图书数据的过程
		case 2: addbook(); break; //添加图书信息
		case 3:modifybook(); break;//修改图书信息
		case 4:deletebook(); break;//删除图书信息
		case 5:querybook(); break;//查询图书信息
		case 6:exit(0);//退出
		default:break;
		}
		cin >> n;

	}




	mysql_init(&mysql);



	


	
	
	return 0;


}

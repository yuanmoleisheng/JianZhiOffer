// Question01.cpp: 定义应用程序的入口点。
// 面试题1：赋值运算符函数

/*
* 如下为类型CMyString的的声明，请为该类型添加赋值运算符函数
* class CMyString {
* public:
*		CMyString(char* pData = nullptr);
*		CMyString(const CMyString& str);
*		~CMyString(void);
* private:
*		char* m_pData;
* };
*/
#include "Question01.h"

using namespace std;

class CMyString {
public:
	CMyString(char* pData = nullptr);//用户指定参数初始化
	CMyString(const CMyString& str);//用一个实例初始化该实例
	CMyString& operator = (const CMyString & rhs);//赋值运算符函数
	~CMyString();//析构函数

	void get()const;//控制台输出字符串内容

private:
	char* m_pData;
};

CMyString::CMyString(char* pData) {
	if (pData == nullptr) {
		m_pData = new char[1];
		m_pData[0] = '\0';
	}
	else {
		int length = strlen(pData);
		m_pData = new char[length + 1];
		strcpy(m_pData, pData);
	}
}

CMyString::CMyString(const CMyString& str) { 
	int length = strlen(str.m_pData);
	m_pData = new char[length + 1];
	strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString() {
	delete[] m_pData;
}

void CMyString::get()const {
	cout << m_pData << endl;
}

CMyString& CMyString::operator=(const CMyString& rhs) {
	if (this != &rhs) {
		/*下面注释的代码是错误的，错误原因在于
		* temp是一个指针，指向了rhs的内存地址
		* 当最后delete temp时，也将rhs的内容删除了
		* 这样是非常危险的
		* 同样也有将m_pData置空后进行如下操作的：
		* m_pData = temp;
		* delete[] temp;
		* 这也是没有考虑好指针的特点与delete的用法，同样十分危险
		*/
		//char* temp = rhs.m_pData;
		//delete[] m_pData;
		//m_pData = nullptr;
		//m_pData = new char[strlen(temp) + 1];
		//strcpy(m_pData, temp);
		//delete[] temp;

		CMyString strtemp(rhs);
		char* temp = strtemp.m_pData;
		strtemp.m_pData = m_pData;
		m_pData = temp;
		/*
		* 上面是考虑了异常安全的做法，其本质是避免了指针直接操作lhs和rhs的状况
		* 首先用rhs初始化一个中间实例strtemp
		* 然后用指针temp指向该实例的data,接着将该实例的内容替换为lhs的内容
		* 最后lhs的内容是temp指向的内容
		* 中间实例的生命周期也结束，调用其析构函数
		*/
	}
	return *this;
}

/*测试用例使用的是书中用例*/
//Test1：把一个CMyString实例复制给另一个实例
void Test1() {
	cout << "Test1 begins:\n";

	char* text = (char*)"Hello world";

	CMyString str1(text);
	CMyString str2;
	str2 = str1;

	cout << "The expected result is: " << text << endl;
	cout << "The actual result is: ";
	str2.get();
	cout << endl;
}

// Test2：把一个CMyString实例赋值给自己
void Test2() {
	cout << "Test2 begins:\n";

	char* text = (char*)"Hello world";

	CMyString str1(text);
	str1 = str1;

	cout << "The expected result is: " << text << endl;
	cout << "The actual result is: ";
	str1.get();
	cout << endl;
}

// 连续赋值
void Test3() {
	cout << "Test3 begins:\n";

	char* text = (char*)"Hello world";

	CMyString str1(text);
	CMyString str2, str3;

	str3 = str2 = str1;

	cout << "The expected result is: " << text << endl;
	cout << "The actual result is: ";
	str2.get();
	cout << endl;

	cout << "The expected result is: " << text << endl;
	cout << "The actual result is: ";
	str3.get();
	cout << endl;
}

int main() {
	Test1();
	Test2();
	Test3();
	return 0;
}

// Question04.cpp: 定义应用程序的入口点。
// 面试题4：二维数组中的查找

/*
* 在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序
* 请完成一个函数，输入这样的一个二维数组和一个整数
* 判断数组中是否含有该整数
*/

#include "Question04.h"

using namespace std;

bool Find(int arr[][4], const int& num) {
	if (num < 0 || num > 100) {
		cout << "The number you entered is out of range!\n";
		return false;
	}
	//int m = 0, n = 0;//m用于获取数组的行数，n获取列数
	//m = sizeof(arr) / sizeof(arr[0]);
	//n = sizeof(arr[0]) / sizeof(arr[0][0]);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (arr[i][j] == num) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	int test[][4] = {	1, 2, 8, 9,
						2, 4, 9, 12,
						4, 7, 10, 13,
						6, 8, 11, 15 };
	cout << "The test 2d-array is like:\n";
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << test[i][j] << '\t';
			if (j + 1 == 4) {
				cout << '\n';
			}
		}
	}
	cout << "Then, you should press a number(0~100):";
	int num = -1;
	cin >> num;
	bool res = false;
	res = Find(test, num);
	if (res) {
		cout << "TRUE" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
	return 0;
}

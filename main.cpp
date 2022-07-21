#include<iostream>
#include <regex>
#include<map>
#include<vector>
#include<typeinfo>

#define debug(x) std::cout << "**" << __FUNCTION__ << "**" << endl << typeid(x).name() << " " << (#x) << " = " << (x) << std::endl;

using namespace std;

int global_variable = 1;

class Grade {
public:
	double math;
	double chinese;
	double english;

	Grade() :
		math(0.0),
		chinese(0.0),
		english(0.0)
	{}
};

class Student {
public:
	Grade m_grade;
	char m_gender;
	int m_no;
	static const int totNum = 55;

	// 构造函数，最好要使用初始化列表（如果是类的话，不用初始化列表会多调用一次default构造函数）
	Student() :
		m_grade(),
		m_gender('M'),
		m_no(0)
	{}

	// 为了提高代码复用性，可以用non-const函数调用const函数
	const double& getMathGrade() const {
		return m_grade.math;
	}
	double& getMathGrade() {
		// 首先用const类调用getGrade函数，然后再消除其const性
		const Student s = static_cast<const Student&>(*this);
		return const_cast<double&>(s.getMathGrade());
	}
};
ostream& operator<<(ostream& os, const Student& rhs) {
	os << "gender : " << rhs.m_gender << endl;
	os << "no : " << rhs.m_no << endl;
	return os;
}


int returnAInt(int& a) {
	a++;
	return 1;
}

int main() {
	vector<int> vec(10);

	// iterator和const
	// const vector<int>::iterator相当于const指针，可以更改指向的值大小，不能更改指向对象（失去了iterator的意义？）
	const vector<int>::iterator iter1 = vec.begin();
	*iter1 = 3;
	// vector<int>::const_iterator有用，所以C++才会有一个专门的名字，指向的值不能改
	vector<int>::const_iterator iter2 = vec.begin();
	++iter2;

	Student student;
	// 使用静态const类变量前需要声明
	// Student::totNum; 
	cout << Student::totNum << endl;

	// aut_ptr
	int a = 3;
	auto_ptr<int> autoPa(&a);		// 源码中对用指针初始化auto_ptr的构造函数声明了explicit，所以必须用括号，不能用等号初始化

	Student stu1, stu2;
	const Student* ps = &stu1;		// 常量指针，是个指针，所以能改变指向地址，但不能改变指向值的大小
	Student* const pss = &stu2;		// 指针常量，本质上是个（地址）常量，所以指向的地址不可改变、必须初始化
	ps = &stu2; pss->m_no = 1;

	int i = 0, i1, i2;
	const int &r = 0;				// 非常量引用的初始值必须是左值
									// 一般来说const指针的声明可以取non-const的地址；反过来则不行

	// 顶层const表示指针是个常量，底层const表示所指对象是个常量
	// 顶层const在拷贝时无影响，底层const拷贝时一般要求能够转换（非常量能转换为常量，即无底层const的可以赋给有底层const的）
	// 底层      顶层
	const int* const pp = &i;

	// constexpr 修饰字面值类型（编译阶段就能算出的值 / 也可以修饰指针，但指针指向的必须是nullptr或者地址固定的变量【而函数体内变量地址一般不固定，所以就有了constexpr函数】）
	// constexpr 声明的指针，不能改变指向的地址，因为将指针置为了 顶层const
	constexpr int ca = 1;
	constexpr int cb = ca * ca + 2;
	constexpr const int* p = &global_variable;		// constexpr保证顶层const，const保证底层const

	constexpr int null = 0, *pnull = null;

	// 类型别名（typedef是C的，using是C++的）
	typedef double myDouble;
	using myDouble = double;
	// 都不是单纯的替换，而是相当于生成了一个新的类型
	typedef char* pstring;
	const pstring pst = 0;		// pstring是个char类型的指针，所以加了const，获得的是一个指针常量（相当于char* const pst;）

	// auto 声明的变量一般会忽略顶层const，如果需要请用const auto；引用auto&不会忽略顶层const

	// decltype推导出变量类型（包括顶层const和引用），但不用表达式的值初始化变量【如果decltype中 变量 加了括号，结果就一定是引用！】
	decltype(returnAInt(i)) sum = 3.4;		// sum == 3，i的值没有改变
	// 如果不想要返回引用，可以传入一个表达式
	// 解引用（传入*p）返回的是引用；赋值返回的也是引用

	// 打印出类型名
	cout << typeid(pss).name() << endl;

	

	system("pause");
	return 0;
}
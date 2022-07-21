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

	// ���캯�������Ҫʹ�ó�ʼ���б��������Ļ������ó�ʼ���б������һ��default���캯����
	Student() :
		m_grade(),
		m_gender('M'),
		m_no(0)
	{}

	// Ϊ����ߴ��븴���ԣ�������non-const��������const����
	const double& getMathGrade() const {
		return m_grade.math;
	}
	double& getMathGrade() {
		// ������const�����getGrade������Ȼ����������const��
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

	// iterator��const
	// const vector<int>::iterator�൱��constָ�룬���Ը���ָ���ֵ��С�����ܸ���ָ�����ʧȥ��iterator�����壿��
	const vector<int>::iterator iter1 = vec.begin();
	*iter1 = 3;
	// vector<int>::const_iterator���ã�����C++�Ż���һ��ר�ŵ����֣�ָ���ֵ���ܸ�
	vector<int>::const_iterator iter2 = vec.begin();
	++iter2;

	Student student;
	// ʹ�þ�̬const�����ǰ��Ҫ����
	// Student::totNum; 
	cout << Student::totNum << endl;

	// aut_ptr
	int a = 3;
	auto_ptr<int> autoPa(&a);		// Դ���ж���ָ���ʼ��auto_ptr�Ĺ��캯��������explicit�����Ա��������ţ������õȺų�ʼ��

	Student stu1, stu2;
	const Student* ps = &stu1;		// ����ָ�룬�Ǹ�ָ�룬�����ܸı�ָ���ַ�������ܸı�ָ��ֵ�Ĵ�С
	Student* const pss = &stu2;		// ָ�볣�����������Ǹ�����ַ������������ָ��ĵ�ַ���ɸı䡢�����ʼ��
	ps = &stu2; pss->m_no = 1;

	int i = 0, i1, i2;
	const int &r = 0;				// �ǳ������õĳ�ʼֵ��������ֵ
									// һ����˵constָ�����������ȡnon-const�ĵ�ַ������������

	// ����const��ʾָ���Ǹ��������ײ�const��ʾ��ָ�����Ǹ�����
	// ����const�ڿ���ʱ��Ӱ�죬�ײ�const����ʱһ��Ҫ���ܹ�ת�����ǳ�����ת��Ϊ���������޵ײ�const�Ŀ��Ը����еײ�const�ģ�
	// �ײ�      ����
	const int* const pp = &i;

	// constexpr ��������ֵ���ͣ�����׶ξ��������ֵ / Ҳ��������ָ�룬��ָ��ָ��ı�����nullptr���ߵ�ַ�̶��ı��������������ڱ�����ַһ�㲻�̶������Ծ�����constexpr��������
	// constexpr ������ָ�룬���ܸı�ָ��ĵ�ַ����Ϊ��ָ����Ϊ�� ����const
	constexpr int ca = 1;
	constexpr int cb = ca * ca + 2;
	constexpr const int* p = &global_variable;		// constexpr��֤����const��const��֤�ײ�const

	constexpr int null = 0, *pnull = null;

	// ���ͱ�����typedef��C�ģ�using��C++�ģ�
	typedef double myDouble;
	using myDouble = double;
	// �����ǵ������滻�������൱��������һ���µ�����
	typedef char* pstring;
	const pstring pst = 0;		// pstring�Ǹ�char���͵�ָ�룬���Լ���const����õ���һ��ָ�볣�����൱��char* const pst;��

	// auto �����ı���һ�����Զ���const�������Ҫ����const auto������auto&������Զ���const

	// decltype�Ƶ����������ͣ���������const�����ã��������ñ��ʽ��ֵ��ʼ�����������decltype�� ���� �������ţ������һ�������ã���
	decltype(returnAInt(i)) sum = 3.4;		// sum == 3��i��ֵû�иı�
	// �������Ҫ�������ã����Դ���һ�����ʽ
	// �����ã�����*p�����ص������ã���ֵ���ص�Ҳ������

	// ��ӡ��������
	cout << typeid(pss).name() << endl;

	

	system("pause");
	return 0;
}
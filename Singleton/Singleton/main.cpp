#include <iostream>
#include <mutex>
using namespace std;

//����ģʽ
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}

private:
	Singleton()
	{}
	//��ֹ����
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);

	static Singleton m_instance;
};

Singleton Singleton::m_instance; // �ڳ������ǰ��ɵ�������ĳ�ʼ��

//����ģʽ
class Singleton2
{
public:
	Singleton2* GetpInstance()
	{
		//���μ�����Ч�ʺͱ�֤�̰߳�ȫ
		if (m_pinstance == nullptr)
		{
			m_mtx.lock();
			if (m_pinstance == nullptr)
			{
				m_pinstance = new Singleton2();
			}
			m_mtx.unlock();
		}
		return m_pinstance;
	}
	class CGarbo//�ڲ�����Ϊ����վ
	{
		~CGarbo()
		{
			if (Singleton2::m_pinstance)
			{
				delete Singleton2::m_pinstance;
			}
		}
	};
	static CGarbo Garbo;//���徲̬��Ա������ṹʱ�Զ�������������
	                    //�ͷŵ�������
private:
	Singleton2(){};
	//��ֹ����
	Singleton2(Singleton2 const&);
	Singleton2& operator=(Singleton2 const&);

	static Singleton2* m_pinstance;//��������ָ��
	static mutex m_mtx;//������
};

Singleton2* Singleton2::m_pinstance = nullptr;
mutex Singleton2::m_mtx;
Singleton2::CGarbo Singleton2::Garbo;

int main()
{
	/*Singleton* p = Singleton::GetInstance();*/

	return 0;
}
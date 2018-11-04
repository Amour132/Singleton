#include <iostream>
#include <mutex>
using namespace std;

//饿汉模式
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
	//防止拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);

	static Singleton m_instance;
};

Singleton Singleton::m_instance; // 在程序入口前完成单例对象的初始化

//懒汉模式
class Singleton2
{
public:
	Singleton2* GetpInstance()
	{
		//两次检查提高效率和保证线程安全
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
	class CGarbo//内部类作为回收站
	{
		~CGarbo()
		{
			if (Singleton2::m_pinstance)
			{
				delete Singleton2::m_pinstance;
			}
		}
	};
	static CGarbo Garbo;//定义静态成员，程序结构时自动调用析构函数
	                    //释放单例对象
private:
	Singleton2(){};
	//防止拷贝
	Singleton2(Singleton2 const&);
	Singleton2& operator=(Singleton2 const&);

	static Singleton2* m_pinstance;//单例对象指针
	static mutex m_mtx;//互斥锁
};

Singleton2* Singleton2::m_pinstance = nullptr;
mutex Singleton2::m_mtx;
Singleton2::CGarbo Singleton2::Garbo;

int main()
{
	/*Singleton* p = Singleton::GetInstance();*/

	return 0;
}
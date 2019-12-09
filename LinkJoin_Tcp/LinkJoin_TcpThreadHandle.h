#pragma once

#include <QThread>
#include <QHash>

// 线程管理类 类似于一个线程池 单例类
// 两种初始化方式 一种是每个线程处理的连接数 一个是一共多少个线程
class LJ_TcpThreadHandle {
public:
	~LJ_TcpThreadHandle();

	static LJ_TcpThreadHandle & GetInstance();	// 单例

	QThread *GetThread();	// 获取一个可用连接的线程
	void	ReduceThread(QThread *thread);	// 减少一次线程连接

private:
	LJ_TcpThreadHandle();
	const unsigned					_kThreadMax = 10;	// 每条线程处理最大连接
	QHash<QThread *, unsigned int>	_thread_list;	// 线程列表
};


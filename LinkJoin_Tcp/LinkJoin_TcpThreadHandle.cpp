#include "LinkJoin_TcpThreadHandle.h"
#include "LinkJoin.h"

LJ_TcpThreadHandle::~LJ_TcpThreadHandle() {
	QThread *thread;
	for (auto it = _thread_list.begin(); it != _thread_list.end(); ++it) {
		thread = it.key();
		thread->exit();
		thread->wait(3000);
		delete thread;
	}
}

LJ_TcpThreadHandle & LJ_TcpThreadHandle::GetInstance() {
	static LJ_TcpThreadHandle th;
	return th;
}

QThread * LJ_TcpThreadHandle::GetThread() {
	for (auto it = _thread_list.begin(); it != _thread_list.end(); ++it) {
		if (it.value() < _kThreadMax) {	// 
			++it.value();
			//LJ_DEBUG(QObject::tr("[%1]线程0x%2连接数: %3").arg(_thread_list.size()).arg(quintptr(it.key()), 4, 16, QLatin1Char('0')).arg(it.value()));
			return it.key();
		}
	}
	QThread *thread = new QThread;
	_thread_list.insert(thread, 1);
	//LJ_DEBUG(QObject::tr("[%1]线程0x%2连接数: %3").arg(_thread_list.size()).arg(quintptr(thread), 4, 16, QLatin1Char('0')).arg(1));
	thread->start();
	return thread;
}

void LJ_TcpThreadHandle::ReduceThread(QThread * thread) {
	--_thread_list[thread];
	//LJ_DEBUG(QObject::tr("[%1]线程0x%2连接数: %3").arg(_thread_list.size()).arg(quintptr(thread), 4, 16, QLatin1Char('0')).arg(_thread_list[thread]));
	if (_thread_list[thread] <= 0) {
		thread->exit();
		thread->wait(3000);
		delete thread;
		_thread_list.remove(thread);
		thread = Q_NULLPTR;
	}
}

LJ_TcpThreadHandle::LJ_TcpThreadHandle() {
}
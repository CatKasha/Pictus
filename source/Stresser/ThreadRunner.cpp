#include "ThreadRunner.h"

#include "orz/orz_math.h"

#include "Logger.h"
#include <algorithm>
#include <random>

struct Runner
{
	void operator()(BasicThread::Ptr p)
	{
		OutputString("Starting thread ...");
		p->Run();
		OutputString("Thread started!");
	}
};

struct Terminator
{
	void operator()(BasicThread::Ptr ptr)
	{
		ptr->Terminate();
	}
};


void ThreadRunner::ThreadMain()
{
	startThreads();

	std::random_device rd;
	std::default_random_engine rand(rd());
	std::uniform_int_distribution<> slp(0, 2000);

	while (!IsTerminating() && !m_error)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(slp(rand)));

		Output("Restarting");
		stopThreads();
		startThreads();
	}
	stopThreads();

	// Avoid undefined behavior due to dependent deconstruction
	m_threads.clear();
}

void ThreadRunner::startThreads()
{
	std::random_shuffle(m_threads.begin(), m_threads.end());
	std::for_each(m_threads.begin(), m_threads.end(), Runner());
	OutputString("All threads have been requested to start.");
}

void ThreadRunner::stopThreads()
{
	OutputString("Asking threads to die ...");

	std::for_each(m_threads.begin(), m_threads.end(), Terminator());
}

ThreadRunner::ThreadRunner():m_error(false)
{

}

ThreadRunner::~ThreadRunner()
{

}

void ThreadRunner::AddThread( BasicThread::Ptr threadToAdd )
{
	m_threads.push_back(threadToAdd);
}

void ThreadRunner::Stop()
{
	m_error = true;
}
#pragma once

template <class T>
class CSingleton
{
private:
	static T * _instance;

protected:
	CSingleton()			{};
	virtual ~CSingleton()	{};

public:
	static T * GetInstance()
	{
		if ( NULL == _instance )
		{
			_instance = new T;
		}

		return ( static_cast<T*>( _instance ) );
	}

	static void DestoryInstance()
	{
		if ( NULL != _instance )
		{
			delete _instance;
			_instance = NULL;
		}
	}
};

template <class T>
T * CSingleton<T>::_instance = NULL;

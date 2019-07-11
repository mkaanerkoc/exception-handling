#include <iostream>
#include <vector>


using namespace std;


/* bulgular, c++11 ile derlenince try blogu bittikten sonra calistirilan scope temizlemede firlatilan exception larin caller daki catch de yakalanmiyorlar. terminate oluyor. ama c++11 oncesi nde sorun olmuyor callerdaki catch tarafindan yakalaniyolar */

class LockerAction{
	public:
		LockerAction(int id)
		: _id(id)		
		{
		
		}
		virtual void lock() = 0;
		virtual void unlock() = 0;
	protected:
		int _id;

};

class LraAction : public LockerAction{
	public:
		LraAction()
		:LockerAction(5)
		{
		}
		void lock()
		{
			cout<<"LraAction Lock"<<endl;
		}
		void unlock()
		{
			if( _id == 5 )
			{
				throw _id;
			}
			cout<<"LraAction Unlock"<<endl;
		}
};

class KjdrmiAction : public LockerAction{
	public:
		KjdrmiAction()
		:LockerAction(5)
		{
		}
		void lock()
		{
			cout<<"KjdrmiAction Lock"<<endl;
		}
		void unlock()
		{
			if( _id == 5 )
			{
				throw _id;
			}
			cout<<"KjdrmiAction Unlock"<<endl;
		}
};

class LockerExecutor{
	public:
		LockerExecutor(LockerAction& action, vector<int>& errors)
		: _action(action),_errors(errors)
		{
			_action.lock();
		}
	
	protected:
		LockerAction& _action;
		vector<int>& _errors;
};

class LockerExecutorAlwaysThrows : public LockerExecutor{
	public:
		LockerExecutorAlwaysThrows(LockerAction& action, vector<int>& errors)
		: LockerExecutor(action,errors)
		{
			
		}
		virtual ~LockerExecutor() = 0;
		virtual ~LockerExecutorAlwaysThrows()
		{
			cout<<"LockerExecutorAlwaysThrows THROWS"<<endl;
			_action.unlock();
		}
};

/* this class makes any LockerAction object no-throw safety if there is any uncaught exception!*/
class LockerExecutorSafelyThrows : public LockerExecutor{
	public:
		LockerExecutorSafelyThrows(LockerAction& action, vector<int>& errors)
		: LockerExecutor(action,errors)
		{

		}
		virtual ~LockerExecutorSafelyThrows()
		{
			if( 0 != uncaught_exception())
			{
				cout<<"Uncaught Exception EXIST!!! SafelyThrows wont throw anything"<<endl;
				try{
					_action.unlock();			
				}
				catch(int v)
				{
					cout<<"Exception Catch on executor! ID:"<<v<<endl;
					_errors.push_back(v);
				}			
			}
			else			
			{
				cout<<"Uncaught Exception non-exist SafelyThrows will THROW"<<endl;
				// burada uncaught exception olmadigi icin yukari salalim gitsin...
				// bu bize ne saglicak, elimizi guclendirdi. onceden ortada herhangi bi exception
				// olmasa bile bizde olusan exception u yukari gondermiyorduk. Bilgi kaybina yol acabilirdi
				// ama simdi eger ortada bi exception yoksa bam diye yukari gonderiyoruz. 
				// ama bu durumda yukari gonderdigimiz durum direkt throw atip catch ' e giriyor.
				// bunu istemeyebiliriz her zaman. onun yerine bize verilen bi alana hata oldugu bilgisini 
				// yazip da birakabiliriz. o yuzden SafelyThrows kullanilamaz. cunku her turlu exception 					// aticak eger ortam musait ise. 
				_action.unlock();
			}
		}
};

class LockerExecutorNoThrows : public LockerExecutor{
	public:
		LockerExecutorNoThrows(LockerAction& action, vector<int>& errors)
		: LockerExecutor(action,errors)
		{
		}
		virtual ~LockerExecutorNoThrows()
		{
			if( 0 != uncaught_exception())
			{
				cout<<"Uncaught Exception EXIST!!! - NoThrows"<<endl;
			}
			{
				cout<<"Uncaught Exception non-exist - NoThrows"<<endl;
			}
			try{
				_action.unlock();			
			}
			catch(int v)
			{
				cout<<"Exception Catch on LockerExecutorNoThrows ID:"<<v<<endl;
				_errors.push_back(v);
			}			
		}
};



/* ilk once throw 100 atiliyor, burada uncaught exception sayısı bir artırılıyor. stack unwinding baslıyor.
exctin destructoru cagiralacak burada, exctin dtorunda exception var mı yok mu die bakıyoruz
var. ondan sonra Action'un unlock methodunu cagiriyoruz. burada stack unwinding basliyor. ondan sonra exception catch ine giriyor. burada cozuluyor bu dert. cozulmeseydi eger yukari cikacakti. ozaman isler karisirdi


*/
int main(void)
{
	vector<int> errors;
	LraAction act;
	KjdrmiAction kact;
	try
	{
		LockerExecutorSafelyThrows exc(act,errors);
		LockerExecutorSafelyThrows exct(kact,errors);
		//throw 100;
		//LockerExecutorAlwaysThrows(act,errors);	
	}
	catch(int v)
	{
		cout<<"Main Exception Caught ! ID : "<<v<<endl;
	}
	vector<int>::iterator ptr; 
	for (ptr = errors.begin(); ptr < errors.end(); ptr++)
	{
		cout << *ptr << endl;
	} 
         
		
	return 0;
}

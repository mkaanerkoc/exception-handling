#include <iostream>

using namespace std;

class Car;
class Driver;

void program_1(void);
void program_2(void);
void program_3(void);
void program_4(void);
void program_5(void);
void program_6(void);
void program_7(void);

class Car{
	public:
		Car()
		{
			_v = -1;
			cout<<"Car"<<_v<<" Initalized"<<endl;
		}
		Car(int v)
		:_v(v)		
		{
			cout<<"Car"<<_v<<" Initalized"<<endl;
		}
		~Car()
		{
			cout<<"Car"<<_v<<" Destroy start"<<endl;
			if( _v == 99 )
			{
				/*try{
					throw _v;
				}catch(int v)
				{
					cout<<"Exception catch on Car"<<v<<" destructor"<<endl;
				}	*/	
				throw _v;	
			}
			cout<<"Car"<<_v<<" Destroy end"<<endl;
		}
		void drive()
		{
			cout<<"drive"<<_v<<" start"<<endl;
			if( _v != 10 && _v != 15 )
				throw _v;			
			cout<<"drive"<<_v<<" end"<<endl;			
		}
	private:
 		int _v;
};



class Driver{
	public:
		Driver(Car &car,int id)
		:_car(car),_id(id)		
		{
			cout<<"Driver"<<_id<<" Initialized"<<endl;
		}
		~Driver()
		{
			cout<<"Driver"<<_id<<" Destroyed"<<endl;
		}
	private:
		Car& _car;
		Car _car1;
		int _id;
};

class DummyClass{
	public:		
		DummyClass()	
		{
			cout<<"DummyClass Initialized"<<endl;
		}
		~DummyClass()
		{
			cout<<"DummyClass Destroyed"<<endl;
		}
};

int main(void)
{
	//program_2();	
	try{
		program_7();	
	}	
	catch(int v)
	{
		cout<<"Main Catch : "<<v<<endl;
	}
	return 0;
}

void program_1(void)
{
	try{
		Car c(99);
		Driver d(c,15);		
		c.drive();
		cout<<"Drive done succesfully"<<endl;
	}
	catch(int a)
	{
		cout<<"Exception"<<a<<" has catch"<<endl;
	}	
}

void program_2(void)
{
	program_3();
}

void program_3(void)
{
	program_4();
	cout<<"burada cakilacak"<<endl;	
	throw 30;
}

void program_4(void)
{
	throw 20;
}

void program_5(void)
{
	{
		Car c(99);
	}
}

void program_6(void)
{
	try{
		throw 20;
	}
	catch(int v)
	{
		cout<<"Exception"<<v<<" has catch on program_6"<<endl;
		throw v;
	}
}

void program_7(void)
{
	{	
		DummyClass dc;
		cout<<"throw happened"<<endl;
		throw 20;
	}
}


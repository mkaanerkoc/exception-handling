#include <iostream>

using namespace std;

// write macro function to provide compile-time polymorphism in C
// develop ISummable interface to provide run-time generyc type methods/class, bu cok munkun olmayabilir
// + isleminin sonucu ne olacak amk ??


// bu methodda da return value yu generic yapamadik
// bunlar sadece return type i belli olanlar da oluyo herhalde
// Kural da bu zaten, generic programming de return turu ile input turu ayni olarak kabul edilir
// aksinin olabilecegi durumlar belirtilmelidir. bizim plus_op_generyc de yaptigimiz gibi

// python da bu durum su sekilde yapilmis
/*
	def __add__(self, o): 
        return self.a + o.a  

	return degeri de typesiz amk
*/

#define SUM(a,b)         (a+b)


class ISummable{
	public:
	private:
};


static int plus_op(int a,int b)
{
	return a+b;
}

template <typename In,typename Out>
static Out plus_op_generyc(In a, In b)
{
	return a+b;
}

/* bu durumda pythondaki gibi + operatorune uygunlugu base class gibi tanimlayamiyoruz
summable die bi interface yok yani */
template <class In, class Out> 
class Calculator{
	public:
		Out Plus(In a, In b)
		{
			cout<<"Calculator Result:"<<(a+b)<<endl;
			return a+b;
		}
};

class Score{
public:
	Score(int v)
	:value(v)
	{}
	int operator+(const Score& b)
	{
		return this->value + b.value;
	}
	const int value; 
};



int main(void)
{
	int a = 5;
	int b = 7;
	Score s1(50);
	Score s2(53);
	cout<<a<<"+"<<b<<"="<<plus_op(a,b)<<endl;
	cout<<a<<"+"<<b<<"="<<plus_op_generyc<int,int>(a,b)<<endl;
	cout<<"s1+s2="<<plus_op_generyc<Score,int>(s1,s2)<<endl;
	cout<<"SUM(a,b):"<<SUM(a,b)<<endl;	
	cout<<"SUM(s1,s2):"<<SUM(s1,s2)<<endl;	
	Calculator<int,int> c1;
	Calculator<Score,int> c2;
	c1.Plus(a,b);
	c2.Plus(s1,s2);
	return 0;
}

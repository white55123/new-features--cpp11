#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
class Container
{
public:
   void print(const T& t)const
   {
       auto it = t.begin();
       for (; it != t.end(); ++it)
       {
           cout << it->first << ", " << it->second << endl;
       }
   }
};


template <typename T>
using MMap = map<int, T>;

int main(int agrc, char* argv[])
{
		MMap<string> mm3;
	    mm3.insert(std::make_pair(1, "hello"));
	    mm3.insert(std::make_pair(2, "world"));
	    Container<MMap<string>> a;
	    a.print(mm3);
}
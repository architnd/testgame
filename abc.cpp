#include <iostream>
using namespace std;
#if 1
class base
{
   int j;

protected:
   int i;

public:
   void set(int a, int b) { i = a, j = b; }
   void show() { cout << i << " " << j << "\n"; }
};
class derived : public base
{
   int k;

public:
   derived(int x)
   {
      k = x;
   }
   void showk() { cout << k << " "
                       << i << "\n"; }
};
int main()
{
   derived ob(3);
   ob.set(1, 2);
   ob.show();
   ob.showk();
}
#endif
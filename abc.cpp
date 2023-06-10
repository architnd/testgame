#include <iostream>
#include <list>
using namespace std;
#if 0
class base
{
   int j;

protected:
   int i;

public:
   base(){
      i = 0;
      j = 0;
      cout << "I am constructor \n";
   }
   ~base(){
      cout << "I am destructor \n";
   }
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
   derived*ob = new derived(3);
//   derived ob(3);
   ob->set(1, 2);
   ob->show();
   ob->showk();
   delete ob;
   derived ob2(4);
   ob2.showk();
}
#endif
#if 0
int main() {

  int year;
  cout << "Enter a year: ";
  cin >> year;

  // leap year if perfectly divisible by 400
  if (year % 400 == 0) {
    cout << year << " is a leap year.";
  }
  // not a leap year if divisible by 100
  // but not divisible by 400
  else if (year % 100 == 0) {
    cout << year << " is not a leap year.";
  }
  // leap year if not divisible by 100
  // but divisible by 4
  else if (year % 4 == 0) {
    cout << year << " is a leap year.";
  }
  // all other years are not leap years
  else {
    cout << year << " is not a leap year.";
  }

  return 0;
}

int main() {

  int i, n;
  bool is_prime = true;

  cout << "Enter a positive integer: ";
  cin >> n;

  // 0 and 1 are not prime numbers
  if (n == 0 || n == 1) {
    is_prime = false;
  }

  // loop to check if n is prime
  for (i = 2; i <= n/2; ++i) {
    if (n % i == 0) {
      is_prime = false;
      break;
    }
  }

  if (is_prime)
    cout << n << " is a prime number";
  else
    cout << n << " is not a prime number";

  return 0;
};
#endif
#if 1
class Userdata
{
   string username_;
   int age_;

public:
   Userdata(string username, int age)
   {
      username_ = username;
      age_ = age;
   }
   ~Userdata()
   {
   }
   void PrintData()
   {
      cout << username_ << "\n";
      cout << age_ << "\n";
   }
   string GetUsername()
   {
      return username_;
   }
   int GetAge()
   {
      return age_;
   }
};

std::list<Userdata *> Userlist;

int main()
{
   {
      int Array[] = {12, 14, 34, 24};
      for (int i = 0; i < sizeof(Array)/sizeof(int); i++)
      {
         cout << Array[i] << "\n";
      }
      std::list<int> Mylist = {12, 14, 34, 24};
      for (auto it = Mylist.begin(); it != Mylist.end(); it++)
      {
         cout << *it << "\n";
      }
   }
   int i;
   while (1)
   {
      cout << "1. Add User\n";
      cout << "2. Delete User\n";
      cout << "3.Edit User Details\n";
      cout << "4. List Users\n";
      cout << "5. Exit\n";
      cin >> i;
      if ((i < 1) || (i > 4))
      {
         cout << "invalid option entered\n";
      }
      else if (i == 5)
      {
         break;
      }
      else if (i == 1)
      {
         string username;
         int age;
         cout << "Enter Username\n";
         cin >> username;
         cout << "Enter Age\n";
         cin >> age;

         Userdata *ud = new Userdata(username, age);
         Userlist.push_back(ud);
      }
      else if (i == 2)
      {
         string username;
         cout << "Enter the Username to delete: \n";
         cin >> username;
         auto it = Userlist.begin();
         while (it != Userlist.end())
         {
            if ((*it)->GetUsername().compare(username) == 0)
            {
               delete *it;
               it = Userlist.erase(it);
            }
            else
            {
               it++;
            }
         }
      }
      else if (i == 4)
      {
         for (auto it : Userlist)
         {
            it->PrintData();
         }
      }
      else if (i == 3)
      {
         int age;
         int new_age;
         cout << "Enter the Age to Edit: \n";
         cin >> age;
         cout << "Enter the New Age: \n";
         cin >> new_age;
         auto it = Userlist.begin();
         while (it != Userlist.end())
         {
            if ((*it)->GetAge() == age)
            {
               (*it) = new_age;
            }
         }
      }
   }
}
#endif
#if 0
int main()
{
   int i, n;
   bool is_prime = true;
   cout << "Enter a Number: \n";
   cin >> n;
   if(n == 0 || n == 1)
   {
      is_prime = false;
   }
   for(i = 2; i <= n/2; i++)
   {
      if (n % i == 0)
      {
         is_prime = false;
         break;
      }
   }
   if(is_prime == true)
   {
      cout << n << " is a prime number\n";
   }
   else
   {
      cout << n << " is not a prime number\n";
   }
   return 0;
}
#endif

#include<iostream>
#include<conio.h>
#include<vector>
#include<cstring>
#include<fstream>
using namespace std;
int Add();
void car();
 void totalveh();
 void display();
 void  totalamount();
 void deleteVehicle();
 void read_file();

class date
{
public :
    int dd;
    int mm;
    int yy;
};
class time
{
public :
    int hh;
    int mm;
    int ss;
};
class vehicle
{
private :
    int tn;
    char vn[30];//vehicle number
    time t; //arrival time
    date d;//date
    string on; //owner name
   char mob_no[10];//mobile no
public :
    void set_car();
    void set_bike();
    void show_data();
    int token();
    void save_car();
    void save_bike();


};
vector <vehicle> c1;
vector <vehicle> b1;

void vehicle :: set_car()
{
    int i;
      cout<<endl<<"Enter Token No:-";
      cin>>tn;
      cout<<endl<<"Enter owner name :-";
   cin>>on;
     cout<<endl<<"Enter vehicle number :-";
   cin>>vn;
     cout<<endl<<"Enter Arrival time(hh/mm/ss) :-";
   cin>>t.hh>>t.mm>>t.ss;
     cout<<endl<<"Enter Date(DD/MM/YY) :-";
   cin>>d.dd>>d.mm>>d.yy;
   cout<<endl<<"Enter Mobile_No:-";
cin>>mob_no;





}
void read_file()
{
    vehicle temp;
    ifstream fin;
    fin.open("file1.dat",ios ::in);
    if(!fin)
    {
        cout<<endl<<"not file found";
    }
    else
    {
        fin.read((char*)&temp,sizeof(temp));

        while(!fin.eof())
        {
            temp.show_data();

            fin.read((char *)&temp,sizeof(temp));
        }
        fin.close();
    }
}
  void vehicle:: save_car()
  {
   ofstream fout;
   fout.open("file1.dat",ios ::app);
   fout.write((char *)this,sizeof(*this));
   fout.close();
  }
   void vehicle:: save_bike()
  {
   ofstream fout;
   fout.open("file2.dat",ios ::app );
   fout.write((char *)this,sizeof(*this));
   fout.close();
  }
void vehicle :: show_data()
{
       cout<<endl<<"owner name :-";
   cout<<on;
     cout<<endl<<"vehicle number :-";
   cout<<vn;
     cout<<endl<<"Enter Arrival time(hh/mm/ss) :-";
   cout<<t.hh<<":"<<t.mm<<":"<<t.ss;
     cout<<endl<<"Enter Date(DD/MM/YY) :-";
   cout<<d.dd<<"/"<<d.mm<<"/"<<d.yy;
   cout<<endl<<"Mobile_No:-";
   cout<<mob_no;
   cout<<endl<<"token no :-";
   cout<<tn<<endl;

}


int vehicle :: token()
{
    return tn;
}
void  vehicle ::set_bike()
{
    int i;
       cout<<endl<<"Enter Token NO :-";
cin>>tn;
      cout<<endl<<"Enter owner name :-";
   cin>>on;
     cout<<endl<<"Enter vehicle number :-";
   cin>>vn;
     cout<<endl<<"Enter Arrival time(hh/mm/ss) :-";
   cin>>t.hh>>t.mm>>t.ss;
     cout<<endl<<"Enter Date(DD/MM/YY) :-";
   cin>>d.dd>>d.mm>>d.yy;
   cout<<endl<<"Enter Mobile_No:-";
cin>>mob_no;


}



int main()
  {
    int choice;
    char ans;
    system ( "cls" ) ;

    read_file();

  while(1)
  {
     system ( "cls" ) ;
    cout<<"********************************************************************"<<endl;
    cout<<"                 VEHICLE PARKING RESERVATION SYSTEM                 "<<endl;
    cout<<"1. Arrival of a vehicle"<<endl;
    cout<<"2. Total number of vehicles parked"<<endl;
    cout<<"3. Departure of vehicle"<<endl;
    cout<<"4. Total Amount collected "<<endl;
    cout<<"5. Display "<<endl;
    cout<<"6. Exit"<<endl;
    cout<<"********************************************************************"<<endl;
    cout<<"Enter your Choice : ";
    cin>>choice;

         switch(choice)
         {
             case 1: system ( "cls" ) ;
                     cout<<"Add : "<<endl;
                    Add();

                     break;

             case 2: system ( "cls" ) ;
                     totalveh();
                     break;

             case 3: system ( "cls" ) ;
                     cout<<"Departure : "<<endl;
                     deleteVehicle();
                     break;

             case 4: system ( "cls" ) ;
                    totalamount();
                     break;

             case 5: system ( "cls" ) ;
                    display();
                     break;
             case 6:
                 for(auto c7=c1.begin();c7 !=c1.end();c7++)
                    c7->save_car();
                  for(auto b7=b1.begin();b7 !=b1.end();b7++)
                    b7->save_car();
                 exit(0);
         }



  };

  return 0;
  }





  int Add()
  {
     while(1)
     {
          int choice;
      char c;
      cout<<"Enter vehicle Type :(1-car/2-bike)";
      cin>>choice;
      if(choice==1)
      {
          vehicle *obj=new vehicle;

          obj->set_car();

          c1.push_back(*obj);
      }
     else if(choice==2)
      {
       vehicle *obj1=new vehicle;
       obj1->set_bike();
        b1.push_back(*obj1);
      }
      cout<<endl<<"Do you want to continue(y/n)";
      cin>>c;
      if(c=='y')
      {
          system("cls");
          continue;
      }
      else if(c=='n')
      {
          break;
      }
     }

return 0;

  }


   void totalveh()
   {
       cout<<"Total no of car parked :-"<<c1.size()<<endl;
        cout<<"Total no of bike parked :-"<<b1.size();
        getch();
   }
void display()
{
    int i=0;
    cout<<"*****************Car Detail*****************";
    for(auto c=c1.begin();c !=c1.end();c++)
    {
        i++;
        cout<<endl<<i<<". ";
        c->show_data();


    }
      cout<<"*****************Bike Detail*****************";
    for(auto b=b1.begin();b !=b1.end();b++)
    {
        i++;
        cout<<endl<<i<<". ";
        b->show_data();


    }
    getch();
}
 void  totalamount()
 {
     int car_coll,bike_coll,total;
     car_coll=c1.size();
     car_coll=(car_coll)*20;
      bike_coll=b1.size();
     bike_coll=(bike_coll)*10;

     total=car_coll+bike_coll;
      cout<<endl<<"collection from Car="<<car_coll;
       cout<<endl<<"collection from bike="<<bike_coll;
     cout<<endl<<"Total today collection is : "<<total;
getch();
 }
 void deleteVehicle()
 {
   int choice,m,x,z=9;
   cout<<endl<<"Enter Token No :-";
   cin>>m;
   cout<<endl<<"Enter choice(1-Car/2-Bike) :-";
   cin>>choice;
   if(choice==1)
   {
       for(auto c6=c1.begin();c6 !=c1.end();c6++)
       {

           x=c6->token();
           if(x==m)
           {
               c1.erase(c6);
               z=-1;
               break;
           }
       }
       if(z==-1)
        cout<<endl<<"vehicle deleted successfully..";
       else
        cout<<endl<<"vehicle not found..";
   }
   if(choice==2)
   {
       for(auto b6=b1.begin();b6 !=b1.end();b6++)
       {

           x=b6->token();
           if(x==m)
           {
               b1.erase(b6);
               z=-2;
               break;
           }
       }
       if(z==-2)
        cout<<endl<<"vehicle deleted successfully..";
       else
        cout<<endl<<"vehicle not found..";
   }
getch();
 }

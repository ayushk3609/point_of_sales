#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<stdlib.h>
using namespace std;
class products
{
private:
    char pid[50];
    char pname[50];
    float price;
friend void searchproduct();
friend void newbill();
friend void delte();
friend void edit();
public:
    void accept()
    {
        cout<<endl<<"Enter product_ID : ";
        cin>>pid;
        cout<<endl<<"Enter product name : ";
        cin>>pname;
        cout<<endl<<"Enter price : ";
        cin>>price;
    }
    void display()
    {
        cout<<endl<<pid<<setw(20)<<pname<<setw(20)<<price;
    }


};
products obj;
 void addproduct()
    {
        fstream wr;
        wr.open("c:\\programs\\myproducts.txt",ios::app);
        obj.accept();
        wr.write((char*)&obj,sizeof(obj));
        cout<<endl<<"object written succesfully ........";
    }
void readproducts()
{
    fstream rd;
    rd.open("c:\\programs\\myproducts.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(5)<<"BAR CODE"<<setw(25)<<"Product Name"<<setw(22)<<"Price"<<endl;
    cout<<"======================================================================"<<endl;
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
    }
    cout<<endl<<"======================================================================"<<endl;
}
void searchproduct()
{
    fstream rd;
    rd.open("c:\\programs\\myproducts.txt",ios::in);
    char nm[50];
    cout<<endl<<"Enter Product_ID you want to search : ";
    cin>>nm;
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(strcmp(nm,obj.pid)==0)
        {
            obj.display();
        }
    }
}

class bill
{
public:
    int billno;
    char date[20];
    char itemcode[50];
    char itemname[50];
    float price;
    int qty;
    float total;
    void display()
    {
        cout<<endl<<itemcode<<setw(15)<<itemname<<setw(15)<<qty<<setw(15)<<price<<setw(10)<<total;
    }
};
bill obj2;
void newbill()
{
    int bid;
    char d[50];
    cout<<endl<<"Enter bill no. : ";
    cin>>bid;
    cout<<endl<<"Enter date(dd/mm/yy) : ";
    cin>>d;
    int e=0;
    while(e!=1)
    {
        char barcode[50];
        cout<<endl<<"Enter Product barcode : ";
        cin>>barcode;
        if (strcasecmp(barcode,"0")==0)
        {
            e=1;
            break;
        }
        else
        {
            fstream rd;
            rd.open("c:\\programs\\myproducts.txt",ios::in);
            rd.seekg(0,ios::end);
            int n=rd.tellg()/sizeof(obj);
            rd.seekg(0,ios::beg);
            for(int i=1;i<=n;i++)
            {
                rd.read((char*)&obj,sizeof(obj));
                if(strcmp(barcode,obj.pid)==0)
            {
                    obj2.billno=bid;
                    strcpy(obj2.date,d);
                    strcpy(obj2.itemcode,obj.pid);
                    strcpy(obj2.itemname,obj.pname);
                    obj2.price=obj.price;
                    obj2.qty=1;
                    obj2.total=obj2.price*obj2.qty;
                    fstream w;
                    w.open("c:\\programs\\posbill.txt",ios::app);
                    w.write((char*)&obj2,sizeof(obj2));
                    w.close();
            }
        }
        }
    }
fstream rd2;
rd2.open("c:\\programs\\posbill.txt");
rd2.seekg(0,ios::end);
int n2=rd2.tellg()/sizeof(obj2);
rd2.seekg(0,ios::beg);
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
cout<<endl<<"\t\t\tWELCOME TO MY SUPER STORE";
cout<<endl<<endl<<endl;
float mybill=0;
for(int j=1;j<=n2;j++)
{
    rd2.read((char*)&obj2,sizeof(obj2));
    if(obj2.billno==bid && strcmp(obj2.date,d)==0)
    {
        obj2.display();
        mybill = mybill+obj2.total;
    }
}
cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
cout<<endl<<"please pay : "<<mybill;
cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}
void dupbill()
{
    char da[50];
    int b;
    cout<<endl<<"Enter bill no. : ";
    cin>>b;
    bill obj3;
    fstream rd;
    rd.open("c:\\programs\\posbill.txt",ios::in);
     rd.seekg(0,ios::end);
     int n=rd.tellg()/sizeof(obj3);
     rd.seekg(0,ios::beg);
     cout<<"\n\n\===========================##WELCOME TO MY SUPERSTORE##=========================";
     float mybill=0;
     cout<<endl<<endl<<setw(50)<<"##DUPLICATE BILL##"<<setw(50);
        for(int i=1;i<=n;i++)
        {
            rd.read((char*)&obj3,sizeof(obj3));
            if(obj3.billno==b)
            {
                obj3.display();
                mybill=mybill+obj3.total;
            }

        }
        cout<<endl<<"\n\n==========================================================================";
        cout<<"\nPlease Pay -- Rs. "<<mybill<<endl;
        cout<<"====================================================================================";
}
void delte()
{
    fstream rd,wr;
    rd.open("c:\\programs\\myproducts.txt",ios::in);
    wr.open("c:\\programs\\copyproducts.txt",ios::out);

    char pid[50];
    cout<<endl<<"Enter product bar code : ";
    cin>>pid;
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    int f=0;
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(strcmp(obj.pid,pid)==0)
        {
            f=1;
            cout<<endl<<"Object removed........";
        }
        else
        {
            wr.write((char*)&obj,sizeof(obj));
        }
    }
    if(f==0)
    {
        cout<<endl<<"Product not found........";
    }
    rd.close();
    wr.close();
    remove("c:\\programs\\myproducts.txt");
    rename("c:\\programs\\copyproducts.txt","c:\\programs\\myproducts.txt");

}
void edit()
{
    fstream rd,wr;
    rd.open("c:\\programs\\myproducts.txt",ios::in);
    wr.open("c:\\programs\\temp.txt",ios::out);

    char pid[50];
    cout<<endl<<"Enter product bar code to edit : ";
    cin>>pid;
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(strcmp(obj.pid,pid)==0)
        {
            obj.accept();
            wr.write((char*)&obj,sizeof(obj));
        }
        else
        {
            wr.write((char*)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();
    remove("c:\\programs\\myproducts.txt");
    rename("c:\\programs\\temp.txt","c:\\programs\\myproducts.txt");


    cout<<endl<<"Product EDITTED successfully.........";
}

float totcal(int bno,char da[50])
{
    float to=0;
    bill ob;
    fstream rd2;
    rd2.open("c:\\programs\\posbill.txt",ios::in);
    rd2.seekg(0,ios::end);
    int n=rd2.tellg()/sizeof(ob);
    rd2.seekg(0,ios::beg);
    for (int i=1;i<=n;i++)
    {
        rd2.read((char*)&ob,sizeof(ob));
        if(strcmp(ob.date,da)==0 && ob.billno==bno)
        {
            to=to+ob.total;
        }
    }
    rd2.close();
    return to;
}
void sales()
{
    char dat[50];
    int billno;
    int temp=0;
    float to=0;
    cout<<endl<<"ENTER DATE to view SALES (dd/mm/yy) : ";
    cin>>dat;
    cout<<endl<<endl<<"_______________________________________________________________________________";
    cout<<endl<<"SALES for date "<<dat<<" are : ";
    cout<<endl<<endl<<setw(15)<<"BILL NO."<<setw(20)<<"TOTAL BILL";
    fstream rd;
    float total=0;
    rd.open("c:\\programs\\posbill.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj2);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj2,sizeof(obj2));
        if(strcmp(obj2.date,dat)==0)
        {
            total=total+obj2.price;
            billno=obj2.billno;
            if(billno!=temp)
            {
                int tot=0;
                temp=billno;
                tot=totcal(billno,dat);
                cout<<endl<<endl<<endl<<setw(15)<<billno<<setw(20)<<tot;
            }
        }
    }
    cout<<endl<<"--------------------------------------------------------------------------------";
    cout<<endl<<"TOTAL SALE : "<<total;
    cout<<endl<<"--------------------------------------------------------------------------------";
}
main()
{
    int e=0;
    while(e!=1)
    {
        cout<<endl<<"=================================# M E N U #==================================";
        cout<<endl<<"1. TO ADD products.";
        cout<<endl<<"2. TO VIEW products.";
        cout<<endl<<"3. TO SEARCH product.";
        cout<<endl<<"4. TO EDIT product.";
        cout<<endl<<"5. TO DELETE product.";
        cout<<endl<<"6. TO create NEW BILL.";
        cout<<endl<<"7. TO view DUPLICATE BILL.";
        cout<<endl<<"8. TO view SALES.";
        cout<<endl<<"9. TO EXIT.";
        cout<<endl<<"___________________________________________________________________________________";
        cout<<endl<<"ENTER your CHOICE : ";
        cin>>e;

        switch(e)
        {
            case 1:addproduct();
                    break;
            case 2:readproducts();
                    break;
            case 3:searchproduct();
                    break;
            case 4:edit();
                    break;
            case 5:delte();
                    break;
            case 6:newbill();
                    break;
            case 7:dupbill();
                    break;
            case 8:sales();
                    break;
            case 9:cout<<endl<<"EXITTING........";
                    exit(0);


        }
        cout<<endl<<"PRESS 0 to continue to MAIN MENU or PRESS 1 to Exit : ";
        cin>>e;
        system("cls");


    }


}



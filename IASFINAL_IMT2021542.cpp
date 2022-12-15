#include<iostream>
#include<bits/stdc++.h>
#define int long long
#define pb(x) push_back(x)
#define rep(i,a,b) for(int i=a;i<b;i++)
using namespace std;
string memory[1000]; //1000 MEMORY LOCATIONS
//variables declared
int PC=0;
string AC="0";
string MBR="0";
string MAR="";
string IBR="";
string IR="";
int signbin(string b) //this function takes care of negative number: 2's compliment is passed and returns appropriate number
{   
    int l=b.length()-1;
    int res=-pow(2,l);
    int n=0;
    for( int i=l;i>=1;i--)
    {
        int ch=b[i];
        res=res+(ch-48)*pow(2,n);
        n++;
    }
    return res;    
}
string assembler(string str) //this is a part of assembler which returns the opcode for instructions
{
    if(str=="LOAD MQ")
        return "00001010";
    else if(str =="LOAD MQ,M(X)")
        return "00001001";
    else if(str=="STOR M(X)")
        return "00100001";
    else if(str=="LOAD M(X)")
        return "00000001";
    else if(str=="LOAD -M(X)")
        return "00000010";
    else if(str=="LOAD |M(X)|")
        return "00000011";
    else if(str=="LOAD -|M(X)|")
        return "00000100";
    else if(str=="JUMP M(X,0:19)")
        return "00001101";
    else if(str=="JUMP M(X,20:39)")
        return "00001110";
    else if(str=="JUMP+ M(X,0:19)")
        return "00001111";
    else if(str=="JUMP+ M(X,20:39)")
        return "00010000";
    else if(str=="ADD M(X)")
        return "00000101";
    else if(str=="ADD|M(X)|")
        return "00000111";
    else if(str=="SUB M(X)")
        return "00000110";
    else if(str=="SUB |M(X)|")
        return "00001000";
    else if(str=="MUL M(X)")
        return "00001011";
    else if(str=="DImemory M(X)")
        return "00001100";
    else if(str=="LSH")
        return "00010100";
    else if(str=="RSH")
        return "00010101";
    else if(str=="STOR M(X,8:19)")
        return "00010010";
    else if(str=="STOR M(X,28:39)")
        return "00010011";
    else 
        return "000000000";
}
string address(string a) //this function returns entire 40 bit instructions when user inputs english instructions
{
    int ctr=0;
    string s=""; //contains entire 40 bit instructions
    string no="";
    string l="";
    
    if(a[0]=='J')
   
    {
        int len=a.length();
        int i;
        string w="";
        for( i=len-1;i>=0;i--)
        {
            if(a[i]!=' ')
            {
                no=no+a[i];
            }
            else
            {
                for(int j=0;j<i;j++)
                {
                    w=w+a[j];
                }
                break;
            }
        }
    reverse(no.begin(), no.end());
    int number=stoi(no);
    std::string str = std::bitset<12>(number).to_string();
    string op=assembler(w);
    s=op+str;
    w="";
    if(s.length()==20)
    {
        s="00000000000000000000"+s;
        return s;
    }
    return s;
    
    }
    else
    {
    for(int i=0;i<a.length();i++)
    {
        if(a[i]>=48 && a[i]<=57)
        {
             while(1)
            {
                if(a[i]!=' ' && ctr!=a.length()-1)
                {
                    no=no+a[i];
                    i++;
                    
                }
                else
                {
                    int number=stoi(no);
                    std::string str = std::bitset<12>(number).to_string();
                    int len=l.length()-1;
                    string ass=assembler(l.substr(0,len));
                    s=s+ass+str;
                    l="",no="";
                    break;
                }
                ctr++;
            }

        }
        else
        {
            l=l+a[i];
        }


    }
    if(s.length()==0)
        return "00000000";
    else
    
    return s;
    }
}
void decode(string s) //decode the 40 bit instructions and output the values
{
    while(1)
    {
        string LHS=s.substr(0,20); 
        string RHS=s.substr(20,40);
        string op=LHS.substr(0,8);
        string add=LHS.substr(8,20);
        //LHS EXECUTION
        if(LHS!="00000000000000000000")
        {
            int loc=stoi(add, 0, 2);
            cout<<"LEFT INSTRUCTION CYCLE--------->"<<endl;
        
        if(op=="00000000")
            break;
        else if(op=="00000001") //LOAD M(X)
        {
            string bin = memory[loc];
            MBR=bin;
            AC=MBR;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;   
        }
        else if(op=="00100001") //STORE M(X)
        {
            int Num,Address;
            string Ml;
            Ml=AC;
            MBR=AC;
            Address=stoi(add,0,2);
            memory[Address]=Ml;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00000101") //ADD M(X)
        {
            int prev,next;
            if(AC[0]=='1')
                 prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                 next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);
            int res=prev+next;
            std::string bin1 = std::bitset<40>(res).to_string();
            AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00000110")//SUB M(X)
        {
            int prev,next;
            if(AC[0]=='1')
                 prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                 next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);
            int res=prev-next;
            std::string bin1 = std::bitset<40>(res).to_string();
            AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        
        }
        else if(op=="00010100") //LSH
        {
            string zero="";
            for(int i=0;i<loc;i++)
                zero=zero+"0";
            string shift=AC.substr(loc,40)+zero;
            AC=shift;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00001101") //JUMP M(X)
        {
            PC=loc;
        }
      
        IR=op;
        IBR=RHS;
        MAR=add;
        cout<<"PC="<<PC<<endl;
        cout<<"MAR="<<MAR<<endl;
        cout<<"IR="<<IR<<endl;
        cout<<"IBR="<<IBR<<endl;
        PC+=1;
        

        cout<<endl;
        op=RHS.substr(0,8);
        add=RHS.substr(8,20);
       
        loc=stoi(add, 0, 2);
        cout<<"RIGHT INSTRUCTION CYCLE--------->"<<endl;
        //RHS EXECUTION
        if(op=="00000000")
            break;
        else if(op=="00000001") //LOAD M(X)
        {
            string bin = memory[loc];
            MBR=bin;
            AC=MBR;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00100001") //STOR M(X)
        {
            int Num,Address;
            string Ml;
            Ml=AC;
            MBR=AC;
            // Num=stoi(Ml,0,2);
            Address=stoi(add,0,2);
            memory[Address]=Ml;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
         else if(op=="00000101") //ADD M(X)
        {
            int prev,next;
            if(AC[0]=='1')
                prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);
            
            int res=prev+next;
            std::string bin1 = std::bitset<40>(res).to_string();
            AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
         else if(op=="00000110")//SUB M(X)
        {
            int prev,next;
            if(AC[0]=='1')
                 prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                 next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);
            
            int res=prev-next;
            std::string bin1 = std::bitset<40>(res).to_string();
            AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00010100") //LSH
        {
            string zero="";
            for(int i=0;i<loc;i++)
                zero=zero+"0";
            string shift=AC.substr(loc,40)+zero;
            AC=shift;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
          else if(op=="00001101") //JUMP M(X)
        {
            PC=loc;
        }
        IR=op;
        MAR=add;
        cout<<"PC="<<PC<<endl;
        cout<<"MAR="<<MAR<<endl;
        cout<<"IR="<<IR<<endl;
        cout<<endl;
        
        break;
        }
        //This is executed when there is only 1 instruction so it goes to RHS
        else
        {
        op=RHS.substr(0,8);
        add=RHS.substr(8,20);
        int loc=stoi(add, 0, 2);
        cout<<"RIGHT INSTRUCTION CYCLE--------->"<<endl;
        
        if(op=="00000000")
            break;
        else if(op=="00000001") //LOAD M(X)
        {
           string bin = memory[loc];
            MBR=bin;
            AC=MBR;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
        else if(op=="00100001") //STOR M(X)
        
        {
            int Num,Address;
            string Ml;
            Ml=AC;
            MBR=AC;
            Address=stoi(add,0,2);
            memory[Address]=Ml;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
         else if(op=="00000101") //ADD M(X)
        {
          int prev,next;
            if(AC[0]=='1')
                prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);

            int res=prev+next;
            std::string bin1 = std::bitset<40>(res).to_string();
             AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
         else if(op=="00000110")//SUB M(X)
        {
            int prev,next;
            if(AC[0]=='1')
                 prev=signbin(AC);
            else
                prev= stoi(AC,0,2);
            if(memory[loc][0]=='1')
                 next=signbin(memory[loc]);
            else
                next=stoi(memory[loc],0,2);

            int res=prev-next;
            std::string bin1 = std::bitset<40>(res).to_string();
         
            AC=bin1;
            MBR=memory[loc];
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        
        }
        else if(op=="00010100") //LSH
        {
            string zero="";
            for(int i=0;i<loc;i++)
                zero=zero+"0";
            string shift=AC.substr(loc,40)+zero;
            AC=shift;
            cout<<"AC="<<AC<<endl;
            cout<<"MBR="<<MBR<<endl;
        }
          else if(op=="00001101") //JUMP M(X)
        {
            PC=loc;   
        }
      
        IR=op;
        MAR=add;
        IBR=RHS;
        cout<<"PC="<<PC<<endl;
        cout<<"MAR="<<MAR<<endl;
        cout<<"IR="<<IR<<endl;
        cout<<endl;
        }
        PC+=1;
        break;

    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int count=0;
    string temp;
    string t="00000000000000000000";
    //Options that the user gets
    cout<<"Enter '1' to Swap two Numbers"<<endl;
    cout<<"Enter '2' to Add two Numbers" <<endl;
    cout<<"Enter '3' to difference two numbers(a-b)"<<endl;
    cout<<"Enter '4' to Find perimeter of rectangle " <<endl;
    cout<<"Enter '5' to find 5th element of fibonacci"<<endl;
    
    int choice,a,b;
    cin>>choice;
    cout<<"Enter two numbers a and b"<<endl;
    cin>>a>>b;
    //numbers are stored in binary form in memory location starting from 200
    std::string str = std::bitset<40>(a).to_string();
    memory[200]=str;
    std::string str2 = std::bitset<40>(b).to_string();
    memory[201]=str2;
    
    while(1)
    {
        string inp;
        getline(cin, inp);
        memory[count]=inp;
        temp=memory[count];
        if(temp=="HALT") //stops when user inputs HALT
            break;
        count++; 
    }

    cout<<endl;
    cout<<endl;
    if(choice==1) //Swapping two numbers without temporary variable
    {
    cout<<"Elements before swapping are ";
    for(int i=200;i<202;i++)
    {
        if(memory[i][0]=='1')
            cout<<signbin(memory[i])<<" ";
        else
            cout<<stoi(memory[i],0,2)<<" ";
    }
    cout<<endl;
    count=0;
    int loc;
    while(1)
    {
     static int ctr=1;  
    temp=memory[count];
    if(temp=="HALT")
    {
         cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<"0000000000000000000000000000000000000000000"<<endl;
        
        break;
    }
    
    string ins=address(memory[count]); //40 bit instruction

    if(ins.length()==20||ins=="00000000")
    {
        if(ins=="00000000")
            ins="0000000000000000000000000000000000000000";
        else
        ins=t+ins;
    }
    if(ins!="0000000000000000000000000000000000000000")
    {

       cout<<"INSTRUCTION --------->"<<ctr<<endl;
        cout<<ins<<endl;
        ctr++;
        
    }
    decode(ins);
    count++;
    }
    cout<<"Elements after swapping are ";
     for(int i=200;i<202;i++)
    {
        if(memory[i][0]=='1')
            cout<<signbin(memory[i])<<" ";
        else
            cout<<stoi(memory[i],0,2)<<" ";
    }
    cout<<endl;
    }
    else if(choice ==2) //Adding two numbers
    {
        int loc;
        count=1;
    while(1)
    {
        static int ctr=1;
     

    temp=memory[count];
    if(temp=="HALT")
    {
         cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<"0000000000000000000000000000000000000000000"<<endl;
        
        break;
    }
    string ins=address(memory[count]);

    if(ins.length()==20||ins=="00000000")
    {
        if(ins=="00000000")
            ins="0000000000000000000000000000000000000000";
        else
        ins=t+ins;
    }
    string address=ins.substr(28,40);
     loc=stoi(address, 0, 2);
      if(ins!="0000000000000000000000000000000000000000")
      {
          cout<<"INSTRUCTION --------->"<<ctr<<endl;
        cout<<ins<<endl;
        
        ctr++;
      }
    decode(ins);
    count++;
    }
    if(memory[loc][0]=='1')
    {
            int act=signbin(memory[loc]);
            cout<<"Sum of a and b is "<<act<<endl;
    }
        else
         cout<<"Sum of a and b is "<<stoi(memory[loc],0,2)<<endl;
    }
    else if(choice==3) //Subtracting two numbers
    {
         count=1;
         int loc;
    while(1)
    {
        static int ctr=1;
    temp=memory[count];
    if(temp=="HALT")
    {
       
        cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<"0000000000000000000000000000000000000000000"<<endl;
        break;
    }
    string ins=address(memory[count]);

    if(ins.length()==20||ins=="00000000")
    {
        if(ins=="00000000")
            ins="0000000000000000000000000000000000000000";
        else
        ins=t+ins;
    }
    string address=ins.substr(28,40);
     loc=stoi(address, 0, 2);
      if(ins!="0000000000000000000000000000000000000000")
      {
        cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<ins<<endl;
      }
        
    decode(ins);
    count++;
    }
     if(memory[loc][0]=='1')
    {
        int act=signbin(memory[loc]);
        cout<<"Difference of a and b is "<<act<<endl;
    }
    else
        cout<<"Difference of a and b is "<<stoi(memory[loc],0,2)<<endl;
    }
    
    else if(choice==4) //perimeter of rectangle using LSH
    {
        int loc;
        count=1;
        while(1)
    {
        static int ctr=1;
        temp=memory[count];
        if(temp=="HALT")
        {
         cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<"0000000000000000000000000000000000000000000"<<endl;
        
        break;
        }
    
    string ins=address(memory[count]);

    if(ins.length()==20||ins=="00000000")
    {
        if(ins=="00000000")
            ins="0000000000000000000000000000000000000000";
        else
        ins=t+ins;
    }
      string address=ins.substr(28,40);
     loc=stoi(address, 0, 2);
      if(ins!="0000000000000000000000000000000000000000")
      {
          cout<<"INSTRUCTION --------->"<<ctr<<endl;
        cout<<ins<<endl;
        
        ctr++;
      }
    decode(ins);
    count++;
    }
     if(memory[loc][0]=='1')
    {
            int act=signbin(memory[loc]);
            cout<<"perimeter of rectangle is "<<act<<endl;
    }
        else
         cout<<"perimeter of rectangle is "<<stoi(memory[loc],0,2)<<endl;
    }

    else if(choice==5) //prints 5th element of fibonacci series
    {
    count=1;
    int loc;
    while(1)
    {
     static int ctr=1;
     static int fib=1; //jump counter
     
    temp=memory[count];
    if(temp=="HALT")
    {
         cout<<"INSTRUCTION --------->"<<ctr<<endl;
            ctr++;
        cout<<"0000000000000000000000000000000000000000000"<<endl;
        
        break;
    }
    else if(temp[0]=='J')
    {
        string ins=address(memory[count]);
        cout<<"INSTRUCTION --------->"<<ctr<<endl;
        cout<<ins<<endl;
        ctr++;
        string sl=ins.substr(28,40);
        count =stoi(sl, 0, 2);
        decode(ins);
        if(fib==4)
        {
            cout<<"INSTRUCTION --------->"<<ctr<<endl;
            cout<<"0000000000000000000000000000000000000000"<<endl;
            cout<<endl;
            break;
        }
        else  
            fib++;
            continue;
    }
    
    string ins=address(memory[count]);

    if(ins.length()==20||ins=="00000000")
    {
        if(ins=="00000000")
            ins="0000000000000000000000000000000000000000";
        else
        ins=t+ins;
    }
    string address=ins.substr(28,40);
    loc=stoi(address, 0, 2);
    if(ins!="0000000000000000000000000000000000000000")
    {

       cout<<"INSTRUCTION --------->"<<ctr<<endl;
        cout<<ins<<endl;
        ctr++;
        
    }
    decode(ins);
    count++;
    }
     if(memory[loc][0]=='1')
    {
            int act=signbin(memory[loc]);
            cout<<"5th element of fibonacci is "<<act<<endl;
    }
    else
         cout<<"5th element of fibonacci is "<<stoi(memory[loc],0,2)<<endl;

    }
    
}  

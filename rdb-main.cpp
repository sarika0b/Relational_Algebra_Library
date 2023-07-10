#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

using namespace std;


//structure to define a table
typedef struct {
    string name;
    Relation * rel;
    vector<string> attr_types;
}table;


//vector to store all the tables
vector<table> tables;

//test selection for float and string attribute types
void testSelection(){
    vector<string> attr_names;
    attr_names.push_back("A");
    attr_names.push_back("B");
    attr_names.push_back("C");
    attr_names.push_back("D");
    Relation * R = new Relation(attr_names);
    Record * r = new Record();
    r->addAttribute(new floatAttr(1.1));
    r->addAttribute(new stringAttr("abc"));
    r->addAttribute(new IntAttr(3));
    r->addAttribute(new IntAttr(4));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(5.5));
    r->addAttribute(new stringAttr("def"));
    r->addAttribute(new IntAttr(7));
    r->addAttribute(new IntAttr(8));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(9.9));
    r->addAttribute(new stringAttr("ghi"));
    r->addAttribute(new IntAttr(11));
    r->addAttribute(new IntAttr(12));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(13.13));
    r->addAttribute(new stringAttr("jkl"));
    r->addAttribute(new IntAttr(15));
    r->addAttribute(new IntAttr(16));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(17.17));
    r->addAttribute(new stringAttr("mno"));
    r->addAttribute(new IntAttr(19));
    r->addAttribute(new IntAttr(20));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(21.21));
    r->addAttribute(new stringAttr("pqr"));
    r->addAttribute(new IntAttr(23));
    r->addAttribute(new IntAttr(24));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(25.25));
    r->addAttribute(new stringAttr("stu"));
    r->addAttribute(new IntAttr(27));
    r->addAttribute(new IntAttr(28));
    R->addRecord(r);
    r = new Record();
    r->addAttribute(new floatAttr(29.29));
    r->addAttribute(new stringAttr("vwx"));
    r->addAttribute(new IntAttr(31));
    r->addAttribute(new IntAttr(32));
    R->addRecord(r);
    //selection
  
    DNFformula * f = new DNFformula();
    list <tuple <string, char, Attr *> > l;
    tuple <string, char, Attr *> t;
    get<0>(t) = "A";
    get<1>(t) = '>';
    get<2>(t) = new floatAttr(1.1);
    l.push_back(t);
    get<0>(t) = "B";
    get<1>(t) = '>';
    get<2>(t) = new stringAttr("def");
    l.push_back(t);
    //call selection
    f->ops.push_back(l);
    Relation * R1 = selection(R,f);

    printRelation(R1);
}

//test natural join over r1 and r2
void testNaturalJoin(){
    vector<string> attr_names;
    attr_names.push_back("A");
    attr_names.push_back("B");
    attr_names.push_back("C");
    attr_names.push_back("D");
    Relation * R1 = new Relation(attr_names);
    Record * r = new Record();
    r->addAttribute(new IntAttr(1));
    r->addAttribute(new IntAttr(2));
    r->addAttribute(new IntAttr(3));
    r->addAttribute(new IntAttr(4));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(5));
    r->addAttribute(new IntAttr(6));
    r->addAttribute(new IntAttr(7));
    r->addAttribute(new IntAttr(8));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(9));
    r->addAttribute(new IntAttr(10));
    r->addAttribute(new IntAttr(11));
    r->addAttribute(new IntAttr(12));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(13));
    r->addAttribute(new IntAttr(14));
    r->addAttribute(new IntAttr(15));
    r->addAttribute(new IntAttr(16));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(17));
    r->addAttribute(new IntAttr(18));
    r->addAttribute(new IntAttr(19));
    r->addAttribute(new IntAttr(20));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(21));
    r->addAttribute(new IntAttr(22));
    r->addAttribute(new IntAttr(23));
    r->addAttribute(new IntAttr(24));
    R1->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(9));
    r->addAttribute(new IntAttr(26));
    r->addAttribute(new IntAttr(27));
    r->addAttribute(new IntAttr(28));
    R1->addRecord(r);

    vector<string> attr_names2;
    attr_names2.push_back("E");
    attr_names2.push_back("F");
    attr_names2.push_back("A");
    attr_names2.push_back("G");
    Relation * R2 = new Relation(attr_names2);
    r = new Record();
    r->addAttribute(new IntAttr(1));
    r->addAttribute(new stringAttr("anjs"));
    r->addAttribute(new IntAttr(9));
    r->addAttribute(new IntAttr(4));
    R2->addRecord(r);
    r = new Record();
    r->addAttribute(new IntAttr(5));
    r->addAttribute(new stringAttr("hab"));
    r->addAttribute(new IntAttr(13));
    r->addAttribute(new IntAttr(8));
    R2->addRecord(r);
 
    //natural join
   list<string> common_attr;
    common_attr.push_back("A");
    Relation * R3 = naturaljoin(R1,R2,common_attr);
    printRelation(R3);
}

int main(){
    
    while(1){
    cout<<"Enter 1 to create a new table"<<endl;
    cout<<"Enter 2 to delete a table"<<endl;
    cout<<"Enter 3 to add a record to a table"<<endl;
    cout<<"Enter 4 to print a table"<<endl;
    cout<<"Enter 5 to create a table from existing tables by performing different operations."<<endl;
    cout<<"Enter 6 to Display the names of current tables"<<endl;

    int n;
    cin>>n;

    if(n==1){
        int numofattr;

        table t;
        cout<<"Enter the name of the table"<<endl;
        cin>>t.name;
        cout<<"Enter the no. of attributes"<<endl;
        cin>>numofattr;
        vector<string> attr_names(numofattr);
        for(int i=0;i<numofattr;i++){
            cout<<"Enter the name of attribute "<<i+1<<endl;
            cin>>attr_names[i];
        }
        Relation * R = new Relation(attr_names);
        t.rel=R;
        cout<<"Table created successfully"<<endl;
        tables.push_back(t);
        
    }
    else if(n==2){
        cout<<"Enter the name of the table you want to delete"<<endl;
        string name;
        cin>>name;
        for(int i=0;i<tables.size();i++){
            if(tables[i].name==name){
                tables[i].rel->deleteRelation();
                for(int j=i;j<tables.size()-1;j++){
                    tables[j]=tables[j+1];
                }
                cout<<"Table deleted successfully"<<endl;
                int size = tables.size();
                tables.resize(size-1);
            }
        }
    
    }
    else if(n==3){
        //add a record
        cout<<"Enter the name of the table you want to add a record to"<<endl;
        string name;
        cin>>name;
      
        for(int i=0;i<tables.size();i++){
            if(tables[i].name==name){
                Record * r = new Record();
                
                if(tables[i].rel->getNumRecords()==0){
                    cout<<"Enter the type of each of the attributes"<<endl;
                    cout<<"Enter int for integer, string for string and float for float data type"<<endl;
                    for(int j=0;j<tables[i].rel->getAttributeNames().size();j++){
                        cout<<"Enter the type of attribute for "<<tables[i].rel->getAttributeNames()[j]<<endl;
                        string type;
                        cin>>type;
                        tables[i].attr_types.push_back(type);
                    }
                }

                for(int j=0;j<tables[i].rel->getAttributeNames().size();j++){
                    cout<<"Enter the value of attribute "<<tables[i].rel->getAttributeNames()[j]<<endl;
                    //string type=attr_types[j];
                    if(tables[i].attr_types[j]=="int"){
                        int val;
                        cin>>val;
                        r->addAttribute(new IntAttr(val));
                    }
                    else if(tables[i].attr_types[j]=="string"){
                        string val;
                        cin>>val;
                        r->addAttribute(new stringAttr(val));
                    }
                    else if(tables[i].attr_types[j]=="float"){
                        float val;
                        cin>>val;
                        r->addAttribute(new floatAttr(val));
                    }
                }
                tables[i].rel->addRecord(r);
                cout<<"Record added successfully"<<endl;
                break;
            }
            
        }
    
    }
    else if(n==4){
        //print a table
        cout<<"Enter the name of the table you want to print"<<endl;
        string name;
        cin>>name;
        for(int i=0;i<tables.size();i++){
            if(tables[i].name==name){
                printRelation(tables[i].rel);
            }
        }
    }
    else if(n==5){

        cout<<"Enter 1 to create union of two tables"<<endl;
        cout<<"Enter 2 to create difference of two tables"<<endl;
        cout<<"Enter 3 to implement projection of a table"<<endl;
        cout<<"Enter 4 to implement selection of a table"<<endl;
        cout<<"Enter 5 to rename attribute of a table"<<endl;
        cout<<"Enter 6 to implement cartesian product of two tables"<<endl;
        cout<<"Enter 7 to implement natural join of two tables"<<endl;

        int n;
        cin>>n;

        if(n==1){
            //select two tables
            cout<<"Enter the names of the two tables you want to perform union on"<<endl;
            string name1,name2;
            cin>>name1>>name2;
            Relation * R1;
            Relation * R2;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name1){
                    R1=tables[i].rel;
                }
                if(tables[i].name==name2){
                    R2=tables[i].rel;
                }
            }
            Relation * R = union_(R1,R2);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "unionof_"+name1+"_and_"+name2;
            tables.push_back(ttemp);

        }
        else if(n==2){
            cout<<"Enter the names of the two tables you want to perform difference on"<<endl;
            string name1,name2;
            cin>>name1>>name2;
            Relation * R1;
            Relation * R2;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name1){
                    R1=tables[i].rel;
                }
                if(tables[i].name==name2){
                    R2=tables[i].rel;
                }
            }
            Relation * R = difference(R1,R2);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "differenceof_"+name1+"_and_"+name2;
            tables.push_back(ttemp);
        }
        else if(n==3){
            cout<<"Enter the name of the table you want to perform projection on"<<endl;
            string name;
            cin>>name;
            Relation * R1;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name){
                    R1=tables[i].rel;
                }
            }
            cout<<"Enter the no. of attributes you want to project on"<<endl;
            int numofattr;
            cin>>numofattr;
            list<string> attr_names;
            for(int i=0;i<numofattr;i++){
                cout<<"Enter the name of attribute "<<i+1<<endl;
                string str;
                cin>>str;
                attr_names.push_back(str);
            }
            Relation * R = projection(R1,attr_names);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "projectionof_"+name;
            tables.push_back(ttemp);


        }
        else if(n==4){
            cout<<"Enter the name of the table you want to perform selection on"<<endl;
            string name;
            cin>>name;
            Relation * R1;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name){
                    R1=tables[i].rel;
                }
            }

            DNFformula * f = new DNFformula();
            list <tuple <string, char, Attr *> > l;
            tuple <string, char, Attr *> t;
            cout<<"Enter the no. of conditions you want to add"<<endl;
            int numofcond;
            cin>>numofcond;
            for(int i=0;i<numofcond;i++){
                cout<<"Enter the name of attribute "<<i+1<<endl;
                string attr_name;
                cin>>attr_name;
                cout<<"Enter the operator you want to use"<<endl;
                char op;
                cin>>op;
                cout<<"Enter the type of the attribute"<<endl;
                string type;
                cin>>type;
                if(type=="int"){
                    int val;
                    cin>>val;
                    Attr * a = new IntAttr(val);
                    get<0>(t)=attr_name;
                    get<1>(t)=op;
                    get<2>(t)=a;
                    l.push_back(t);
                }
                else if(type=="string"){
                    string val;
                    cin>>val;
                    Attr * a = new stringAttr(val);
                    get<0>(t)=attr_name;
                    get<1>(t)=op;
                    get<2>(t)=a;
                    l.push_back(t);
                }
                else if(type=="float"){
                    float val;
                    cin>>val;
                    Attr * a = new floatAttr(val);
                    get<0>(t)=attr_name;
                    get<1>(t)=op;
                    get<2>(t)=a;
                    l.push_back(t);
                }
            }
            f->ops.push_back(l);
            Relation * R = selection(R1,f);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "selectionof_"+name;
            tables.push_back(ttemp);

            


        }
        else if(n==5){
            cout<<"Enter the name of the table you want to rename attribute of"<<endl;
            string name;
            cin>>name;
            Relation * R1;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name){
                    R1=tables[i].rel;
                }
            }
            cout<<"Enter the name of the attribute you want to rename"<<endl;
            string attr_name;
            cin>>attr_name;
            cout<<"Enter the new name of the attribute"<<endl;
            string new_attr_name;
            cin>>new_attr_name;
            Relation * R = rename(R1,attr_name,new_attr_name);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "renameof_"+name;
            tables.push_back(ttemp);
        }
        
        else if(n==6){
            cout<<"Enter the names of the two tables you want to perform cartesian product on"<<endl;
            string name1,name2;
            cin>>name1>>name2;
            Relation * R1;
            Relation * R2;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name1){
                    R1=tables[i].rel;
                }
                if(tables[i].name==name2){
                    R2=tables[i].rel;
                }
            }
            Relation * R = cartesianProduct(R1,R2);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "cartesianProductof_"+name1+"_and_"+name2;
            tables.push_back(ttemp);

        }
        else if(n==7){
            cout<<"Enter the names of the two tables you want to perform natural join on"<<endl;
            string name1,name2;
            cin>>name1>>name2;
            Relation * R1;
            Relation * R2;
            for(int i=0;i<tables.size();i++){
                if(tables[i].name==name1){
                    R1=tables[i].rel;
                }
                if(tables[i].name==name2){
                    R2=tables[i].rel;
                }
            }
            list<string> join_attrs;
            cout<<"Enter the number of attributes you want to join on"<<endl;
            int n;
            cin>>n;
            cout<<"Enter the names of the attributes you want to join on"<<endl;
            for(int i=0;i<n;i++){

                string attr;
                cin>>attr;
                join_attrs.push_back(attr);
            }
            Relation * R = naturaljoin(R1,R2,join_attrs);
            table ttemp;
            ttemp.rel=R;
            ttemp.name= "naturaljoinof_"+name1+"_and_"+name2;
            tables.push_back(ttemp);

        }
        else{
            cout<<"Invalid input"<<endl;
        }
        
    }
    else if(n==6){
        cout<<"The names of the current tables are:"<<endl;
        for(int i=0;i<tables.size();i++){
            cout<<tables[i].name<<endl;
        }
    }
    else{
        cout<<"Invalid input"<<endl;
        break;
    }


}
}



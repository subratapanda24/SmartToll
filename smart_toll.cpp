#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

string getCurrentTimestamp(){

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",ltm);
    return string(buffer);
}

class Vehicle {

private:
    string plateNumber;
    string ownerName;
    string vehicleType;
    bool hasFasTag;

public:
    Vehicle(){
        plateNumber="";
        ownerName="";
        vehicleType="";
        hasFasTag=false;
    }

    Vehicle(string plate,string owner,string type,bool fasTag){
        plateNumber=plate;
        ownerName=owner;
        vehicleType=type;
        hasFasTag=fasTag;
    }

    string getPlate(){ return plateNumber; }
    string getOwner(){ return ownerName; }
    string getType(){ return vehicleType; }
    bool getFasTag(){ return hasFasTag; }

    void display(){
        cout<<"  Plate No     : "<<plateNumber<<"\n";
        cout<<"  Owner        : "<<ownerName<<"\n";
        cout<<"  Vehicle Type : "<<vehicleType<<"\n";
        cout<<"  FASTag       : "<<(hasFasTag?"Yes":"No")<<"\n";
    }
};

class TollSystem {
private:

    Vehicle vehicles[100];
    int vehicleCount;

    double calculateToll(string type){

        if(type=="Motorcycle") return 30;
        if(type=="Car") return 60;
        if(type=="SUV") return 80;
        if(type=="Bus") return 120;
        if(type=="Truck") return 150;

        return 0;
    }

    int findVehicle(string plate){

        for(int i=0;i<vehicleCount;i++){
            if(vehicles[i].getPlate()==plate)
                return i;
        }

        return -1;
    }

    void logTransaction(string plate,string type,double amount,string mode){

        ofstream file("transactions.txt",ios::app);

        if(file.is_open()){

        file<<"Plate: "<<plate<<"\n";
        file<<"Type: "<<type<<"\n";
        file<<"Amount: INR "<<amount<<"\n";
        file<<"Mode: "<<mode<<"\n";
        file<<"Time: "<<getCurrentTimestamp()<<"\n";
        file<<"-----------------------------\n";

        file.close();
    }
}

    void generateReceipt(Vehicle &v,double baseToll,double finalToll){

        double discount=v.getFasTag()?baseToll*0.10:0.0;

        string filename="receipt_"+v.getPlate()+"_"+getCurrentTimestamp()+".txt";

        ofstream file(filename);

        if(file.is_open()){

            file<<fixed<<setprecision(2);

            string booth="BOOTH-1 - NH-48 Entry Gate";

            file<<"================================================\n";
            file<<"       SMART TOLL COLLECTION RECEIPT\n";
            file<<"================================================\n";

            file<<"Date & Time  : "<<getCurrentTimestamp()<<"\n";
            file<<"Booth        : "<<booth<<"\n";

            file<<"------------------------------------------------\n";

            file<<"Plate No     : "<<v.getPlate()<<"\n";
            file<<"Owner        : "<<v.getOwner()<<"\n";
            file<<"Vehicle Type : "<<v.getType()<<"\n";
            file<<"FASTag       : "<<(v.getFasTag()?"Yes":"No")<<"\n";

            file<<"------------------------------------------------\n";

            file<<"Base Toll    : INR "<<baseToll<<"\n";

            if(v.getFasTag())
                file<<"FASTag Disc  : -INR "<<discount<<"\n";

            file<<"------------------------------------------------\n";

            file<<"TOTAL PAID   : INR "<<finalToll<<"\n";
            file<<"Payment Mode : "<<(v.getFasTag()?"FASTag":"Cash")<<"\n";

            file<<"================================================\n";
            file<<"        Thank you! Drive Safe!\n";
            file<<"================================================\n";

            file.close();

            cout<<"\nReceipt saved -> "<<filename<<"\n";
        }
    }

public:

    TollSystem(){
        vehicleCount=0;
    }

    void registerVehicle(){
        cout<<"\n  --- Register New Vehicle ---\n";

        string plate,owner,type;
        int typeChoice;
        char ft;

        cout<<"  Enter Plate Number : ";
        cin>>plate;

        if(findVehicle(plate)>=0){
            cout<<"  Error: Plate already registered.\n";
            return;
        }

        cin.ignore();

        cout<<"  Owner Name         : ";
        getline(cin,owner);

        cout<<"\n  Vehicle Types:\n";
        cout<<"  1. Motorcycle\n";
        cout<<"  2. Car\n";
        cout<<"  3. SUV\n";
        cout<<"  4. Bus\n";
        cout<<"  5. Truck\n";

        do{
            cout<<"  Choice (1-5)       : ";
            cin>>typeChoice;
        }while(typeChoice<1 || typeChoice>5);

        switch(typeChoice){

            case 1: type="Motorcycle"; break;
            case 2: type="Car"; break;
            case 3: type="SUV"; break;
            case 4: type="Bus"; break;
            case 5: type="Truck"; break;
        }

        cout<<"  Has FASTag? (y/n)  : ";
        cin>>ft;

        bool fasTag=(ft=='y'||ft=='Y');

        vehicles[vehicleCount++]=Vehicle(plate,owner,type,fasTag);

        cout<<"\n  Vehicle registered successfully!\n";
    }

    void processToll(){

        cout<<"\n  --- Process Toll ---\n";

        string plate;
        cout<<"  Enter Plate No  : ";
        cin>>plate;

        int vi=findVehicle(plate);
        if(vi<0){
            cout<<"  Error: Vehicle not registered.\n";
            return;
        }

        Vehicle &v=vehicles[vi];
        double baseToll=calculateToll(v.getType());
        double toll=baseToll;

        if(v.getFasTag())
            toll*=0.9;

        logTransaction(plate,v.getType(),toll,
                       v.getFasTag()?"FASTag":"Cash");

        generateReceipt(v,baseToll,toll);
    }

    void searchVehicle(){
        cout<<"\n  --- Search Vehicle ---\n";

        string plate;
        cout<<"  Enter Plate No: ";
        cin>>plate;

        int vi=findVehicle(plate);
        if(vi<0){
            cout<<"  Error: Vehicle not found.\n";
            return;
        }

         cout<<"\n  Vehicle Found Successfully!\n";
        cout<<"  --------------------\n";
        vehicles[vi].display();
        cout<<"  --------------------\n";
    }

    void viewTransactions(){
        cout<<"\n  --- Transaction Log ---\n";

        ifstream file("transactions.txt");

        if(!file.is_open()){
            cout<<"  No transactions recorded yet.\n";
            return;
        }

        string line;
        int count=0;

        while(getline(file,line)){
            cout<<"  "<<line<<"\n";

            if(line=="-----------------------------")
                count++;
        }

        file.close();

        cout<<"  --------------------\n";
        cout<<"  Total transactions: "<<count<<"\n";
    }

    void viewAllVehicles(){

        cout<<"\n  --- All Registered Vehicles ---\n";

        if(vehicleCount==0){
            cout<<"  No vehicles registered yet.\n";
            return;
        }

        for(int i=0;i<vehicleCount;i++){

            cout<<"\n  ["<<(i+1)<<"]\n";
            vehicles[i].display();
            cout<<"  --------------------\n";
        }

        cout<<"  Total: "<<vehicleCount<<" vehicle(s)\n";
    }
};

int main(){

    TollSystem system;
    int choice;

    cout<<"\n";
    cout<<"  ================================================\n";
    cout<<"       SMART TOLL COLLECTION SYSTEM\n";
    cout<<"  ================================================\n";

    do{
        cout<<"\n";
        cout<<"     MAIN MENU\n";
        cout<<"  ================\n";
        cout<<"  1. Register Vehicle\n";
        cout<<"  2. Process Toll\n";
        cout<<"  3. Search Vehicle\n";
        cout<<"  4. Transaction Log\n";
        cout<<"  5. All Registered Vehicles\n";
        cout<<"  6. Exit\n";
        cout<<"  ----------------\n";

        cout<<"  Enter choice (1-6): ";

        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"  Invalid input. Enter number 1-6.\n";
            continue;
        }

        switch(choice){

            case 1: system.registerVehicle(); break;
            case 2: system.processToll(); break;
            case 3: system.searchVehicle(); break;
            case 4: system.viewTransactions(); break;
            case 5: system.viewAllVehicles(); break;

            case 6:
                cout<<"\n  ------------------------------------------------\n";
                cout<<"  Thank you for using the Toll System. Goodbye!\n";
                cout<<"  ------------------------------------------------\n";
                break;
        }

    }while(choice!=6);

    return 0;
}
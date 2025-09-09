#include<bits/stdc++.h>
using namespace std;

class Appointment {
    private:
    string date;
    string time;
    string reason;
    string status;
    public:
    Appointment(string d, string t, string r, string s) : 
    date(d), time(t), reason(r), status(s) {}
    string getdate() {
        return date;
    }
    string gettime() {
        return time;
    }
    string getreason () {
        return reason;
    }
    void updatestatus(string s) {
         status = s;
         cout << "Appointment status updated to: " << status << endl;
    }
    

    void displayappointment() {
        cout << "Appointment Infomation" << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Reason: " << reason << endl;
        cout << "Status: " << status << endl;
    }
};

class Patient {
    protected:
    string name;
    int id;
    int age;
    vector<string>medicalHistory;
    vector<Appointment* >appointment;
    public:
    Patient(string n, int i, int a ) : name(n), id(i), age(a) {} 
    int getid() {
        return id;
    }
    string getname() {
        return name;
    }
    
    virtual void scheduleappointment(Appointment * app) {
        appointment.push_back(app); 
        cout << "The patient " << name << " has successfully scheduled an appointment " << endl; 

    }
    void cancelappointment(Appointment * app) {
        auto it = find(appointment.begin(), appointment.end(), app) ;
        if(it != appointment.end()) {
            appointment.erase(it);
            
        }
        
    }  
    virtual void addmedicalhistory(string med) {
        medicalHistory.push_back(med);
    }
    virtual void displayInfo() {
        
        cout << "Patient Information" << endl;
        cout << "Name: " << name << endl;
        cout << "Id: " << id << endl;
        cout << "age: " << age << endl;
        cout << "medicalHistory: " ;
        for(int i = 0; i < medicalHistory.size(); i++) {
            cout << medicalHistory[i] << endl ;
        }
    }

};

class ChronicPatient : public Patient {
   private:
   string conditionType;
   string lastCheckupDate;
   public:
   ChronicPatient(string n, int i, int a, string c, string l) : 
   Patient(n,i,a), conditionType(c), lastCheckupDate(l) {}

   void scheduleappointment(Appointment* app) override {
    cout << "The patient " << name << " has successfully scheduled an appointment " << endl; 
    cout << "Chronic Patient " << name << " condition: " << conditionType << ", check-up every 3 months" << endl;
     appointment.push_back(app); 
     
   }
    void addmedicalhistory(string med) override {
        medicalHistory.push_back(med);
    }
    
   void displayInfo() override  {
        cout << "Chronic Patient Information" << endl;
        Patient::displayInfo();
        cout << "Condition: " << conditionType << endl;
        cout << "Last check update: " << lastCheckupDate << endl;

}
};

class Doctor {
    private:
    string name;
    int id;
    string specialty;
    vector<Appointment*>appointment;
    public:
    Doctor(string n, int i, string s) : name(n) , id(i), specialty(s) {}

   void addapointment(Appointment * app) {
    appointment.push_back(app);
   }

   void cancelappointment(Appointment * app) {
        auto it = find(appointment.begin(), appointment.end(), app) ;
        if(it != appointment.end()) {
            appointment.erase(it);
        }
   }    
    void displayInfo() {
       cout << "Doctor Information" << endl;
       cout << "Name: " << name << endl;
       cout << "Id: " << id << endl;
       cout << "Specialty: " << specialty << endl;
    }
};
class Clinic {
    private:
    vector<Patient*>patient;
    vector<Doctor*>doctor;
    vector<Appointment*>appointment;
    public:
    void addpatient(Patient* pa) {
      patient.push_back(pa);
    }

    void adddoctor(Doctor* doc) {
        doctor.push_back(doc);
    }
    void addappointment(Appointment* app) {
        appointment.push_back(app);
    }
    void cancelappointment(Appointment * app) {
        auto it = find(appointment.begin(), appointment.end(), app) ;
        if(it != appointment.end()) {
            appointment.erase(it);
        }
   }   

    void scheduleAppointment(Patient* pa, Doctor* doc, Appointment* app) {
        pa->scheduleappointment(app);
        doc->addapointment(app);
        addappointment(app);
       
        cout << "Schedule Appointment" << endl;
        pa->displayInfo();
        doc->displayInfo();
        app->displayappointment();
    }
    
   void CancelAppointment(Patient* pa, Doctor* doc, Appointment* app )  {
    pa->cancelappointment(app);
    doc->cancelappointment(app);
    cancelappointment(app);
    app->updatestatus("Canceled");
   }
    


};
int main() {
    //Patient
    Patient *pa1 = new Patient("Duy", 123, 19) ;
    ChronicPatient* pa2= new ChronicPatient ("Vu", 345, 30, "Hypertension", "09-09-2025");
    //Doctor
    Doctor*  doc1 = new Doctor("A", 1, "General");
    Doctor* doc2 = new Doctor("B", 2, "Cardiology");
    //make Appointment
    Appointment* app1 = new Appointment("2025-09-10", "10:00", "General Checkup", "Scheduled");
    Appointment* app2 = new Appointment("2025-09-12", "14:00", "Diabetes Checkup", "Scheduled");
    //
    

    //
    pa1->addmedicalhistory("Visited on 2025-09-01: General Checkup - Normal");
    pa2->addmedicalhistory("Visited on 2025-09-01: Blood sugar high - Adjusted medication");
    //
    Clinic cl;
    cl.addpatient(pa1);
    cl.addpatient(pa2);
    cl.adddoctor(doc1);
    cl.adddoctor(doc2);
    cl.addappointment(app1);
    cl.addappointment(app2);

    cl.scheduleAppointment(pa1, doc1, app1);
    app1->updatestatus("Scheduled");

    cout << endl;
    cl.scheduleAppointment(pa2, doc2, app2);
    app2->updatestatus("Scheduled");

    cout << endl;
    cout << "Canceling Appointment" << endl;
    cl.CancelAppointment(pa1, doc1, app1);
    return 0;
}

#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
// define maximum number of patients in a queue
#define MAXPATIENTS 100

// define structure for patient data
struct patient
{
   char FirstName[50];
   char LastName[50];
   char ID[20];
};


// define class for queue
class queue
{
   public:
   queue (void);
   int AddPatientAtEnd (patient p);
   int AddPatientAtBeginning (patient p);
   patient GetNextPatient (void);
   int RemoveDeadPatient (patient * p);
   void OutputList (void);
   char DepartmentName[50];
   private:
   int NumberOfPatients;
   patient List[MAXPATIENTS];
};


// declare member functions for queue

queue::queue ()
{
   // constructor
   NumberOfPatients = 0;
}


int queue::AddPatientAtEnd (patient p)
{
   // adds a normal patient to the end of the queue.
   // returns 1 if successful, 0 if queue is full.
  if (NumberOfPatients >= MAXPATIENTS)
   {
      // queue is full
      return 0;
   }
      // put in new patient
      else
      List[NumberOfPatients] = p;  NumberOfPatients++;
      return 1;
}


int queue::AddPatientAtBeginning (patient p)
{
   // adds a critically ill patient to the beginning of the queue.
   // returns 1 if successful, 0 if queue is full.
   int i;
   if (NumberOfPatients >= MAXPATIENTS)
   {
      // queue is full
      return 0;
   }

   // move all patients one position back in queue
   for (i = NumberOfPatients-1; i >= 0; i--)
   {
      List[i+1] = List[i];
   }
   // put in new patient
   List[0] = p;  NumberOfPatients++;
   return 1;
}


patient queue::GetNextPatient (void)
{
   // gets the patient that is first in the queue.
   // returns patient with no ID if queue is empty

   int i;  patient p;
   if (NumberOfPatients == 0) {
   // queue is empty
   strcpy(p.ID,"");
   return p;}
   // get first patient
   p = List[0];
   // move all remaining patients one position forward in queue
   NumberOfPatients--;
   for (i=0; i<NumberOfPatients; i++)
   {
      List[i] = List[i+1];
   }
   // return patient
   return p;
}


int queue::RemoveDeadPatient (patient * p)
{
   // removes a patient from queue.
   // returns 1 if successful, 0 if patient not found
   int i, j, found = 0;
   // search for patient
   for (i=0; i<NumberOfPatients; i++)
	{
		if (stricmp(List[i].ID, p->ID) == 0)
		{
		// patient found in queue
		*p = List[i];  found = 1;
		// move all following patients one position forward in queue
		NumberOfPatients--;
			for (j=i; j<NumberOfPatients; j++)
				{
					List[j] = List[j+1];
				}
		}
	}
   return found;
}


void queue::OutputList (void)
{
   // lists entire queue on screen
   int i;
   if (NumberOfPatients == 0)
	{
		cout << "Queue is empty";
	}
   else
	{

		for (i=0; i<NumberOfPatients; i++)
		{
			cout << "" << List[i].FirstName;
			cout << " " << List[i].LastName;
			cout << " " << List[i].ID;
		}
	}
}


// declare functions used by main:

patient InputPatient (void)
{
   // this function asks user for patient data.
   patient p;
   cout << "Please enter data for new patient First name:\n ";
   cin.getline(p.FirstName, sizeof(p.FirstName));
   cout << "Last name:\n ";
   cin.getline(p.LastName, sizeof(p.LastName));
   cout << "Age:\n ";
   cin.getline(p.ID, sizeof(p.ID));
   // check if data valid
   if (p.FirstName[0]==0 || p.LastName[0]==0 || p.ID[0]==0)
	{
		// rejected
		strcpy(p.ID,"");
		cout <<"Error: Data not valid. Operation cancelled.\n";
		getch();
	}
   return p;
}


void OutputPatient (patient * p)
{
   // this function outputs patient data to the screen
   if (p == NULL || p->ID[0]==0)
	{
		cout << "No patient\n";
		return;
	}
   else
   cout << "Patient data:";
   cout << "First name: " << p->FirstName;
   cout << "Last name: " << p->LastName;
   cout << "Age:" << p->ID;
}


int ReadNumber()
{
   // this function reads an integer number from the keyboard.
   // it is used because input with cin >> doesn't work properly!
   char buffer[20];
   cin.getline(buffer, sizeof(buffer));
   return atoi(buffer);
}


void DepartmentMenu (queue * q)
{
   // this function defines the user interface with menu for one department
   int choice = 0, success; patient p;
   while (choice != 6)
	{
	   // clear screen
	   clrscr();
	   // print menu
	   cout << "Welcome to department:\n " << q->DepartmentName;
	   cout << "Please enter your choice:\n";
	   cout << "1:  Add normal patient\n";
	   cout << "2:  Add critically ill patient\n";
	   cout << "3:  Take out patient for operation\n";
	   cout << "4:  Remove dead patient from queue\n";
	   cout << "5:  List queue\n";
	   cout << "6:  Change department or exit\n";
	   // get user choice
	   choice = ReadNumber();
		// do indicated action
	switch (choice)
	  {
		case 1:   // Add normal patient
		p = InputPatient();
		if (p.ID[0])
		   {
			success = q->AddPatientAtEnd(p);
			clrscr();
			  if (success)
			    {
				cout << "Patient added:\n";

			    }
		else
		  {
			// error
			cout << "Error: The queue is full. Cannot add patient:\n";
		   }
			OutputPatient(&p);
			cout << "Press any key";
			getch();
	  }
	 break;

      case 2:   // Add critically ill patient
	 p = InputPatient();
	 if (p.ID[0])
	     {
		success = q->AddPatientAtBeginning(p);
		clrscr();
		  if (success)
			{
			  cout << "Patient added:\n";
			}
		  else
			{
			  // error
			  cout << "Error: The queue is full. Cannot add patient:\n";
			}

			  OutputPatient(&p);
			  cout << "Press any key";
			  getch();
	     }
	 break;

      case 3:   // Take out patient for operation
	 p = q->GetNextPatient();
	 clrscr();
	 if (p.ID[0])
	    {
	       cout << "Patient to operate:\n";
	       OutputPatient(&p);}
	 else
	    {
	       cout << "There is no patient to operate.\n";
	    }
	       cout << "Press any key\n";
	       getch();
	       break;

      case 4:   // Remove dead patient from queue
	 p = InputPatient();
	 if (p.ID[0])
	   {
		success = q->RemoveDeadPatient(&p);
		clrscr();
		  if (success)
		      {
			cout << "Patient removed:\n";
		      }
		  else
		      {
			// error
			cout << "Error: Cannot find patient:\n";
		      }
		OutputPatient(&p);
		cout << "Press any key\n";
		getch();
	   }
	 break;

      case 5:   // List queue
	 clrscr();
	 q->OutputList();
	 cout << "Press any key\n";
	 getch();  break;
	 }
      }
}
void printMsg()
{
    // auto detection
    int gdriver = DETECT,gmode,i;

    // initialize graphics mode
    initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");


    for (i=3; i<7; i++)
    {
	// setcolor of cursor
		setbkcolor(2);
		setcolor(1);
	// set text style as
	// settextstyle(font, orientation, size)
	settextstyle(i,0,i);

	// print text at coordinate x,y;
	outtextxy(100,20*i,"50-50 HOSPITAL");

	delay(500);
	}

    cout <<" \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                 |||Enhancing LIFE, Excelling in care  ||||| \n";
    cout<<" \n\n\n\n\n\n                                           REDIRECTING TO OUR MAIN PAGE";
     for( i=0;i<5;i++){
			 cout<<'.';
			 }
    delay(2000);

  // cout<< "  << Enhancing LIFE, Excelling in care   >>";

}

// main function defining queues and main menu
void main ()
{   printMsg();
    clrscr();
    int i, MenuChoice = 0;
   // define three queues
   queue departments[3];
   // set department names
   strcpy (departments[0].DepartmentName, "HEART SURGERY\n");
   strcpy (departments[1].DepartmentName, "PLASTIC SURGERY\n");
   strcpy (departments[2].DepartmentName, "LUNG SURGERY\n");
  // strcpy (departments[3].DepartmentName, "Skin and Dermatology\n");
  // strcpy (departments[4].DepartmentName, "Gynecologist\n");
  //  strcpy (departments[5].DepartmentName, "EMERGENCY(RED ALERT)\n");


   while (MenuChoice != 4)
	{

	   // clear screen
	   clrscr();


	   // print menu

	   cout<<"-------------------------------------------------------------------------------\n";
	   cout<<"-------------------------------------------------------------------------------\n";
	   cout<<"-------------------------------------------------------------------------------\n";
	   cout<<"*************************** WELCOME TO 50-50 HOSPITAL**************************\n";
	   cout<<"-------------------------------------------------------------------------------\n";
	   cout<<"-------------------------------------------------------------------------------\n";
	   cout<<"-------------------------------------------------------------------------------\n";
	   cout << "Please enter your choice:\n";

	  for (i = 0; i < 3; i++)
		{
		   // write menu item for department i
		   cout << "" << (i+1) << ":  " << departments[i].DepartmentName;
		}
	  cout << "4:  Exit\n";
	  // get user choice
	  MenuChoice = ReadNumber();
	  // is it a department name?
		if (MenuChoice >= 1 && MenuChoice <= 3)
		    {
		    gotoxy(40,40);
		    cout<<"                                Please Wait";
		    for(int i=0;i<5;i++){
			 cout<<'.';
			 delay(1000);
			 }
			// call submenu for department
			// (using pointer arithmetics here:)
			DepartmentMenu (departments + (MenuChoice-1));
		    }
	}

}
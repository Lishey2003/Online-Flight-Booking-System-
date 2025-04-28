#include <iostream>
#include <stack>
using namespace std;

const int MAX_P = 5;
void displayTitle()
{
    cout << "=====================================" << endl;
    cout << "       FLIGHT BOOKING SYSTEM         " << endl;
    cout << "=====================================\n"
         << endl;
}

struct Flight
{
    string FlightName;
    string ArrivalTime;
    string DepartureTime;
    string source;
    string destination;
    int ticketPrice;
    int seatAllocation[MAX_P];
    int rare;
    int front;
    int seatsAvailable;
    Flight *next;

    Flight(string FlightName, string ArrivalTime, string DepartureTime, string source, string destination, int ticketPrice)
    {
        this->FlightName = FlightName;
        this->ArrivalTime = ArrivalTime;
        this->DepartureTime = DepartureTime;
        this->source = source;
        this->destination = destination;
        this->ticketPrice = ticketPrice;
        next = NULL;
        seatsAvailable = MAX_P;
        rare = front = -1;

        for (int i = 1; i <= MAX_P; i++)
        {
            EnqueueSeat(i);
        }
    }

    void EnqueueSeat(int data)
    {
        if (rare == MAX_P - 1)
        {
            seatsAvailable = 0;
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }
            rare++;
            seatAllocation[rare] = data;
        }
    }

    int DequeueSeat()
    {
        if (front == -1)
        {
            cout << "Queue underflow : " << endl;
            return 0;
        }
        int v = seatAllocation[front];
        if (front == rare)
        {
            front = rare = -1;
        }
        else
        {

            front++;
        }
        seatsAvailable--;
        return v;
    }
};

struct BSTFlightNode
{
    Flight *flight;
    BSTFlightNode *left;
    BSTFlightNode *right;

    BSTFlightNode(Flight *flight)
    {
        this->flight = flight;
        left = right = NULL;
    }
};

BSTFlightNode *InsertTree(BSTFlightNode *root, Flight *flight)
{
    if (root == NULL)
    {
        return new BSTFlightNode(flight);
    }
    if (flight->DepartureTime < root->flight->DepartureTime)
    {
        root->left = InsertTree(root->left, flight);
    }
    else
    {
        root->right = InsertTree(root->right, flight);
    }
    return root;
}

void inorder(BSTFlightNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << "--------------------------------------" << endl;
    cout << "Flight Name : " << root->flight->FlightName << endl;
    cout << "Source : " << root->flight->source << endl;
    cout << "Destination : " << root->flight->destination << endl;
    cout << "Departure Time : " << root->flight->DepartureTime << endl;
    cout << "Arrival Time : " << root->flight->ArrivalTime << endl;
    cout << "Ticket Price : " << root->flight->ticketPrice << endl;
    cout << "Seats Available : " << root->flight->seatsAvailable << endl;
    cout << "--------------------------------------" << endl;
    inorder(root->right);
}

class FlightList
{

private:
    Flight *head;
    BSTFlightNode *root;

public:
    FlightList()
    {
        head = NULL;
        root = NULL;
    }

    void InsertFlightAtEnd(string FlightName, string ArrivalTime, string DepartureTime, string source, string destination, int ticketPrice)
    {

        Flight *NewFlight = new Flight(FlightName, ArrivalTime, DepartureTime, source, destination, ticketPrice);
        if (head == NULL)
        {
            head = NewFlight;
            root = InsertTree(root, NewFlight);
            return;
        }
        Flight *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NewFlight;
        InsertTree(root, NewFlight);
    }

    bool displayDesiredFlights(string source, string destination)
    {
        Flight *temp = head;
        bool status = false;
        while (temp != NULL)
        {
            if (temp->destination == destination && temp->source == source)
            {
                cout << "--------------------------------------" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Flight Name : " << temp->FlightName << endl;
                cout << "Source : " << temp->source << endl;
                cout << "Destination : " << temp->destination << endl;
                cout << "Departure Time : " << temp->DepartureTime << endl;
                cout << "Arrival Time : " << temp->ArrivalTime << endl;
                cout << "Ticket Price : " << temp->ticketPrice << endl;
                cout << "Seats Available : " << temp->seatsAvailable << endl;
                cout << "--------------------------------------" << endl;
                cout << "--------------------------------------" << endl;
                status = true;
            }
            temp = temp->next;
        }
        if (status == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void DisplayAllFlights()
    {
        Flight *temp = head;
        while (temp != nullptr)
        {
            cout << "--------------------------------------" << endl;
            cout << "Flight Name : " << temp->FlightName << endl;
            cout << "Source : " << temp->source << endl;
            cout << "Destination : " << temp->destination << endl;
            cout << "Departure Time : " << temp->DepartureTime << endl;
            cout << "Arrival Time : " << temp->ArrivalTime << endl;
            cout << "Seats Avaialble : " << temp->seatsAvailable << endl;
            cout << "Ticket Price : " << temp->ticketPrice << endl;
            cout << "--------------------------------------" << endl;
            temp = temp->next;
        }
    }

    Flight *getHead()
    {
        return head;
    }

    BSTFlightNode *getRoot()
    {
        return root;
    }
};

struct Booking
{
    string FullName;
    string FlightName;
    string source;
    string destination;
    int seats;
    int *seatNo;
    int Fare;
    string bookingStatus;
    Booking *next;

    Booking(string FullName, string FlightName, string source, string destination, int seats, FlightList &flightlist)
    {
        this->FullName = FullName;
        this->FlightName = FlightName;
        this->destination = destination;
        this->source = source;
        this->seats = seats;
        seatNo = new int[seats];
        bookingStatus = "Booked";
        Flight *temp = flightlist.getHead();
        while (temp != NULL)
        {
            if (temp->FlightName == FlightName && temp->destination == destination && temp->source == source)
            {
                for (int i = 0; i < seats; i++)
                {
                    seatNo[i] = temp->DequeueSeat();
                }
                Fare = seats * temp->ticketPrice;
                break;
            }
            temp = temp->next;
        }
        next = NULL;
    }
};

class BookingList
{

private:
    Booking *head;
    stack<Booking *> canceledBookings;

public:
    BookingList()
    {
        head = NULL;
    }

    void addBooking(string FullName, string FlightName, string source, string destination, int seats, FlightList &flightlist)
    {
        Flight *temp = flightlist.getHead();
        while (temp != NULL)
        {
            if (temp->FlightName == FlightName && temp->source == source && temp->destination == destination)
            {

                if (temp->seatsAvailable < seats)
                {
                    cout << "No more seats available! you can not book this flight :" << endl;
                    return;
                }
            }
            temp = temp->next;
        }

        Booking *newBooking = new Booking(FullName, FlightName, source, destination, seats, flightlist);
        if (head == NULL)
        {
            head = newBooking;
        }
        else
        {
            Booking *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newBooking;
        }
        cout << "Booked Successfully : " << endl;
    }

    void CancelBooking(string FullName, string FlightName, string source, string destination, FlightList &flightlist)
    {
        if (head == NULL)
        {
            cout << "No bookings to cancel!" << endl;
            return;
        }

        Booking *temp = head;
        Flight *tmp = flightlist.getHead();

        while (temp != NULL)
        {
            if (temp->FullName == FullName && temp->FlightName == FlightName && temp->source == source && temp->destination == destination)
            {

                while (tmp != NULL)
                {

                    if (tmp->FlightName == FlightName && tmp->source == source && tmp->destination == destination)
                    {

                        for (int i = 0; i < temp->seats; i++)
                        {
                            tmp->EnqueueSeat(temp->seatNo[i]);
                            tmp->seatsAvailable++;
                        }
                        break;
                    }
                    tmp = tmp->next;
                }
                temp->bookingStatus = "Cancelled";
                cout << "Booking Cancelled Successfully : " << endl;
                canceledBookings.push(temp);
                return;
            }
            temp = temp->next;
        }

        cout << "Booking Not Found!" << endl;
    }

    void history(FlightList &flightlist)
    {
        Booking *temp = head;
        while (temp != NULL)
        {
            cout << "--------------------------------------" << endl;
            cout << "--------------------------------------" << endl;
            cout << "Full Name : " << temp->FullName << endl;
            cout << "Flight Name : " << temp->FlightName << endl;
            cout << "Source : " << temp->source << endl;
            cout << "Destination : " << temp->destination << endl;
            Flight *tmp;
            tmp = flightlist.getHead();
            while (tmp != NULL)
            {
                if (tmp->FlightName == temp->FlightName && tmp->destination == temp->destination && tmp->source == temp->source)
                {
                    cout << "--------------------------------------" << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "Flight Name : " << temp->FlightName << endl;
                    cout << "Departure Time : " << tmp->DepartureTime << endl;
                    cout << "Arrival Time : " << tmp->ArrivalTime << endl;
                    cout << " Total Seats Booked : " << temp->seats << endl;
                    for (int i = 0; i < temp->seats; i++)
                    {
                        cout << "Seat No : " << temp->seatNo[i] << " Booked : " << endl;
                    }
                    cout << "Total Charges : " << temp->Fare << endl;
                    ;
                    cout << "Booking Status : " << temp->bookingStatus << endl;
                    cout << "--------------------------------------" << endl;
                    cout << "--------------------------------------" << endl;
                    break;
                }
                tmp = tmp->next;
            }
            temp = temp->next;
        }
    }

    void UndoRecentCancelBooking()
    {

        if (canceledBookings.empty())
        {
            cout << "No cancellation to undo!" << endl;
            return;
        }

        Booking *temp = canceledBookings.top();
        temp->bookingStatus = "Booked";
        canceledBookings.pop();
        cout << "Undo Recent cancelation : " << endl;
    }
};

struct User
{

    string FullName;
    string PhoneNo;
    string Nationality;
    string PassPortNo;
    string Password;
    BookingList *bookinglist;
    User *next;

    User()
    {
        next = NULL;
    }

    User(string FullName, string PhoneNo, string Nationality, string PassPortNo, string Password)
    {
        this->FullName = FullName;
        this->PhoneNo = PhoneNo;
        this->Nationality = Nationality;
        this->PassPortNo = PassPortNo;
        this->Password = Password;
        bookinglist = new BookingList();
        next = NULL;
    }
};

class UserList
{
private:
    User *head;

public:
    UserList()
    {
        head = NULL;
    }

    void InsertUserAtEnd(string FullName, string PhoneNo, string Nationality, string PassPortNo, string Password)
    {
        User *NewUser = new User(FullName, PhoneNo, Nationality, PassPortNo, Password);
        if (head == NULL)
        {
            head = NewUser;
            return;
        }
        User *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NewUser;
    }

    User *LoginUser(string FullName, string Password)
    {
        User *temp = head;
        while (temp != nullptr)
        {
            if (temp->FullName == FullName && temp->Password == Password)
            {
                cout << "Login Successfully : " << endl;
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
};

int main()
{

    int choice;
    string FullName;
    string PhoneNo;
    string Nationality;
    string PassPortNo;
    string Password;
    string FlightName;
    string ArrivalTime;
    string DepartureTime;
    string source;
    string destination;
    int ticketPrice;
    int select;
    int seats;
    User *user;
    UserList userlist;
    FlightList flightlist;
    BookingList *bookinglist;
    do
    {
        displayTitle();
        cout << "1.   Admin " << endl;
        cout << "2.   User " << endl;
        cout << "3.   Exit  " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            do
            {
                system("Clear");
                cout << "Enter Flight Name : " << endl;
                cin >> FlightName;
                cout << "Enter Flight Arrival Time : " << endl;
                cin >> ArrivalTime;
                cout << "Enter Flight Departure Time : " << endl;
                cin >> DepartureTime;
                cout << "Enter Source : " << endl;
                cin >> source;
                cout << "Enter Destination : " << endl;
                cin >> destination;
                cout << "Enter Flight Ticket Price : " << endl;
                cin >> ticketPrice;
                flightlist.InsertFlightAtEnd(FlightName, ArrivalTime, DepartureTime, source, destination, ticketPrice);
                cout << "Flight Added Successfully : " << endl;
                cout << "Do you want to add another Flight ? " << endl;
                cout << "1. Yes " << endl;
                cout << "2. NO " << endl;
                cin >> choice;
            } while (choice == 1);
            break;

        case 2:

            do
            {
                system("Clear");
                cout << "1. Create Account " << endl;
                cout << "2. Login " << endl;
                cout << "3. Back " << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    system("clear");
                    cout << "Enter Full Name : " << endl;
                    cin >> FullName;
                    cout << "Enter Phone Number : " << endl;
                    cin >> PhoneNo;
                    cout << "Enter Nationality : " << endl;
                    cin >> Nationality;
                    cout << "Enter Pass Port Number : " << endl;
                    cin >> PassPortNo;
                    cout << "Enter Password : " << endl;
                    cin >> Password;
                    userlist.InsertUserAtEnd(FullName, PhoneNo, Nationality, PassPortNo, Password);
                    cout << "Account Created Successfully : " << endl;
                    break;

                case 2:
                    system("clear");
                    cout << "Enter Full Name : " << endl;
                    cin >> FullName;
                    cout << "Enter Password : " << endl;
                    cin >> Password;
                    user = userlist.LoginUser(FullName, Password);
                    if (user != NULL)
                    {
                        system("Clear");

                        do
                        {

                            cout << "1. Display All Flights " << endl;
                            cout << "2. Flight based on urgent Departure " << endl;
                            cout << "3. Expensive Flight " << endl;
                            cout << "4. cheapest Flight " << endl;
                            cout << "5. Booking Flight " << endl;
                            cout << "6. Cancel Flight  " << endl;
                            cout << "7. Undo Recent Cancelation  " << endl;
                            cout << "8. history " << endl;
                            cout << "9. Back " << endl;
                            cin >> choice;
                            switch (choice)
                            {
                            case 1:
                                system("Clear");
                                flightlist.DisplayAllFlights();
                                break;

                            case 2:
                                system("Clear");
                                inorder(flightlist.getRoot());
                                break;

                            case 3:

                                break;

                            case 4:
                                break;

                            case 5:
                                system("Clear");
                                cout << "Enter Source : " << endl;
                                cin >> source;
                                cout << "Enter Destination : " << endl;
                                cin >> destination;
                                if (flightlist.displayDesiredFlights(source, destination) == true)
                                {
                                    cout << "D you want to Book a flight ?" << endl;
                                    cout << "1. yes " << endl;
                                    cout << "2. No " << endl;
                                    cin >> select;
                                    if (select == 1)
                                    {
                                        cout << "For Booking Enter Given Details :  " << endl;
                                        cout << "Enter Full Name : " << endl;
                                        cin >> FullName;
                                        cout << "Enter Flight name which you want : " << endl;
                                        cin >> FlightName;
                                        cout << "Enter Source : " << endl;
                                        cin >> source;
                                        cout << "Enter Destination : " << endl;
                                        cin >> destination;
                                        cout << "How many tickets you wants ? " << endl;
                                        cin >> seats;
                                        user->bookinglist->addBooking(FullName, FlightName, source, destination, seats, flightlist);
                                    }
                                }
                                else
                                {
                                    cout << "No Such Flight Exist : " << endl;
                                }
                                break;

                            case 6:
                                system("Clear");
                                cout << "For Cancel Booking Enter Given Details :  " << endl;
                                cout << "Enter Full Name : " << endl;
                                cin >> FullName;
                                cout << "Enter Flight name which you want : " << endl;
                                cin >> FlightName;
                                cout << "Enter Source : " << endl;
                                cin >> source;
                                cout << "Enter Destination : " << endl;
                                cin >> destination;
                                user->bookinglist->CancelBooking(FullName, FlightName, source, destination, flightlist);
                                break;

                            case 7:
                                system("Clear");
                                user->bookinglist->UndoRecentCancelBooking();
                                break;

                            case 8:
                                system("Clear");
                                user->bookinglist->history(flightlist);
                                break;

                            case 9:

                                break;

                            default:
                                cout << "Invalid choice! Try again.\n";
                                system("clear");
                            }
                            system("pause");
                            system("Clear");
                        } while (choice != 9);
                    }
                    else
                    {
                        cout << "Not Login : Try Again : " << endl;
                    }

                    break;

                case 3:

                    break;

                default:
                    cout << "Invalid choice! Try again.\n";
                    system("clear");
                }

            } while (choice != 3);

            break;

        case 3:
            cout << "\nExiting... Thank you!\n";
            return 0;
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
        system("Clear");
    } while (true);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTURE DECLARATION
struct ADMIN
{
    int adminId;
    char firstName[20];
    char lastName[20];
    char gender[6];
    int password;
} Adm;

struct CLIENTFLIGHT
{
    char from[20];
    char to[20];
    char date[12];
    int flightId;
    int seat;
} cltFlt;

struct CLIENT
{
    int passportNbr;
    char firstName[20];
    char lastName[20];
    char gender[20];
    char nationality[20];
    int password;
    int balance;
    int takenSeats;

    // Declare structure variable of clientflight
    struct CLIENTFLIGHT flight[100];
} clt;

struct FLIGHT
{
    int flightId;
    char from[20];
    char to[20];
    char date[12];
    char airplaneModel[20];
    int nbrOfSeats;
    int countSeat;
    int takenSeats[100];
    int price;

    // Declare sturcture variable of client
    struct CLIENT client[100];
} flt;

// GLOBAL VARIABLES
char tabs[8] = "\t\t\t";
int isAdminLoggedIn = 0;
int isClientLoggedIn = 0;
char *message = "";

// FUNCTION DECLARATION
void displayHeader(void);

// ADMIN FUNCTIONS
void displayAdminMenus(void);
void checkAdminCredential(void);
void initAdminCredential(void);
void displayFlightMenus(void);
void addFlight(void);
void viewFlight(void);
void viewParticularFlight(void);
void searchFlight(void);
void addMoneyToClient(void);

// CLIENT FUNCTIONS
void clientSide(void);
void createClientCredential(void);
void checkClientCredential(void);
void displayClientMenus(void);
void booking(void);
void updateClient(struct CLIENT client);
void checkBalance(void);
void bookingProcess(struct FLIGHT flight, struct CLIENT client, int nOfSeat);
void updateFlight(struct FLIGHT flight);
void historyClient(void);

int main()
{
    int choice, tried = 0;

    do
    {
       if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // clear out previous message
            printf("\n%sPlease enter your choice from below <1-3>\n\n", tabs);
            printf("%s1. Continue as Admin\n", tabs);
            printf("%s2. Continue as Client\n", tabs);
            printf("%s3. Exit program\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            tried = 0;
            checkAdminCredential();
            break;
        case 2:
            tried = 0;
            clientSide();
            break;
        case 3:
            printf("\n\n%s..Exit program..\n\n", tabs);
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 3);
}

// FUNCTION DEFINE

// Header function
void displayHeader(void)
{
    printf("=============================================================================================\n");
    printf("|                                                                                           |\n");
    printf("|                                AIRPLANE RESERVATION SYSTEM                                |\n");
    printf("|                                                                                           |\n");
    printf("=============================================================================================\n");
}

void initAdminCredential(void)
{
    FILE *adminFile;
    adminFile = fopen("admin.txt", "w");

    strcpy(Adm.firstName, "Mugabe");
    strcpy(Adm.lastName, "Chris");
    strcpy(Adm.gender, "male");
    Adm.adminId = 2020;
    Adm.password = 123;

    fwrite(&Adm, sizeof(struct ADMIN), 1, adminFile);
    fclose(adminFile);
}

void checkAdminCredential(void)
{
    int pass, admId, realAdmId, realPassword, attempts = 3;
    FILE *adminFile;

    adminFile = fopen("admin.txt", "r");

    if (adminFile == NULL)
    {
        fclose(adminFile);
        initAdminCredential();
    }
    else
    {
        fread(&Adm, sizeof(struct ADMIN), 1, adminFile);
        fclose(adminFile);
    }

    realPassword = Adm.password;
    realAdmId = Adm.adminId;

    printf("\n%sTo continue as admin\n", tabs);

    do
    {
        if (attempts != 3)
            printf("\n%sTry Again\n", tabs);

        printf("\n%s\tEnter AdminId: ", tabs);
        scanf("%d", &admId);

        printf("\n%s\tEnter Password: ", tabs);
        scanf("%d", &pass);

        if (admId == realAdmId && pass == realPassword)
            isAdminLoggedIn = 1;
        else
            attempts--;

    } while (attempts != 0 && isAdminLoggedIn != 1);

    if (isAdminLoggedIn == 1)
    {
        message = "..You have successfully Logged In..";
        displayAdminMenus();
    }
    else
    {
        message = "..Too many attemps, try again later..";
    }
}

void displayAdminMenus(void)
{
    int choice, tried = 0;

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // clear out previous message
            printf("\n%s             ADMIN DASHBOARD             ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);
            printf("\n%sPlease enter your choice from below <1-4>\n\n", tabs);
            printf("%s1. Flight\n", tabs);
            printf("%s2. Add money to a user account\n", tabs);
            printf("%s3. Logout\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            tried = 0;
            displayFlightMenus();
            break;
        case 2:
            tried = 0;
            addMoneyToClient();
            break;
        case 3:
            isAdminLoggedIn = 0;
            message = "..You have successfully logged out..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 3);
}

void displayFlightMenus(void)
{
    int choice, tried = 0;
    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // clear out previous message
            printf("\n%s         ADMIN DASHBOARD - FLIGHT        ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);
            printf("\n%sPlease enter your choice from below <1-4>\n\n", tabs);
            printf("%s1. Add Flight\n", tabs);
            printf("%s2. view Flight\n", tabs);
            printf("%s3. Search Flight\n", tabs);
            printf("%s4. Back to the dashboard\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            tried = 0;
            addFlight();
            break;
        case 2:
            tried = 0;
            viewFlight();
            break;
        case 3:
            tried = 0;
            searchFlight();
            break;
        case 4:
            message = "..Back to the dashboard..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 4);
}

void addFlight(void)
{
    int newId = 999;
    FILE *flightFile;
    flightFile = fopen("flight.txt", "a+");

    // For getting id of last flight
    while (fread(&flt, sizeof(struct FLIGHT), 1, flightFile))
    {
        newId = flt.flightId;
    }

    flt.flightId = newId + 1;

    printf("\n%sFill out the information below about Flight", tabs);
    printf("\n%s-------------------------------------------", tabs);

    printf("\n\n%sEnter starting point: ", tabs);
    scanf("%s", flt.from);
    printf("%sEnter destination: ", tabs);
    scanf("%s", flt.to);
    printf("%sEnter airplane model: ", tabs);
    scanf("%s", flt.airplaneModel);
    printf("%sEnter Price: ", tabs);
    scanf("%d", &flt.price);
    printf("%sEnter number of seats: ", tabs);
    scanf("%d", &flt.nbrOfSeats);
    printf("%sEnter date: ", tabs);
    scanf("%s", flt.date);
    flt.countSeat = 0;
    fwrite(&flt, sizeof(struct FLIGHT), 1, flightFile);

    message = "..You have successfully added Flight..";

    fclose(flightFile);
}

void viewFlight(void)
{
    int choice, tried = 0;
    FILE *flightFile;
    flightFile = fopen("flight.txt", "r");

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // clear out previous message

            printf("\n%s               VIEW FLIGHTS             ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);

            printf("\nFlightId\t    From    \t    TO    \tAirplaneModel\tNumberOfSeats\t    Date    ", tabs);
            printf("\n--------\t------------\t----------\t-------------\t-------------\t------------\n", tabs);

            // Displaying all flights
            while (fread(&flt, sizeof(struct FLIGHT), 1, flightFile))
            {
                printf("  %d\t\t  %s\t   %s\t  %s\t  %d\t\t   %s\n", flt.flightId, flt.from, flt.to, flt.airplaneModel, flt.nbrOfSeats, flt.date);
            }

            printf("\n\n%sPlease enter your choice from below <1-2>\n\n", tabs);
            printf("%s1. To see information about particular flight\n", tabs);
            printf("%s2. Back to the Flight menus\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        fclose(flightFile);

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewParticularFlight();
            choice = 2; // Back to the Flight menus
            break;
        case 2:
            tried = 0;
            message = "..Back to the Flight menus..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 2);
}

void viewParticularFlight(void)
{
    int flightId, choice, tried = 0, found = 0, column = 0, seat = 0, row = 0, foundSeat;

    FILE *flightFile;
    struct FLIGHT flight;
    flightFile = fopen("flight.txt", "r");

    printf("\n%sEnter Flight ID: ", tabs);
    scanf("%d", &flightId);

    system("cls");
    displayHeader();

    // Search for flight with Id that user has entered

    while (fread(&flight, sizeof(struct FLIGHT), 1, flightFile))
    {
        if (flight.flightId == flightId)
        {
            found = 1;
            flt = flight;
        }
    }

    if (found == 0)
    {
        printf("\n%s..We couldn't find Flight with ID %d..\n", tabs, flightId);
    }
    else
    {
        printf("\n%sFLIGHT DETAILS\n%s--------------\n\n", tabs, tabs);
        printf("%sFLIGHT ID: %d\n", tabs, flt.flightId);
        printf("%sFLIGHT STARTING POINT: %s\n", tabs, flt.from);
        printf("%sFLIGHT DESTINATION: %s\n", tabs, flt.to);
        printf("%sFLIGHT AIRPLANE MODEL: %s\n", tabs, flt.airplaneModel);
        printf("%sFLIGHT PRICE: %d\n", tabs, flt.price);
        printf("%sFLIGHT NUMBER OF SEATS: %d\n", tabs, flt.nbrOfSeats);
        printf("%sFLIGHT DATE: %s\n", tabs, flt.date);

        printf("\n%sFLIGHT PASSENGERS\n%s-----------------\n\n", tabs, tabs);

        // Checking if there's any Passenger(Atleast one)
        if (flt.countSeat != 0)
        {
            for (int i = 0; i < flt.countSeat; i++)
            {
                printf("%s|%s %s (%s)\n", tabs, flt.client[i].firstName, flt.client[i].lastName, flt.client[i].nationality);
            }
        }
        else
        {
            printf("%s..We couldn't find any passenger..\n", tabs);
        }

        printf("\n%sFLIGHT SEATS\n%s------------\n\n", tabs, tabs);

        printf("%s", tabs);

        // Arrange seats with 3 column (4 seats on each column) and rows (4 lines on each row)

        for (int i = 1; i <= flt.nbrOfSeats; i++)
        {
            foundSeat = 0;

            if (seat == 4)
            {
                seat = 0;
                column++;
                printf("\t");
            }

            if (column == 3)
            {
                column = 0;
                row++;
                printf("\n%s", tabs);
            }

            if (row == 4)
            {
                row = 0;
                printf("\n%s", tabs);
            }

            // Check if I is found in takenSeats
            for (int j = 0; j < flt.countSeat; j++)
            {
                if (flt.takenSeats[j] == i)
                {
                    foundSeat = 1;
                    break;
                }
            }

            if (foundSeat == 1)
            {
                printf("XXX ");
            }

            else
            {
                if (i < 10)
                    printf("00%d ", i);
                else if (i < 100)
                    printf("0%d ", i);
                else
                    printf("%d ", i);
            }
            seat++;
        }
    }

    do
    {
        if (tried == 0)
            printf("\n\n%sPress 0 to go back: ", tabs);
        else
            printf("\n%sWrong choice, try again: ", tabs);

        scanf("%d", &choice);

        if (choice != 0)
            tried = 1;

    } while (choice != 0);

    fclose(flightFile);
}

void searchFlight(void)
{
    int choice, tried = 0, count = 0;
    char from[20], to[20];
    FILE *flightFile;
    flightFile = fopen("flight.txt", "r");

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // Clear out previous message
            printf("\n%s             SEARCH FLIGHTS             ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);

            printf("\n%sEnter Starting point: ", tabs);
            scanf("%s", from);

            printf("\n%sEnter Destination: ", tabs);
            scanf("%s", to);

            printf("\nFlightId\t    From    \t    TO    \tAirplaneModel\tNumberOfSeats\t    Date    ", tabs);
            printf("\n--------\t------------\t----------\t-------------\t-------------\t------------\n", tabs);

            // Display flight that meets the conditions
            while (fread(&flt, sizeof(struct FLIGHT), 1, flightFile))
            {
                if (strcmp(flt.from, from) == 0 && strcmp(flt.to, to) == 0)
                {
                    count++;
                    printf("  %d\t\t  %s\t   %s\t  %s\t  %d\t\t   %s\n", flt.flightId, flt.from, flt.to, flt.airplaneModel, flt.nbrOfSeats, flt.date);
                }
            }

            if (count == 0)
                printf("\n%s..We couldn't find any Flight..\n", tabs);

            printf("\n\n%sPlease enter your choice from below <1-2>\n\n", tabs);
            printf("%s1. To see information about particular flight\n", tabs);
            printf("%s2. Back to the Flight menus\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        fclose(flightFile);

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewParticularFlight();
            choice = 2;
            break;
        case 2:
            tried = 0;
            message = "..Back to the Flight menus..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 2);
}

void addMoneyToClient(void)
{

    int passport, count = 0, amount = 0;
    FILE *clientFile;
    struct CLIENT readClt;
    clientFile = fopen("client.txt", "r");

    system("cls");
    displayHeader();
    printf("\n%s%s\n", tabs, message); // Display message
    message = "";                      // Clear out previous message

    printf("\n%s           ADD MONEY TO CLIENT           ", tabs);
    printf("\n%s-----------------------------------------\n", tabs);

    printf("\n%sEnter client passport: ", tabs);
    scanf("%d", &passport);

    printf("\n%sEnter amount: ", tabs);
    scanf("%d", &amount);

    // Try to get client structure (details) with passport that was provided
    while (fread(&readClt, sizeof(struct CLIENT), 1, clientFile))
    {
        if (readClt.passportNbr == passport)
        {
            count = 1;
            clt = readClt;
        }
    }

    fclose(clientFile);

    if (count == 0)
    {
        message = "..We couldn't find client, try again later..";
    }
    else
    {
        clt.balance += amount;
        updateClient(clt);
        message = "..Money was successful added to a client account ..";
    }
}

// CLIENT FUNCTIONS

void clientSide(void)
{
    int choice, tried = 0;

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // Clear out previous message
            printf("\n%sPlease enter your choice from below <1-3>\n\n", tabs);
            printf("%s1. Create an account\n", tabs);
            printf("%s2. login as Client\n", tabs);
            printf("%s3. Back\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            tried = 0;
            createClientCredential();
            break;
        case 2:
            tried = 0;
            checkClientCredential();
            break;
        case 3:
            message = "..Back to the main menus..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 3);
}

void createClientCredential(void)
{
    FILE *clientFile;
    clientFile = fopen("client.txt", "a+");

    printf("\n%sCreate an account\n%s-----------------\n", tabs, tabs);

    printf("%sEnter your passport: ", tabs);
    scanf("%d", &clt.passportNbr);

    printf("%sEnter firstName: ", tabs);
    scanf("%s", &clt.firstName);

    printf("%sEnter lastName: ", tabs);
    scanf("%s", &clt.lastName);

    printf("%sEnter nationality: ", tabs);
    scanf("%s", &clt.nationality);

    printf("%sEnter gender: ", tabs);
    scanf("%s", &clt.gender);

    printf("%sEnter password: ", tabs);
    scanf("%d", &clt.password);
    clt.balance = 0;
    clt.takenSeats = 0;

    fwrite(&clt, sizeof(struct CLIENT), 1, clientFile);
    message = "..Account created successful..";
    fclose(clientFile);
}

void checkClientCredential(void)
{
    int pass, passport, tried = 0;
    struct CLIENT client;

    FILE *clientFile;
    clientFile = fopen("client.txt", "r");

    printf("\n%sTo continue as Client\n", tabs);

    do
    {

        printf("\n%s\tEnter your passport: ", tabs);
        scanf("%d", &passport);

        printf("\n%s\tEnter your Password: ", tabs);
        scanf("%d", &pass);

        if (clientFile != NULL)
        {
             while (fread(&client, sizeof(struct CLIENT), 1, clientFile))
            {
                if (client.passportNbr == passport && client.password == pass)
                {
                    isClientLoggedIn = 1;
                    clt = client;
                }
                else
                {
                    tried = 1;
                }
            }
        }
        else
        {
            tried = 1;
        }

    } while (tried != 1 && isClientLoggedIn != 1);

    fclose(clientFile);

    if (isClientLoggedIn == 1)
    {
        message = "..You have successfully Logged In..";
        displayClientMenus();
    }
    else
    {
        message = "..Failed to login, Try again later..";
    }
}

void displayClientMenus(void)
{
    int choice, tried = 0;

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // Clear out previous message

            printf("\n%s             CLIENT MENU             ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);
            printf("%sWelcome dear %s %s\n\n", tabs, clt.firstName, clt.lastName);
            printf("\n%sPlease enter your choice from below <1-6>\n\n", tabs);
            printf("%s1. View Flight\n", tabs);
            printf("%s2. Search Flight\n", tabs);
            printf("%s3. Booking\n", tabs);
            printf("%s4. History\n", tabs);
            printf("%s5. Check balance\n", tabs);
            printf("%s6. Logout\n\n", tabs);
            printf("%sEnter you choice: ", tabs);
        }

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            tried = 0;
            viewFlight();
            break;
        case 2:
            tried = 0;
            searchFlight();
            break;
        case 3:
            tried = 0;
            booking();
            break;
        case 4:
            tried = 0;
            historyClient();
            break;
        case 5:
            tried = 0;
            checkBalance();
            break;
        case 6:
            isClientLoggedIn = 0;
            message = "..You have successfully logged out..";
            break;

        default:
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 6);
}

void booking(void)
{
    int flightId, nOfSeat, found = 0, choice, totPrice = 0;

    struct FLIGHT flight;
    FILE *flightFile;

    flightFile = fopen("flight.txt", "r");

    printf("\n%sBooking\n%s----------\n", tabs, tabs);
    printf("\n%sEnter Flight ID: ", tabs);
    scanf("%d", &flightId);
    printf("\n%sEnter Flight Number of seats: ", tabs);
    scanf("%d", &nOfSeat);

    // Get flight with id that user has entered
    while (fread(&flight, sizeof(struct FLIGHT), 1, flightFile))
    {
        if (flight.flightId == flightId)
        {
            found = 1;
            flt = flight;
        }
    }

    fclose(flightFile);

    if (found == 0)
    {
        message = "..We couldn't find flight, try again..";
    }
    else
    {
        totPrice = nOfSeat * flt.price;

        printf("\n%s Total price: %d\n", tabs, totPrice);

        printf("\n\n%sPlease enter your choice from below <1-2>\n\n", tabs);
        printf("%s1. Proceed booking process\n", tabs);
        printf("%s2. Back to the client menus\n\n", tabs);
        do
        {
            printf("%sEnter you choice: ", tabs);
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                if (clt.balance >= totPrice)
                    bookingProcess(flt, clt, nOfSeat);
                else
                    message = "..You don't have enough money..";
                choice = 2;
                break;
            case 2:
                message = "..Back to the client menus..";
                break;
            default:
                printf("Wrong choice, try again later");
            }
        } while (choice != 2);
    }
}

void updateClient(struct CLIENT client)
{
    FILE *tempFile, *clientFile;

    clientFile = fopen("client.txt", "r");
    tempFile = fopen("tempClient.txt", "a+");

    while (fread(&clt, sizeof(struct CLIENT), 1, clientFile))
    {
        if (clt.passportNbr == client.passportNbr)
        {
            clt = client;
        }
        fwrite(&clt, sizeof(struct CLIENT), 1, tempFile);
    }

    clt = client;

    fclose(clientFile);
    fclose(tempFile);

    remove("client.txt");
    rename("tempClient.txt", "client.txt");
}

void updateFlight(struct FLIGHT flight)
{
    FILE *tempFile, *flightFile;

    flightFile = fopen("flight.txt", "r");
    tempFile = fopen("tempflight.txt", "a+");

    while (fread(&flt, sizeof(struct FLIGHT), 1, flightFile))
    {
        if (flt.flightId == flight.flightId)
        {
            flt = flight;
        }
        fwrite(&flt, sizeof(struct FLIGHT), 1, tempFile);
    }
    flt = flight;

    fclose(flightFile);
    fclose(tempFile);
    remove("flight.txt");
    rename("tempflight.txt", "flight.txt");
}

void checkBalance(void)
{
    int choice, tried = 0;

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();
            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // Clear out previous message
            printf("\n%s             CHECK BALANCE              ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);
            printf("\n%sYour balance: %d\n", tabs, clt.balance);
            printf("\n%sPress 0 to Go back: ", tabs);
        }

        scanf("%d", &choice);

        if (choice != 0)
        {
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 0);
}

void bookingProcess(struct FLIGHT flight, struct CLIENT client, int nOfSeat)
{
    int choice, seats[nOfSeat], seat, found;

    do
    {
        system("cls");
        displayHeader();
        printf("\n%s%s\n", tabs, message); // Display message
        message = "";                      // Clear out previous message

        printf("\n%s         PROCEED BOOKING PROCESS         ", tabs);
        printf("\n%s-----------------------------------------\n", tabs);

        // Storing seats in array user has entered
        for (int i = 0; i < nOfSeat; i++)
        {
            printf("\n%sSelect seat %d: ", tabs, i + 1);
            scanf("%d", &seats[i]);
        }

        found = 0;

        // Check if there are seats that was already taken

        for (int i = 0; i < nOfSeat; i++)
        {
            seat = seats[i];

            // Check if seat is out of range
            if (seat > flight.nbrOfSeats)
            {
                found = 1;
                printf("\n%s..You've entered wrong seat, Please take other seats..\n", tabs);
                break;
            }

            for (int j = 0; j < flight.countSeat; j++)
            {

                if (flight.takenSeats[j] == seat)
                {
                    found = 1;
                    printf("\n%s..Seat you've entered is already taken,Please take other seats..\n", tabs);
                    break;
                }
            }
        }

        if (found == 1)
        {
            printf("\n%sPress 1 to try again or 0 to Go back: ", tabs);
            scanf("%d", &choice);
        }
        else
        {
            // Add client into flight passengers
            for (int j = flight.countSeat; j < flight.countSeat + nOfSeat; j++)
            {
                flight.client[j] = client;
            }

            // Add chosen seats in flight takenSeats
            for (int i = 0; i < nOfSeat; i++)
            {
                seat = seats[i];
                for (int j = flight.countSeat + i; j < flight.countSeat + i + 1; j++)
                {
                    flight.takenSeats[j] = seat;
                }
            }

            flight.countSeat += nOfSeat; // Update number of passengers in a flight

            strcpy(cltFlt.from, flight.from);
            strcpy(cltFlt.to, flight.to);
            strcpy(cltFlt.date, flight.date);

            cltFlt.flightId = flight.flightId;

            // Add flight in client history with seat number
            for (int i = 0; i < nOfSeat; i++)
            {
                seat = seats[i];
                for (int j = client.takenSeats + i; j < client.takenSeats + i + 1; j++)
                {

                    cltFlt.seat = seat;
                    client.flight[j] = cltFlt;
                }
            }

            client.takenSeats += nOfSeat;             // Udpate number of taken flights
            client.balance -= flight.price * nOfSeat; // Descrease balance of client

            updateClient(client);
            updateFlight(flight);

            choice = 0;
            message = "..You have successfully booked a flight..";
        }

    } while (choice != 0);
}

void historyClient(void)
{
    int choice, tried = 0, found = 0;

    do
    {
        if (tried == 0)
        {
            system("cls");
            displayHeader();

            printf("\n%s%s\n", tabs, message); // Display message
            message = "";                      // Clear out previous message
            printf("\n%s                HISTORY                 ", tabs);
            printf("\n%s-----------------------------------------\n", tabs);

            printf("\nFlightId\t    From    \t    TO    \tSeatNumber\t    Date    ", tabs);
            printf("\n--------\t------------\t----------\t----------\t-------------\n", tabs);

            // Check if client has taken any flight
            if (clt.takenSeats > 0)
            {

                // Display client history
                for (int i = 0; i < clt.takenSeats; i++)
                {
                    found = 1;
                    printf("  %d\t\t  %s\t   %s\t  %d\t\t   %s\n", clt.flight[i].flightId, clt.flight[i].from, clt.flight[i].to, clt.flight[i].seat, clt.flight[i].date);
                }
            }

            if (found == 0)
                printf("\n%s..We couldn't find any History for you..\n", tabs);

            printf("\n%sPress 0 to Go back: ", tabs);
        }

        scanf("%d", &choice);

        if (choice != 0)
        {
            tried = 1;
            printf("%sWrong choice, try again: ", tabs);
        }

    } while (choice != 0);
}

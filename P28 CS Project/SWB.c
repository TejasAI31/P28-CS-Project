#include "includeheaders.h"

// Function to display helpline numbers
void displayHelplineNumbers() {
    printf("%s\n\n\n\n\n\033[53CHelpline Numbers:\n%s\033[53C================\n\n\n\n%s",brightred,brightyellow,yellow);
    printf("\033[52C1.%s Hospital%s\n",brightgreen,yellow);
    printf("\033[52C2.%s Security Helpline%s\n", brightgreen,yellow);
    printf("\033[52C3.%s A.P.J Abdul Kalam Hostel%s\n", brightgreen,yellow);
    printf("\033[52C4.%s C.V Raman Hostel%s\n", brightgreen,yellow);
    printf("\033[52C5.%s Aryabhatta Hostel%s\n", brightgreen,yellow);
}

// Function to display details based on choice
void displayDetails(int choice) {

    char hospital[7][50] = { "Ambulance","Apollo Pharmacy","Medical Officer","Mr. Ravi","PIC_Medical (Dr. Saurabh Kumar)","Hospital Reception","Institute Ambulance" };
    char hospitalnumbers[7][15] = { "9264193927","7605035992","9612747626","8210893435","7321893616","06115233800"," 9508910134" };

    char securityhelpline[5][50] = { "Security Officer","Security Patrolling Vehicle","Security Supervisor (Mr. Prahlad Singh)","Security Supervisor (Mr. Hari Shankar)","Security Supervisor (Mr. T.N Sharma)" };
    char securitynumbers[5][15] = { "8340269042","9574578404","8102917508","9122171516","6202159737" };

    char kalam[10][50] = { "Warden(A & B block) (Dr.Ajay Kumar Yadav)","Warden(C & D block) (Dr.Shailesh Kumar Tiwari)","Caretaker (Mr. Sudama)","Caretaker (Mr. Sujit Tiwari)","Hostel Office(Administration) (Mr. Deep Raj)","Mess Manager(Mess 1) (Mr. Umanand)","Mess Manager(Mess 2) (Mr. Prem)","Cleaning Supervisor (Mr. Bipin)","Carpenter (Mr. Kunal)","Electrician (Mr. Kamlesh)" };
    char kalamnumbers[10][15] = { "9035552339","916123028074","6206250769","9122737307","8825236592","8789471175","9755213223","7004976395","9973359488","7481091061" };

    char cvr[6][50] = { "Warden (Dr.Chandra Shekhar Prajapati)","Caretaker (Mr. Samad)","Hostel Office(Administration) (Mr. Amit)","Hostel Office(Administration) (Mr. Anurag)","Mess Manager (Mr.Sanjeet)","CHS Cleaning Supervisor (Mr. Bipin)" };
    char cvrnumbers[6][15] = { "916115233141","9931405122","9386433912","9661699330","7002280341","7004976395" };

    char aryabhatta[7][50] = { "Warden(A1 & A2 block) (Dr.T.Rajagopala Rao)","Warden(B1 & B2 block) (Dr.Suraj Suman)","Hostel Office (Ms. Supriya)","Caretaker	(Mr. Imraan)","Caretaker (Mr. Naushad)","Cleaning Supervisor (Mr. Bipin)","Mess Manager	(Mr. Gautam Rana)" };
    char aryabhattanumbers[7][15] = { "916123028238","916115233970","9122458200","7766842737","9060075032","7004976395","8167644026" };

    printf("\n\n\n");
    switch (choice) 
    {
    case 1:
        for (int x = 0; x < 7; x++)
        {
            printf("%s%s: %s%s\n\n",brightyellow,hospital[x],brightgreen,hospitalnumbers[x]);
            Sleep(200);
        }
        break;
    case 2:
        for (int x = 0; x < 5; x++)
        {
            printf("%s%s: %s%s\n\n", brightyellow, securityhelpline[x], brightgreen, securitynumbers[x]);
            Sleep(200);
        }
        break;
    case 3:
        for (int x = 0; x < 10; x++)
        {
            printf("%s%s: %s%s\n\n", brightyellow, kalam[x], brightgreen, kalamnumbers[x]);
            Sleep(200);
        }
        break;
    case 4:
        for (int x = 0; x < 6; x++)
        {
            printf("%s%s: %s%s\n\n", brightyellow, cvr[x], brightgreen, cvrnumbers[x]);
            Sleep(200);
        }
        break;
    case 5:
        for (int x = 0; x < 7; x++)
        {
            printf("%s%s: %s%s\n\n", brightyellow, aryabhatta[x], brightgreen, aryabhattanumbers[x]);
            Sleep(200);
        }
        break;

    }
    printf("%s", white);
}

void swb()
{
    int choice;
    system("cls");
    printf("\n%s\033[60CSWB\n\033[60C===%s",cyan,white);
    displayHelplineNumbers();
    printf("\033[H");
    for (int y = 1; y <= 2; y++)
    {
        printf("%s%s", yellow, greenbkg);
        for (int x = 1; x <= 30; x++)
        {
            if (x == 23)
            {
                printf("%s%s", yellow, yellowbkg);
                if (y == 1)
                    printf("\033[14D\033[1B");
                else
                    printf("\033[1B");
            }
            printf("||              ||\033[18D\033[1B");
        }
        printf("\033[0;102H");
    }
    printf("\033[23;50H%s",defaultbkg);
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);
    system("cls");
    displayDetails(choice);
    printf("%sPress 'm' to return to mainscreen. Press 'r' to return to SWB screen\n\n",magenta);
    printf("%sEnter choice:%s",brightgreen,save);
    char returnchoice = 'p';
    while (returnchoice != 'r' && returnchoice != 'm')
    {
        printf("%s\033[0K", reset);
        returnchoice = getchar();
    }
    if (returnchoice == 'm')
        mainscreen();
    else
    {
        swb();
    }
} 
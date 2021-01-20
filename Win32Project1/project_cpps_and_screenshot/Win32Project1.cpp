// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <iostream>
#include <string>

#define MAX_LOADSTRING 100
#define ID_BUTTON 1

using namespace std;

struct userInfo
{
	int month;
	int day;
	int year;

};



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int countNumberOfLeapYears(userInfo &desiredStruct)
{
	//TotalLeapYears = MultiplesOf4 - multiplesOf100 + multiplesOf4000;

	int answer = 0;
	int multiplesOf4 = desiredStruct.year / 4;
	int multiplesOf100 = desiredStruct.year / 100;
	int multiplesOf400 = desiredStruct.year / 400;

	answer = multiplesOf4 - multiplesOf100 + multiplesOf400;

	return answer;
}

bool isSuperWDigit(wchar_t *desiredVariable)
{
	bool answer = true;
	int arrayLength = wcslen(desiredVariable);

	for (int i = 0; i < arrayLength-1; i++)
	{
		if (!iswdigit(desiredVariable[i]))
		{
			if (desiredVariable[i] != '\0')
			{
				answer = false;
				return answer;
			}
		}
	}

	return answer;
}
bool doesPassInboundsTest(userInfo desiredStruct)
{
	//Precondition: input is valid in terms of it being only integers
	bool isLeapYear = false;

	if (desiredStruct.year > 0)
	{
		if (desiredStruct.month < 13 && desiredStruct.month > 0)
		{

			if (desiredStruct.month == 1 ||
				desiredStruct.month == 3 ||
				desiredStruct.month == 5 ||
				desiredStruct.month == 7 ||
				desiredStruct.month == 8 ||
				desiredStruct.month == 10 ||
				desiredStruct.month == 12)
			{
				if (desiredStruct.day < 32) return true;
			}
			if (desiredStruct.month == 4 ||
				desiredStruct.month == 6 || 
				desiredStruct.month == 9 ||
				desiredStruct.month == 11)
			{
				if (desiredStruct.day < 31) return true;
			}
			if (desiredStruct.month == 2)
			{
				if (desiredStruct.year % 4 == 0 && desiredStruct.year % 100 != 0 || desiredStruct.year % 400 == 0 || desiredStruct.year % 1000 == 0) isLeapYear = true;

				if (isLeapYear)
				{
					if (desiredStruct.day < 30) return true;
				}
				if (!isLeapYear)
				{
					if (desiredStruct.day < 29) return true;
				}

			}
		}
	}

	return false;
}


int daysSinceOne(userInfo &desiredStruct)
{
	//Precondition: Is that userInfo is correct.

	int answer = 0;
	float leapYears = 0;
	int regularYears = 0;
	bool isLeapYear = false;

	if (desiredStruct.year % 4 == 0 && desiredStruct.year % 100 != 0 || desiredStruct.year % 400 == 0 || desiredStruct.year % 1000 == 0) isLeapYear = true;

	leapYears = countNumberOfLeapYears(desiredStruct);
	if (isLeapYear) leapYears--;								//Don't count the current leap year the latter part of the method will do that
	regularYears = desiredStruct.year - leapYears - 1;			//because 1 A.C is the offset
	answer = 366 * leapYears + 365 * regularYears;

	for (int i = 1; i < desiredStruct.month; i++)
	{
		switch (i)
		{
		case 1:
			answer += 31;
			break;
		case 2:
			if (isLeapYear == false) answer += 28;
			if (isLeapYear == true) answer += 29;
			break;
		case 3:
			answer += 31;
			break;
		case 4:
			answer += 30;
			break;
		case 5:
			answer += 31;
			break;
		case 6:
			answer += 30;
			break;
		case 7:
			answer += 31;
			break;
		case 8:
			answer += 31;
			break;
		case 9:
			answer += 30;
			break;
		case 10:
			answer += 31;
			break;
		case 11:
			answer += 30;
			break;
		}
	}

	answer += desiredStruct.day;
	answer--;

	return answer;
}

string determineWeekDay(userInfo &desiredStruct)
{
	int answer = 0, total1 = 0;
	string weekDay;
	string finalString;

	total1 = daysSinceOne(desiredStruct);

	total1 += 1;
	total1 = total1 % 7;

	switch (total1)
	{
	case 0:
		weekDay = "Sunday";
		break;
	case 1:
		weekDay = "Monday";
		break;
	case 2:
		weekDay = "Tuesday";
		break;
	case 3:
		weekDay = "Wednesday";
		break;
	case 4:
		weekDay = "Thursday";
		break;
	case 5:
		weekDay = "Friday";
		break;
	case 6:
		weekDay = "Saturday";
		break;

	}

	finalString = "You were born on a " + weekDay;

	return finalString;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//These variables need to be static or else they don't get sent to 
	static HWND myMonth = NULL, myDay, myYear;
	static wchar_t myString[100];
	int utility;
	string myStringy = "";
	wstring myWString;
	LPCWSTR windowsStringy = NULL;
	userInfo myUserInfo;
	bool errorFlag = false;

    switch (message)
    {
	case WM_CREATE:
		
		CreateWindow(TEXT("STATIC"), TEXT("Please enter the month you were born:"), WS_VISIBLE | WS_CHILD, 10, 10, 270, 20, hWnd, (HMENU) NULL, NULL, NULL);
		myMonth = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 50, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"), TEXT("Please enter the day you were born:"), WS_VISIBLE | WS_CHILD, 10, 100, 270, 20, hWnd, (HMENU)NULL, NULL, NULL);
		myDay = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 150, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"), TEXT("Please enter the year you were born:"), WS_VISIBLE | WS_CHILD, 10, 200, 270, 20, hWnd, (HMENU)NULL, NULL, NULL);
		myYear = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 250, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);

		CreateWindow(TEXT("BUTTON"), TEXT("Go!"), WS_VISIBLE | WS_CHILD, 10, 300, 125, 25, hWnd, (HMENU) ID_BUTTON, NULL, NULL);

		

		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:

			if (LOWORD(wParam) == ID_BUTTON)
			{

				// 12/1/2002
				GetWindowText(myMonth,myString, 20);
				myUserInfo.month = _wtoi(myString);
				if (!isSuperWDigit(myString)) errorFlag = true;

				GetWindowText(myDay, myString, 20);
				myUserInfo.day = _wtoi(myString);
				if (!isSuperWDigit(myString)) errorFlag = true;

				GetWindowText(myYear, myString, 20);
				myUserInfo.year = _wtoi(myString);
				if (!isSuperWDigit(myString)) errorFlag = true;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
				//At this point we are assuming it passes the digit tests, we call inboundsTest
				if (errorFlag == false)
					if (!doesPassInboundsTest(myUserInfo)) errorFlag = true;


				if(errorFlag == false) myStringy = determineWeekDay(myUserInfo);
				if (errorFlag == true) myStringy = "Invalid Input.";


				myWString = wstring(myStringy.begin(), myStringy.end());
				windowsStringy = myWString.c_str();

				CreateWindow(TEXT("STATIC"),windowsStringy, WS_VISIBLE | WS_CHILD, 10, 350, 270, 20, hWnd, (HMENU)NULL, NULL, NULL);

			}
			

            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

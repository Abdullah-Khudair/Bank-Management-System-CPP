#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
    short _Day = 0;
    short _Month = 0; 
    short _Year = 0;

public:
    static bool IsLeapYear(short Year)
    {
        return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
    }

    bool IsLeapYear() const
    {
        return IsLeapYear(_Year);   
    }

    static short NumberOfDaysInMonth(short Month, short Year)
    {
        if (Month > 12 || Month < 1) return -1;

        static short Days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : Days[Month-1];
    }

    short NumberOfDaysInMonth() const
    {
        return NumberOfDaysInMonth(_Month, _Year);
    }

    static bool IsValidYear(short Year)
    {    
        if (Year >= 1900 && Year <= 2050)
                return true;
    
        return false;
    }
    
    static bool IsValidMonth(short Month)
    {
        if (Month >= 1 && Month <= 12)
            return true;
    
        return false;
    }

    static bool IsValidDay(short Day, short Month, short Year)
    {
        if (Day >= 1 && Day <= NumberOfDaysInMonth(Month, Year))
            return true;

        return false;
    }


    clsDate()                                         // Constructor 1
    {
        time_t T = time(0);
        tm * dt = localtime(&T);

        _Year = dt->tm_year + 1900;
        _Month = dt->tm_mon + 1;
        _Day = dt->tm_mday;
    }

    clsDate(short day, short month, short year)       // Constructor 2
    {
        if (!IsValidYear(year) || !IsValidMonth(month) || !IsValidDay(day, month, year))
            throw invalid_argument("Invalid Date!");
            
        _Year = year;
        _Month = month;
        _Day = day;
    }
    
    clsDate(const string & DD_MM_YY)                  // Constructor 3
    {
        vector<string> Vec = clsString::SplitString(DD_MM_YY, "/");

        if (Vec.size() != 3)
            throw invalid_argument("Invalid Date!");

        short year = stoi(Vec[2]);
        short month = stoi(Vec[1]);
        short day = stoi(Vec[0]);

        if (!IsValidYear(year) || !IsValidMonth(month) || !IsValidDay(day, month, year))
            throw invalid_argument("Invalid Date!");

        _Year = year;
        _Month = month;
        _Day = day;
    }
    

    void Day(short day) 
    {
        if (!IsValidDay(day, _Month, _Year))
            throw invalid_argument("Invalid Day!");

        _Day = day;
    }

    void Month(short month) 
    {
        if (!IsValidMonth(month))
            throw invalid_argument("Invalid Month!");

        _Month = month;
        if (_Day > NumberOfDaysInMonth())
            _Day = NumberOfDaysInMonth();
    }
    
    void Year(short year)
    {
        if (!IsValidYear(year))
            throw invalid_argument("Invalid Year!");
        
        _Year = year;
        if (_Month == 2 && _Day == 29 && !IsLeapYear(_Year))
            _Day = 28;
    }


    short Day() const { return _Day; }
    short Month() const { return _Month; }
    short Year() const { return _Year; }


    static short NumberOfDaysInYear(short Year)
    {
        return (IsLeapYear(Year)) ? 366 : 365;
    }

    short NumberOfDaysInYear() const
    {
        return NumberOfDaysInYear(_Year);
    }

    static short NumberOfHoursInYear(short Year)
    {
        return NumberOfDaysInYear(Year) * 24;
    }

    short NumberOfHoursInYear() const
    {
        return NumberOfHoursInYear(_Year);
    }

    static int NumberOfMinutesInYear(short Year)
    {
        return NumberOfHoursInYear(Year) * 60;
    }

    int NumberOfMinutesInYear() const
    {
        return NumberOfMinutesInYear(_Year);
    }

    static int NumberOfSecondsInYear(short Year)
    {
        return NumberOfMinutesInYear(Year) * 60;
    }

    int NumberOfSecondsInYear() const
    {
        return NumberOfSecondsInYear(_Year);
    }

    static short NumberOfHoursInMonth(short Month, short Year)
    {
        return NumberOfDaysInMonth(Month, Year) * 24;
    }

    short NumberOfHoursInMonth() const
    {
        return NumberOfHoursInMonth(_Month, _Year);
    }

    static int NumberOfMinutesInMonth(short Month, short Year)
    {
        return NumberOfHoursInMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInMonth() const
    {
        return NumberOfMinutesInMonth(_Month, _Year);
    }

    static int NumberOfSecondsInMonth(short Month, short Year)
    {
        return NumberOfMinutesInMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInMonth() const
    {
        return NumberOfSecondsInMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short day, short month, short year)
    {
        if (day > NumberOfDaysInMonth(month, year) || day < 1 || month > 12 || month < 1)
            return -1;

        short a = (14 - month) / 12;
        short y = year - a;
        short m = month + 12 * a - 2;
        
        return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
    }

    static short DayOfWeekOrder(const clsDate & dt)
    {
        return DayOfWeekOrder(dt._Day, dt._Month, dt._Year);
    }

    short DayOfWeekOrder() const
    {
        return DayOfWeekOrder(*this);
    }

    static string MonthName(short Month)
    {
        if (Month > 12 || Month < 1) return "";

        const string Months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return Months[Month - 1];
    }

    string MonthName() const
    {
        return MonthName(_Month);
    }

    static string DayName(short DayOrder)
    {
        if (DayOrder > 6 || DayOrder < 0) return "";

        string Days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return Days[DayOrder];
    }

    string DayName() const
    {
        return DayName(DayOfWeekOrder());
    }

    static string GetFullDate(short Day, short Month, short Year)
    {
        return DayName(DayOfWeekOrder(Day, Month, Year)) + ", " + to_string(Day) + '/' + to_string(Month) + '/' + to_string(Year);
    }

    static string GetFullDate(const clsDate & dt)
    {
        return GetFullDate(dt._Day, dt._Month, dt._Year);
    }

    string GetFullDate() const
    {
        return GetFullDate(*this);
    }

    static void MonthCalendar(short Month, short Year)
    {
        if (Month > 12 || Month < 1) return;

        short FirstDay = DayOfWeekOrder (1, Month, Year);
        short NumberOfDays = NumberOfDaysInMonth (Month, Year);

        cout << "\n________________________" << MonthName(Month) << "________________________\n\n";
        printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");

        short count;
        for (count = 0; count < FirstDay; count++)
            printf("  \t");

        for (short i=1; i<=NumberOfDays; i++)
        {
            printf("%02d\t", i);
            if (++count == 7)
            {
                cout << endl;
                count = 0;
            }
    }
    cout << "\n___________________________________________________\n";
    }

    void MonthCalendar() const
    {
        MonthCalendar(_Month, _Year);
    }

    static void YearCalendar(short Year)
    {
        for (short i=1; i<=12; i++)
            MonthCalendar(i, Year);
    }

    void YearCalendar() const
    {
        YearCalendar(_Year);
    }

    static short NumberOfDaysFromBeginningYear(short Day, short Month, short Year)
    {
        if (Day > NumberOfDaysInMonth(Month, Year) || Day < 1 || Month > 12 || Month < 1)
            return -1;

        short Total = 0;
        for (short i = 1; i < Month; i++)
            Total += NumberOfDaysInMonth(i, Year);

        return Total + Day;
    }

    static short NumberOfDaysFromBeginningYear(const clsDate & dt)
    {
        return NumberOfDaysFromBeginningYear(dt._Day, dt._Month, dt._Year);
    }

    short NumberOfDaysFromBeginningYear() const
    {
        return NumberOfDaysFromBeginningYear(*this);
    }

    static clsDate GetDateFromDayOrderInYear(short Days, short Year)
    {
        short Month = 1;
        short Day = 1;
        short TotalDays = 0;

        while(Days > 0)
        {
            TotalDays = NumberOfDaysInMonth(Month, Year);
            if (Days > TotalDays)
            {
                Days -= TotalDays;
                if (++Month > 12)
                {
                    Month = 1;
                    ++Year;
                }
            }

            else 
            {
                Day = Days;
                break;
            }
        }
        return clsDate(Day, Month, Year);
    }

    static clsDate AddDaysToDate(short AddDays, short day, short month, short year)
    {
        short TotalDays = NumberOfDaysFromBeginningYear(day, month, year);
        TotalDays += AddDays;
        
        return GetDateFromDayOrderInYear(TotalDays, year); 
    }

    static clsDate AddDaysToDate(short AddDays, const clsDate & dt)
    {
        short TotalDays = NumberOfDaysFromBeginningYear(dt._Day, dt._Month, dt._Year);
        TotalDays += AddDays;
        
        return GetDateFromDayOrderInYear(TotalDays, dt._Year); 
    }

    void AddDaysToDate(short AddDays)
    {
        *this = AddDaysToDate(AddDays, *this);
    }

    static bool IsDate1BeforeDate2(const clsDate & Date1, const clsDate & Date2)
    {
        if (Date1._Year < Date2._Year) return true;
        if (Date1._Year > Date2._Year) return false;
        if (Date1._Month < Date2._Month) return true;
        if (Date1._Month > Date2._Month) return false;
        return Date1._Day < Date2._Day;
    }

    bool IsDate1BeforeDate2(const clsDate & Date2) const
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(const clsDate & Date1, const clsDate & Date2)
    {
        return (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day);
    }

    bool IsDate1EqualDate2(const clsDate & Date2) const
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsDate1AfterDate2(const clsDate & Date1, const clsDate & Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDate1AfterDate2(const clsDate & Date2) const
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(short day, short month, short year)
    {
        return (day == NumberOfDaysInMonth(month, year));
    }

    static bool IsLastDayInMonth(const clsDate & dt)
    {
        return IsLastDayInMonth(dt._Day, dt._Month, dt._Year);
    }

    bool IsLastDayInMonth() const
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    bool IsLastMonthInYear() const
    {
        return IsLastMonthInYear(this->_Month);
    }

    static clsDate IncreaseDateByOneDay(clsDate & Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date._Month))
            {
                Date._Day = 1;
                Date._Month = 1;
                ++Date._Year;
            }

            else
            {
                Date._Day = 1;
                ++Date._Month;
            }
        }

        else
            ++Date._Day;

        return Date;
    }

    void IncreaseDateByOneDay()
    {
        *this = IncreaseDateByOneDay(*this);
    }

    static int GetDiffrenceDaysBetweenDate1AndDate2(const clsDate & Date1, const clsDate & Date2, bool IncludeLastDay = false)
    {
        if (IsDate1AfterDate2(Date1, Date2))
            return GetDiffrenceDaysBetweenDate1AndDate2(Date2, Date1, IncludeLastDay) * -1;

        unsigned short Days = 0;
        for (short i = Date1._Year; i < Date2._Year; i++)
        {
            Days += (IsLeapYear(i)) ? 366 : 365;
        }

        Days += (NumberOfDaysFromBeginningYear(Date2) - NumberOfDaysFromBeginningYear(Date1));

        return (IncludeLastDay) ? ++Days : Days;
    }

    int GetDiffrenceDaysBetweenDate1AndDate2(const clsDate & Date2, bool IncludeLastDay = false) const
    {
        return GetDiffrenceDaysBetweenDate1AndDate2(*this, Date2, IncludeLastDay);
    }

    static int YourAgeInDays(const clsDate & Date)
    {
        return GetDiffrenceDaysBetweenDate1AndDate2(Date, clsDate());
    }

    int YourAgeInDays() const
    {
        return GetDiffrenceDaysBetweenDate1AndDate2(*this, clsDate());
    }

    static clsDate IncreaseDateByXDays(clsDate & Date, short AddDays)
    {
        for (short i=1; i<=AddDays; i++)
        {
            IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    
    void IncreaseDateByXDays(short Days)
    {
        *this = IncreaseDateByXDays(*this, Days);
    }

    static clsDate IncreaseDateByOneWeek(clsDate & Date)
    {
        IncreaseDateByXDays(Date, 7);
        return Date;
    }
    
    void IncreaseDateByOneWeek()
    {
        *this = IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate & Date, short AddWeeks)
    {
        for (short i=1; i<=AddWeeks; i++)
            IncreaseDateByOneWeek(Date);
        
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        *this = IncreaseDateByXWeeks(*this, Weeks);
    }
    
    static clsDate IncreaseDateByOneMonth(clsDate & Date)
    {
        if (IsLastMonthInYear(Date._Month))
        {
            Date._Month = 1;
            Date._Year++;
        }
    
        else
        {
            Date._Month++;
        }
    
        short MaxDaysInMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
        if (Date._Day > MaxDaysInMonth)
            Date._Day = MaxDaysInMonth;

        return Date;
    }
    
    void IncreaseDateByOneMonth()
    {
        *this = IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonth(clsDate & Date, short AddMonth)
    {
        for (short i=1; i<=AddMonth; i++)
            IncreaseDateByOneMonth(Date);

        return Date;
    }
    
    void IncreaseDateByXMonth(short Months)
    {
        *this = IncreaseDateByXMonth(*this, Months);
    }

    static clsDate IncreaseDateByXYear(clsDate & Date, short Year)
    {
        Date._Year += Year;
    
        if (Date._Month == 2 && Date._Day == 29 && !IsLeapYear(Date._Year))
            Date._Day = 28;

        return Date;
    }
    
    void IncreaseDateByXYear(short Years)
    {
        *this = IncreaseDateByXYear(*this, Years);
    }

    static clsDate IncreaseDateByXDecade(clsDate & Date, short Decade)
    {
        IncreaseDateByXYear(Date, Decade * 10);
        return Date;
    }
    
    void IncreaseDateByXDecade(short Decade)
    {
        *this = IncreaseDateByXDecade(*this, Decade);
    }

    static clsDate IncreaseDateByXCentury(clsDate & Date, short Century)
    {
        IncreaseDateByXYear(Date, Century * 100);
        return Date;
    }
    
    void IncreaseDateByXCentury(short Century)
    {
        *this = IncreaseDateByXCentury(*this, Century);
    }

    static clsDate IncreaseDateByXMillennium(clsDate & Date, short Millennium)
    {
        IncreaseDateByXYear(Date, Millennium * 1000);
        return Date;
    }
    
    void IncreaseDateByXMillennium(short Millennium)
    {
        *this = IncreaseDateByXMillennium(*this, Millennium);
    }

    static clsDate DecreaseDateByOneDay(clsDate & Date)
    {
        if (Date._Day == 1)
        {
            if (Date._Month == 1)
            {
                --Date._Year;
                Date._Month = 12;
                Date._Day = 31;
            }

            else
            {
                --Date._Month;
                Date._Day = NumberOfDaysInMonth(Date._Month, Date._Year);
            }
        }

        else
            --Date._Day;

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(clsDate & Date, short Days)
    {
        for (short i=1; i<=Days; i++)
            DecreaseDateByOneDay(Date);

        return Date;
    }
    
    void DecreaseDateByXDays(short Days)
    {
        *this = DecreaseDateByXDays(*this, Days);
    }

    static clsDate DecreaseDateByOneWeek(clsDate & Date)
    {
        DecreaseDateByXDays(Date, 7);
        return Date;
    }
  
    void DecreaseDateByOneWeek()
    {
        *this = DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(clsDate & Date, short Weeks)
    {
        for (short i=1; i<=Weeks; i++)
            DecreaseDateByOneWeek(Date);

        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        *this = DecreaseDateByXWeeks(*this, Weeks);
    }

    static clsDate DecreaseDateByOneMonth(clsDate & Date)
    {
        if (Date._Month == 1)
        {
            Date._Month = 12;
            Date._Year--;
        }
    
        else
            Date._Month--;
    
        short MonthDays = NumberOfDaysInMonth(Date._Month, Date._Year);
        if (Date._Day > MonthDays)
            Date._Day = MonthDays;

        return Date;
    }
    
    void DecreaseDateByOneMonth()
    {
        *this = DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(clsDate & Date, short Months)
    {
        for (short i=1; i<=Months; i++)
            DecreaseDateByOneMonth(Date);
        
        return Date;
    }
    
    void DecreaseDateByXMonths(short Months)
    {
        *this = DecreaseDateByXMonths(*this, Months);
    }

    static clsDate DecreaseDateByXYears(clsDate & Date, short Years)
    {
        Date._Year -= Years;
    
        if (Date._Month == 2 && Date._Day == 29 && !IsLeapYear(Date._Year))
            Date._Day = 28;

        return Date;
    }
    
    void DecreaseDateByXYears(short Years)
    {
        *this = DecreaseDateByXYears(*this, Years);
    }

    static clsDate DecreaseDateByXDecades(clsDate & Date, short Decades)
    {
        DecreaseDateByXYears(Date, Decades * 10);
        return Date;
    }
    
    void DecreaseDateByXDecades(short Decades)
    {
        *this = DecreaseDateByXDecades(*this, Decades);
    }

    static clsDate DecreaseDateByXCenturys(clsDate & Date, short Centurys)
    {
        DecreaseDateByXYears(Date, Centurys * 100);
        return Date;
    }

    void DecreaseDateByXCenturys(short Centurys)
    {
        *this = DecreaseDateByXCenturys(*this, Centurys);
    }
    
    static clsDate DecreaseDateByXMillenniums(clsDate & Date, short Millenniums)
    {
        DecreaseDateByXYears(Date, Millenniums * 1000);
        return Date;
    }
    
    void DecreaseDateByXMillenniums(short Millenniums)
    {
        *this = DecreaseDateByXMillenniums(*this, Millenniums);
    }

    static bool IsEndOfWeek(const clsDate & Date)
    {
        return (DayOfWeekOrder(Date) == 6);
    }

    bool IsEndOfWeek() const
    {
        return IsEndOfWeek(*this);
    }
    
    static bool IsWeekend(const clsDate & Date)
    {
        short DayOrder = DayOfWeekOrder(Date);
        return (DayOrder == 5 || DayOrder == 6);
    }

    bool IsWeekend() const
    {
        return IsWeekend(*this);
    }
    
    static bool IsBusinessDay(const clsDate & Date)
    {
        return (!IsWeekend(Date));
    }

    bool IsBusinessDay() const
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(const clsDate & Date)
    {
        return (6 - DayOfWeekOrder(Date));
    }
    
    short DaysUntilTheEndOfWeek() const
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(const clsDate & Date)
    {
        return (NumberOfDaysInMonth(Date._Month, Date._Year) - Date._Day);
    }
    
    short DaysUntilTheEndOfMonth() const
    {
        return DaysUntilTheEndOfMonth(*this);
    }
    
    static short DaysUntilTheEndOfYear(const clsDate & Date)
    {
        short MaxDaysInYear = (IsLeapYear(Date._Year)) ? 366 : 365;
        return (MaxDaysInYear - NumberOfDaysFromBeginningYear(Date));
    }

    short DaysUntilTheEndOfYear() const
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateVacationDays(clsDate Date1, clsDate & Date2)
    {
        if (IsDate1AfterDate2(Date1, Date2))
            return CalculateVacationDays(Date2, Date1);

        short Count = 0;
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            IncreaseDateByOneDay(Date1);
            if(IsBusinessDay(Date1))
                ++Count;
        }

        while (IsWeekend(Date1))
            Date1 = IncreaseDateByOneDay(Date1);

        return Count;
    }

    short CalculateVacationDays(clsDate & Date2)
    {
        return CalculateVacationDays(*this, Date2);
    }

    static clsDate CalculateVacationReturnDate(clsDate Date, short VacationDays)
    {
        while(VacationDays > 0)
        {
            if (!IsWeekend(Date))
                VacationDays--;

            IncreaseDateByOneDay(Date);
        }

        while (IsWeekend(Date))
            IncreaseDateByOneDay(Date);

        return Date;
    }

    void CalculateVacationReturnDate(short VacationDays)
    {
        *this = CalculateVacationReturnDate(*this, VacationDays);
    }

    static short CompareDates(const clsDate & Date1, const clsDate & Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return -1;  // Before

        if (IsDate1EqualDate2(Date1, Date2))
            return 0;   // Equal

        return 1;       // After
    }

    short CompareDates(const clsDate & Date2) const
    {
        return CompareDates(*this, Date2);
    }

    static bool IsPeriodsOverlap(const clsDate & StartDate1, const clsDate & EndDate1, const clsDate & StartDate2, const clsDate & EndDate2)
    {
        return (!IsDate1AfterDate2(StartDate1, EndDate2) && !IsDate1BeforeDate2(EndDate1, StartDate2));
    }

    static short PeriodLengthInDays(const clsDate & StartDate, const clsDate & EndDate, bool IncludeLastDay = false)
    {
        return GetDiffrenceDaysBetweenDate1AndDate2(StartDate, EndDate, IncludeLastDay);
    }

    short PeriodLengthInDays(const clsDate & EndDate, bool IncludeLastDay = false) const
    {
        return PeriodLengthInDays(*this, EndDate, IncludeLastDay);
    }

    static bool IsDateWithinPeriod(const clsDate & Date, const clsDate & From, const clsDate & To)
    {
        return !(IsDate1BeforeDate2(Date, From) || IsDate1AfterDate2(Date, To));
    }

    bool IsDateWithinPeriod(const clsDate & From, const clsDate & To) const
    {
        return IsDateWithinPeriod(*this, From, To);
    }

    static short CountOverlapDays(const clsDate & StartDate1, const clsDate & EndDate1, const clsDate & StartDate2, const clsDate & EndDate2)
    {
        if (!IsPeriodsOverlap(StartDate1, EndDate1, StartDate2, EndDate2)) return 0;

        clsDate MaxStart = (IsDate1AfterDate2(StartDate1, StartDate2)) ? StartDate1 : StartDate2;
        clsDate MinEnd = (IsDate1BeforeDate2(EndDate1, EndDate2)) ? EndDate1 : EndDate2;

        return GetDiffrenceDaysBetweenDate1AndDate2(MaxStart, MinEnd, true);
    }

    static string FormatDate(const clsDate & Date, const string & Str = "dd/mm/yyyy")
    {
        string StrDate = Str;
        StrDate = clsString::ReplaceWordsInString(StrDate, "dd", to_string(Date._Day));
        StrDate = clsString::ReplaceWordsInString(StrDate, "mm", to_string(Date._Month));
        StrDate = clsString::ReplaceWordsInString(StrDate, "yyyy", to_string(Date._Year));

        return StrDate;
    }

    string FormatDate(const string & Str = "dd/mm/yyyy") const
    {
        return FormatDate(*this, Str);
    }

    static string GetSystemDateTimeString()
    {
        short Year, Month, Day, Hour, Minute, Second;

        time_t T = time(0);
        tm * dt = localtime(&T);

        Year = dt->tm_year + 1900;
        Month = dt->tm_mon + 1;
        Day = dt->tm_mday;
        Hour = dt->tm_hour;
        Minute = dt->tm_min;
        Second = dt->tm_sec;

        return GetFullDate(Day, Month, Year) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
    }
};
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class clsString
{
private:
    string _String = "";

    static char InvertChar(char Letter)
    {
        return (isupper(Letter)) ? tolower(Letter) : toupper(Letter);
    }

    static bool IsVowel (char Ch)
    {
        Ch = tolower(Ch);
        return (Ch == 'a' || Ch == 'e' || Ch == 'i' || Ch == 'o' || Ch == 'u');
    }


public:
    clsString() {}                                       // First  Constructor
    clsString(const string & str) { _String = str; }     // Second Constructor


    void String(const string & str) { _String = str; }   // Set Property
    string String() { return _String; }                  // Get Property


    static void FirstLettersOfString(const string & Text)
    {
        cout << "\nFirst Letters of This Text:";
        cout << "\n----------------------------\n";

        if (Text == "") return;

        if (Text[0] != ' ') cout << Text[0] << endl;
        for (size_t i=1; i<Text.length(); i++)
        {
            if (Text[i-1] == ' ' && Text[i] != ' ')
                cout << Text[i] << endl;
        }
    }

    void FirstLettersOfString() const
    {
        FirstLettersOfString(_String);
    }

    static string UpperFirstLetterOfEachWord(string Text)
    {
        if (Text == "") return "";
        
        if (Text[0] != ' ') Text[0] = toupper(Text[0]);
        for (size_t i=1; i<Text.length(); i++)
        {
            if (Text[i-1] == ' ' && Text[i] != ' ')
                Text[i] = toupper(Text[i]);
        }

        return Text;
    }

    void UpperFirstLetterOfEachWord()
    {
        _String = UpperFirstLetterOfEachWord(_String);
    }

    static string UpperAllString(string Text)
    {
        for (char & Letter : Text)
            Letter = toupper(Letter);

        return Text;
    }

    void UpperAllString()
    {
        _String = UpperAllString(_String);
    }

    static string LowerAllString(string Text)
    {
        for (char & Letter : Text)
            Letter = tolower(Letter);

        return Text;
    }

    void LowerAllString()
    {
        _String = LowerAllString(_String);
    }

    static string InvertAllStringLetters(string Text)
    {
        for (char & Letter : Text)
            Letter = InvertChar(Letter);

        return Text;
    }

    void InvertAllStringLetters()
    {
        _String = InvertAllStringLetters(_String);
    }

    static short CountCapitalLetters(const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
            if (isupper(Letter))
                ++count;

        return count;
    }

    short CountCapitalLetters() const
    {
        return CountCapitalLetters(_String);
    }

    static short CountSmallLetters(const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
            if (islower(Letter))
                ++count;

        return count;
    }

    short CountSmallLetters() const
    {
        return CountSmallLetters(_String);
    }

    static short CountSpaceInString (const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
            if (isspace(Letter))
                ++count;

        return count;
    }

    short CountSpaceInString() const
    {
        return CountSpaceInString(_String);
    }

    static short CountSpecialCharInString (const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
            if (ispunct(Letter))
                ++count;

        return count;
    }

    short CountSpecialCharInString() const
    {
        return CountSpecialCharInString(_String);
    }

    static short CountNumberInString (const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
            if (isdigit(Letter))
                ++count;

        return count;
    }

    short CountNumberInString() const
    {
        return CountNumberInString(_String);
    }

    static short CountCharInString (const string & Text, char Letter, bool MatchCase = true)
    {
        short count = 0;

        if (MatchCase)
        {
            for (char ch : Text)
                if (ch == Letter)
                    ++count;
        }

        else
        {
            Letter = toupper(Letter);
            for (char ch : Text)
                if (toupper(ch) == Letter)
                    ++count;
        }
        return count;
    }

    static short CountVowelInString (const string & Text)
    {
        short count = 0;
        for (char Letter : Text)
        {
            if (IsVowel(Letter))
                ++count;
        }
        return count;
    }

    short CountVowelLetter() const
    {
        return CountVowelInString(_String);
    }

    static void PrintVowelLetter (const string & Text)
    {
        for (char Letter : Text)
            if (IsVowel(Letter))
                cout << Letter << "   ";
    }

    void PrintVowelLetter() const
    {
        PrintVowelLetter(_String);
    }

    static void PrintEachWordInString(string Text, string Delimiter = " ")
    {
        if (Text == "") return;

        string Word = "";
        size_t Pos = 0;
        while((Pos = Text.find(Delimiter)) != string::npos)
        {
            Word = Text.substr(0, Pos);
            if (Word != "")
                cout << Word << endl;

            Text.erase(0, Pos + Delimiter.length());
        }

        if (Text != "")
            cout << Text << endl;
    }

    void PrintEachWordInString() const
    {
        PrintEachWordInString(_String);
    }

    static short CountWordsInString(string Text, string Delimiter = " ")
    {
        if (Text == "") return 0;

        string Word = "";
        size_t Pos = 0, Count = 0;
        while((Pos = Text.find(Delimiter)) != string::npos)
        {
            Word = Text.substr(0, Pos);
            if (Word != "")
                ++Count;

            Text.erase(0, Pos + Delimiter.length());
        }

        if (Text != "")
            ++Count;

        return Count;
    }

    short CountWordsInString() const
    {
        return CountWordsInString(_String);
    }

    static vector<string> SplitString(string Text, string Delimiter = " ")
    {
        vector<string> Vec;
        if (Text == "") return Vec;

        string Word = "";
        size_t Pos = 0;
        while((Pos = Text.find(Delimiter)) != string::npos)
        {
            Word = Text.substr(0, Pos);
            if (Word != "")
                Vec.emplace_back(Word);

            Text.erase(0, Pos + Delimiter.length());
        }

        if (Text != "")
            Vec.emplace_back(Text);
        
        return Vec;
    }

    vector<string> SplitString() const
    {
        return SplitString(_String);
    }

    static void PrintWordsUsingVector(const vector<string> & Vec)
    {
        for(const string & V : Vec)
        {
            cout << V << endl;
        }
    }

    static string JoinString(const vector<string> & Vec, string Delimiter = " ")
    {
        if (Vec.empty()) return "";

        string Str = Vec[0];
        for (size_t i=1; i<Vec.size(); i++)
        {
            Str += Delimiter + Vec[i];
        }

        return Str;
    }

    static string JoinString(const string Vec[], short arrSize, string Delimiter = " ")
    {
        string Str = Vec[0];
        for (short i=1; i<arrSize; i++)
        {
            Str += Delimiter + Vec[i];
        }

        return Str;
    }
    
    static string TrimLeft(string Text)
    {
        if (Text == "") return "";

        for (size_t i=0; i<Text.length(); i++)
        {
            if (!isspace(Text[i]))
                return Text.erase(0, i);
        }
        return Text;
    }

    void TrimLeft()
    {
        _String = TrimLeft(_String);
    }

    static string TrimRight(string Text)
    {
        if (Text == "") return "";

        for (int i = (int)Text.length() - 1; i >= 0; --i)
        {
            if (!isspace(Text[i]))
                return Text.erase(i+1);   // from (i+1) to end string
        }

        return Text;
    }

    void TrimRight()
    {
        _String = TrimRight(_String);
    }

    static string Trim(const string & Text)
    {
        return TrimLeft(TrimRight(Text));
    }

    void Trim()
    {
        _String = Trim(_String);
    }

    static string ReverseWordsInString(const string & Text)
    {
        vector<string> Vtr = SplitString(Text);
        if (Vtr.empty()) return "";
        
        string Reverse = "";
        for (auto iter = Vtr.rbegin(); iter != Vtr.rend(); ++iter)
        {
            Reverse += *iter + " ";
        }

        if (Reverse != "")
            Reverse.pop_back();
        return Reverse;
    }

    void ReverseWordsInString()
    {
        _String = ReverseWordsInString(_String);
    }

    static string ReplaceWordsInString(const string & Text, string Old, const string & New, bool MatchCase = true)
    {
        if (Text == "") return "";

        vector<string> Vec = SplitString(Text);

        if (MatchCase == true)
        {
            for(string & V : Vec)
            {
                if (Old == V)
                    V = New;
            }
        }

        else
        {
            Old = UpperAllString(Old);
            for(string & V : Vec)
            {
                if (Old == UpperAllString(V))
                    V = New;
            }
        }

        return JoinString(Vec);
    }

    void ReplaceWordsInString(const string & Old, const string & New, bool MatchCase = true)
    {
        _String = ReplaceWordsInString(_String, Old, New, MatchCase);
    }

    static string RemovePunctuationsInString (const string & Text)
    {
        string Str = "";
        for (char Letter : Text)
        {
            if (!ispunct(Letter))
                Str += Letter;
        }
        return Str;
    }

    void RemovePunctuationsInString()
    {
        _String = RemovePunctuationsInString(_String);
    }
};
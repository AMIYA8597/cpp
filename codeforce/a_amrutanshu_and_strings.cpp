// A. Amrutanshu and Stringggs
// time limit per test2 seconds
// memory limit per test512 megabytes
// Amrutanshu loves playing with strings — but only the short ones.

// His friend Ayush loves to tease him by giving extremely long strings. Whenever a string is too long (its length is strictly more than 10), Amrutanshu shortens it using his own rule:

// Keep the first and last character of the string.
// Replace all the characters between them with the number of characters in between.
// Only strings whose length is strictly more than 10 should be converted. Strings of length 10 or less must remain unchanged.

// For example:

// localization" becomes l10n"
// internationalization" becomes i18n"
// amrutanshu" (length 10) remains amrutanshu"
// You are given several strings from Ayush. Help Amrutanshu transform each one according to his rule.

// Input
// The first line contains an integer n
//  (1≤n≤100
// ) — the number of strings. Each of the next n
//  lines contains a single string s
//  consisting only of lowercase Latin letters. The length of each string is between 1
//  and 100
// .

// Output
// Print n
//  lines. For each string, output the shortened version after applying Amrutanshu's rule. Remember: only strings with length strictly greater than 10
//  are replaced; other strings must be printed unchanged.

// Example
// InputCopy
// 4
// amrutanshu
// supercalifragilisticexpialidocious
// short
// extraordinary
// OutputCopy
// amrutanshu
// s32s
// short
// e11y
// Note
// Explanation of the sample test cases:

// amrutanshu — length is 10
// , so it is printed unchanged as amrutanshu.
// supercalifragilisticexpialidocious — length is greater than 10
// . The first character is s and the last character is s; the number of characters between them is 32, so we output s32s.
// short — length is 5
// , so it is printed unchanged as short.
// extraordinary — length is greater than 10
// . The first character is e and the last character is y; the number of characters between them is 11, so we output e11y.




















































#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int len = s.length();
        if (len > 10) {
            cout << s[0] << len - 2 << s[len - 1] << endl;
        } else {
            cout << s << endl;
        }
    }
    return 0;
}
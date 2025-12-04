#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// Text buffer implemented with two stacks (left and right of the cursor)
class TextBuffer {
    private:
        stack<char> left;  // characters to the left of cursor (top is immediate left)
        stack<char> right; // characters to the right of cursor (top is immediate right)

    public:
        TextBuffer() = default;

        // Insert a character at the cursor (cursor stays after the inserted char)
        void insertChar(char c) {
            left.push(c);
        }

        // Insert a whole string at the cursor (characters inserted in order)
        void insertString(const string &s) {
            for (char c : s) insertChar(c);
        }

        // Delete character immediately before the cursor (like backspace)
        bool deleteChar() {
            if (left.empty()) return false;

            left.pop();
            return true;
        }

        // Move cursor one position left
        bool moveLeft() {
            if (left.empty()) return false;

            right.push(left.top());
            left.pop();

            return true;
        }

        // Move cursor one position right
        bool moveRight() {
            if (right.empty()) return false;

            left.push(right.top());
            right.pop();

            return true;
        }

        // Move cursor to start of buffer
        void moveToStart() {
            while (moveLeft()) { }
        }

        // Move cursor to end of buffer
        void moveToEnd() {
            while (moveRight()) { }
        }

        // Get full content as a string (without cursor marker)
        string getContent() const {
            stack<char> l = left;
            stack<char> r = right;
            string out;

            // left: need bottom-to-top order
            vector<char> tmp;
            while (!l.empty()) { 
                tmp.push_back(l.top()); 
                l.pop(); 
            }

            for (auto it = tmp.rbegin(); it != tmp.rend(); ++it) out.push_back(*it);

            // right: top-to-bottom is correct order for characters right of cursor
            while (!r.empty()) { 
                out.push_back(r.top()); 
                r.pop(); 
            }

            return out;
        }

        // Get content with a '|' showing the cursor position
        string getContentWithCursor() const {
            stack<char> l = left;
            stack<char> r = right;
            string out;

            vector<char> tmp;
            while (!l.empty()) { 
                tmp.push_back(l.top()); 
                l.pop(); 
            }

            for (auto it = tmp.rbegin(); it != tmp.rend(); ++it) out.push_back(*it);

            out.push_back('|');

            while (!r.empty()) { 
                out.push_back(r.top()); 
                r.pop(); 
            }

            return out;
        }

        // Number of characters in buffer
        size_t size() const {
            return left.size() + right.size();
        }
};

// Small interactive demo for the TextBuffer.
// Commands:
//  I <text>  : Insert <text> at cursor (text may be multiple chars)
//  L         : Move cursor left
//  R         : Move cursor right
//  D         : Delete char before cursor (backspace)
//  S         : Show buffer with cursor marker
//  E         : Move cursor to end
//  B         : Move cursor to beginning
//  Q         : Quit

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TextBuffer buf;
    cout << "Simple TextBuffer demo (two-stack implementation)\n";
    cout << "Commands: I <text>, L, R, D, S, E (end), B (begin), Q\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        // trim leading spaces
        size_t pos = 0; while (pos < line.size() && isspace((unsigned char)line[pos])) ++pos;
        if (pos >= line.size()) continue;

        char cmd = line[pos];

        if (cmd == 'Q' || cmd == 'q') break;

        if (cmd == 'I' || cmd == 'i') {
            // Insert rest of line after command and optional space
            string rest;
            if (pos + 1 < line.size()) {
                // skip one space if present
                size_t start = pos + 1;
                if (start < line.size() && isspace((unsigned char)line[start])) ++start;
                rest = line.substr(start);
            }
            buf.insertString(rest);
        } else if (cmd == 'L' || cmd == 'l') {
            if (!buf.moveLeft()) cout << "Already at beginning\n";
        } else if (cmd == 'R' || cmd == 'r') {
            if (!buf.moveRight()) cout << "Already at end\n";
        } else if (cmd == 'D' || cmd == 'd') {
            if (!buf.deleteChar()) cout << "Nothing to delete\n";
        } else if (cmd == 'S' || cmd == 's') {
            cout << buf.getContentWithCursor() << '\n';
        } else if (cmd == 'E' || cmd == 'e') {
            buf.moveToEnd();
        } else if (cmd == 'B' || cmd == 'b') {
            buf.moveToStart();
        } else {
            cout << "Unknown command\n";
        }
    }

    cout << "Final buffer: " << buf.getContent() << "\n";
    return 0;
}

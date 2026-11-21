#include <cctype>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream file("main.bin", ios::binary);

    if (!file)
    {
        cerr << "no such a file found!";
        return 1;
    }

    constexpr streamsize bytes_per_line = 16;
    vector<uint8_t> buffer(bytes_per_line);
    unsigned int offset = 0;

    while (file.read(reinterpret_cast<char *>(buffer.data()), bytes_per_line) || file.gcount() > 0)
    {

        streamsize bytes_read = file.gcount();

        cout << setw(8) << setfill('0') << hex << offset << " ";

        for (streamsize i = 0; i < bytes_read; ++i)
        {

            if (i < bytes_read)
                cout << setw(2) << setfill('0') << hex << static_cast<unsigned int>(buffer[i]) << " ";
            else
                cout << "  ";
        }

        for (streamsize i = bytes_read; i < bytes_per_line; i++)
        {
            cout << "  ";
        }

        cout << "| ";
        for (streamsize i = 0; i < bytes_read; ++i)
        {
            unsigned char ch = buffer[static_cast<size_t>(i)];
            cout << (isprint(ch) ? static_cast<char>(ch) : '.');
        }

        cout << " |\n";
        offset += bytes_per_line;
    }

    return 0;
}
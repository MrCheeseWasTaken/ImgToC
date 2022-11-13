#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <fstream>

#include <windows.h>

using namespace std;
using namespace sf;

typedef unsigned short u16;
#define rawRGB(r, g, b) ((r) + ((g) << 5) + ((b) << 10))

struct RGB
{
    int r, g, b;

    u16 raw()
    {
        r = float(r) / 255 * 31;
        g = float(g) / 255 * 31;
        b = float(b) / 255 * 31;

        return (u16(r) + (u16(g) << 5) + (u16(b) << 10));
    }
};

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

template <typename I>
std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1)
{
    static const char *digits = "0123456789ABCDEF";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(w >> j) & 0x0f];
    return rc;
}

// Returns an empty string if dialog is canceled
string openfilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL)
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";

    string fileNameStr;

    if (GetOpenFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}

int main()
{
    string path = openfilename();

    Image img;

    if (img.loadFromFile(path))
    {

        int size = img.getSize().x * img.getSize().y;

        string name = split(path, "\\").back();
        name = split(name, ".")[0];

        vector<u16> colorMap;

        for (int y = 0; y < img.getSize().y; y++)
        {
            for (int x = 0; x < img.getSize().x; x++)
            {

                RGB rgb{img.getPixel(x, y).r, img.getPixel(x, y).g, img.getPixel(x, y).b};
                colorMap.push_back(rgb.raw());
            }
        }

        vector<string> stringMap;

        for (int i = 0; i < colorMap.size(); i++)
            stringMap.push_back("0x" + n2hexstr(colorMap[i]) + ",");

        string code = "//" + name + " " + to_string(img.getSize().x) + ", " + to_string(img.getSize().y);

        code = code + "\n\n" + "const unsigned short " + name + "_Map[" + to_string(size) + "] = {\n";

        for (int i = 0; i < stringMap.size(); i++)
        {
            code = code + stringMap[i];
            if ((i + 1) % 8 == 0 and i + 1 != size)
                code = code + "\n";
        }

        code = code + "\n};";

        string p = split(path, name)[0];
        cout << p + name + ".c";
        ofstream output(p + name + ".c");

        output << code;

        output.close();
    }

    return 0;
}
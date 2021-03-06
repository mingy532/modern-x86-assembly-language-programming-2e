//------------------------------------------------
//               Ch11_03.cpp
//------------------------------------------------

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

#include "stdafx.h"

extern "C" uint64_t GprMulx_(uint32_t a, uint32_t b, uint64_t flags[2]);
extern "C" void GprShiftx_(uint32_t x, uint32_t count, uint32_t results[3], uint64_t flags[4]);

string ToString(uint64_t flags)
{
    ostringstream oss;

    oss << "OF=" << ((flags & (1ULL << 11)) ? '1' : '0') << ' '; 
    oss << "SF=" << ((flags & (1ULL <<  7)) ? '1' : '0') << ' ';
    oss << "ZF=" << ((flags & (1ULL <<  6)) ? '1' : '0') << ' ';
    oss << "PF=" << ((flags & (1ULL <<  2)) ? '1' : '0') << ' ';
    oss << "CF=" << ((flags & (1ULL <<  0)) ? '1' : '0') << ' ';

    return oss.str();
}

void GprMulx(void)
{
    const int n = 3;
    uint32_t a[n] = {64, 3200, 100000000};
    uint32_t b[n] = {1001, 12, 250000000};

    cout << "\nResults for AvxGprMulx\n";

    for (int i = 0; i < n; i++)
    {
        uint64_t flags[2];
        uint64_t c = GprMulx_(a[i], b[i], flags);

        cout << "\nTest case " << i << '\n';
        cout << "  a: " << a[i] << "  b: " << b[i] << "  c: " << c << '\n';

        cout << setfill ('0') << hex;
        cout << "  status flags before mulx: " << ToString(flags[0]) << '\n';
        cout << "  status flags after mulx:  " << ToString(flags[1]) << '\n';
        cout << setfill (' ') << dec;
    }
}

void GprShiftx(void)
{
    const int n = 4;
    uint32_t x[n] = { 0x00000008, 0x80000080, 0x00000040, 0xfffffc10 };
    uint32_t count[n] = { 2, 5, 3, 4 };

    cout << "\nResults for AvxGprShiftx\n";

    for (int i = 0; i < n; i++)
    {
        uint32_t results[3];
        uint64_t flags[4];

        GprShiftx_(x[i], count[i], results, flags);

        cout << setfill(' ') << dec;
        cout << "\nTest case " << i << '\n';

        cout << setfill('0') << hex << "  x:    0x" << setw(8) << x[i] << " (";
        cout << setfill(' ') << dec << x[i] << ") count: " << count[i] << '\n';

        cout << setfill('0') << hex << "  sarx: 0x" << setw(8) << results[0] << " (";
        cout << setfill(' ') << dec << results[0] << ")\n";

        cout << setfill('0') << hex << "  shlx: 0x" << setw(8) << results[1] << " (";
        cout << setfill(' ') << dec << results[1] << ")\n";

        cout << setfill('0') << hex << "  shrx: 0x" << setw(8) << results[2] << " (";
        cout << setfill(' ') << dec << results[2] << ")\n";

        cout << "  status flags before shifts: " << ToString(flags[0]) << '\n';
        cout << "  status flags after sarx:    " << ToString(flags[1]) << '\n';
        cout << "  status flags after shlx:    " << ToString(flags[2]) << '\n';
        cout << "  status flags after shrx:    " << ToString(flags[3]) << '\n';
    }
}

int main()
{
    GprMulx();
    GprShiftx();
    return 0;
}

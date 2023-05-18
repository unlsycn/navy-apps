#include <assert.h>
#include <fixedptc.h>

int main()
{
    fixedpt a = fixedpt_rconst(1.234);
    fixedpt b = fixedpt_fromint(87);
    assert(fixedpt_toint(fixedpt_ceil(fixedpt_div(fixedpt_mul(a + FIXEDPT_ONE, b), fixedpt_rconst(2.3)))) == 85);

    a = fixedpt_rconst(1321.23);
    b = fixedpt_rconst(-492.56);
}
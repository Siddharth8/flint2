/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Abhinav Baid

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "mpf_vec.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("dot2....");
    fflush(stdout);


    for (i = 0; i < 10000 * flint_test_multiplier(); i++)
    {
        mpf *a, *b;
        mpf_t res1, res2, res3;
        slong len = n_randint(state, 100);
        if (!len)
            continue;

        a = _mpf_vec_init(len, 200);
        b = _mpf_vec_init(len, 200);
        _mpf_vec_randtest(a, state, len, 200);
        _mpf_vec_randtest(b, state, len, 200);

        mpf_inits(res1, res2, res3, '\0');
        _mpf_vec_dot2(res1, a, b, len - 1, 200);
        _mpf_vec_dot2(res2, a + len - 1, b + len - 1, 1, 200);
        _mpf_vec_dot2(res3, a, b, len, 200);

        mpf_add(res1, res1, res2);
        result = mpf_cmp(res1, res3);
        if (result)
        {
            flint_printf("FAIL:\n");
            flint_printf("%d\n", len);
            mpf_out_str(stdout, 10, 0, res1);
            flint_printf("\n");
            mpf_out_str(stdout, 10, 0, res3);
            flint_printf("\n");
            abort();
        }

        _mpf_vec_clear(a, len);
        _mpf_vec_clear(b, len);
        mpf_clears(res1, res2, res3, '\0');
    }

    FLINT_TEST_CLEANUP(state);

    flint_printf("PASS\n");
    return 0;
}

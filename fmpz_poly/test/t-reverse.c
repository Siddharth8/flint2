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

    Copyright (C) 2009 William Hart
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int result;
    printf("reverse....");
    fflush(stdout);

    fmpz_poly_randinit();

    // Aliasing
    for (ulong i = 0; i < 2000UL; i++)
    {
        fmpz_poly_t a, b;
        ulong n;

        fmpz_poly_init(a);
        fmpz_poly_init(b);
        fmpz_poly_randtest(b, n_randint(100), n_randint(200));
        n = n_randint(150);

        fmpz_poly_reverse(a, b, n);
        fmpz_poly_reverse(b, b, n);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("Error:\n");
            printf("n = %lu\n\na = ", n);
            fmpz_poly_print(a);
            printf("\n\nb = ");
            fmpz_poly_print(b);
            printf("\n\n");
            abort();
        }

        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    // Correctness (?)
    for (ulong i = 0; i < 2000UL; i++)
    {
        fmpz_poly_t a, b;
        ulong j, len, n;

        fmpz_poly_init(a);
        fmpz_poly_init(b);
        fmpz_poly_randtest(b, n_randint(100), n_randint(200));
        n = n_randint(150);
        
        len = FLINT_MIN(n, b->length);
        if (len)
        {
            fmpz_poly_fit_length(a, n);
            for (j = 0; j < len; j++)
                fmpz_set(a->coeffs + (n - len) + j, b->coeffs + (len - 1 - j));
            _fmpz_poly_set_length(a, n);
            _fmpz_poly_normalise(a);
        }
        
        fmpz_poly_reverse(b, b, n);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("Error:\n");
            printf("n = %lu\n\na = ", n);
            fmpz_poly_print(a);
            printf("\n\nb = ");
            fmpz_poly_print(b);
            printf("\n\n");
            abort();
        }

        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    fmpz_poly_randclear();

    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
#include <ctest.h>
#include <libgeom/geom.h>

CTEST(getfig, test)
{
    char str[] = "circle(1.5 3, 5)", fig[10];
    get_fig(str, fig);

    ASSERT_STR(fig, "circle");
}

CTEST(figcheck, test)
{
    char str[] = "circle(1.5 3, 5)", fig[10];
    get_fig(str, fig);

    fig_check(fig, "circle");
}

CTEST(getnumbers, test_1)
{
    krug circle;
    char str[] = "circle(10 10, 10)";

    int error = 0;
    circle.error = 0;
    float x = 10, y = 10, rad = 10;

    get_numbers(&circle, str);

    ASSERT_DBL_NEAR(circle.p.x, x);
    ASSERT_DBL_NEAR(circle.p.y, y);
    ASSERT_DBL_NEAR(circle.r, rad);
    ASSERT_EQUAL(circle.error, error);
}

CTEST(getnumbers, test_2)
{
    krug circle;
    char str[] = "circle(-4 2, 3.5) af";

    int error = 1;
    circle.error = 0;
    float x = -4, y = 2, rad = 3.5;

    get_numbers(&circle, str);

    ASSERT_DBL_NEAR(circle.p.x, x);
    ASSERT_DBL_NEAR(circle.p.y, y);
    ASSERT_DBL_NEAR(circle.r, rad);
    ASSERT_EQUAL(circle.error, error);
}

CTEST(area, test)
{
    krug circle;
    circle.p.x = 1;
    circle.p.y = 2;
    circle.r = 3;

    float s = 28.27433;
    circle.s = area(&circle);

    ASSERT_DBL_NEAR(circle.s, s);
}

CTEST(perimeter, test)
{
    krug circle;
    circle.p.x = 1;
    circle.p.y = 2;
    circle.r = 3;

    float p = 18.84956;
    circle.per = perimeter(&circle);

    ASSERT_DBL_NEAR(circle.per, p);
}

CTEST(intersection, test_1)
{
    krug circle[2];

    circle[0].p.x = 3;
    circle[0].p.y = 3;
    circle[0].r = 5;
    circle[0].error = 0;

    circle[1].p.x = 5;
    circle[1].p.y = 5;
    circle[1].r = 4;
    circle[1].error = 0;

    intersection_fig(&circle[0], 2);

    ASSERT_EQUAL(circle[0].intersection[0], 2);
    ASSERT_EQUAL(circle[1].intersection[0], 1);
}

CTEST(intersection, test_2)
{
    krug circle[2];

    circle[0].p.x = 3;
    circle[0].p.y = 3;
    circle[0].r = 3;
    circle[0].error = 0;
    circle[0].intersection[0] = 0;

    circle[1].p.x = 10;
    circle[1].p.y = 6;
    circle[1].r = 2;
    circle[1].error = 0;
    circle[1].intersection[0] = 0;

    intersection_fig(&circle[0], 2);

    ASSERT_EQUAL(circle[0].intersection[0], 0);
    ASSERT_EQUAL(circle[1].intersection[0], 0);
}
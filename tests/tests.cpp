#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "utility.cpp"
#include "doctest.h"

TEST_CASE("Умножение матриц") {

    CHECK(matrix m1{{2, 1},{2, 1}} * matrix m2{{3, 2}, {4, 5}}; == matrix res{{10, 9}, {2, 9}});
    CHECK(matrix m1{{1, 2, 3}} * matrix m2{{5}, {6}, {7}}; == matrix res{{18, 36, 54}});
    CHECK(matrix m1{{2, 1, 3}, {1, 2, 3}} * matrix m2{{7, 8}, {9, 10}, {11, 12}}; == matrix res{{56, 62}, {58, 64}});
    CHECK(matrix m1{{}} * matrix m2{{}}; == matrix res{{}});

}

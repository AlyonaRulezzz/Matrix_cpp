#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(Constructors, Default) {
    S21Matrix m1;
    EXPECT_EQ(3, m1.GetRows());
    EXPECT_EQ(3, m1.GetCols());
}

TEST(Constructors, With_parameters) {
    S21Matrix m1(4, 5);
    EXPECT_EQ(4, m1.GetRows());
    EXPECT_EQ(5, m1.GetCols());
    EXPECT_NO_THROW(S21Matrix m1(4, 5));

    EXPECT_ANY_THROW(S21Matrix m2(0, 8));
    EXPECT_ANY_THROW(S21Matrix(-8, 8));
}

TEST(Constructors, Copy) {
    S21Matrix test1;
    test1.Fill(5);

    S21Matrix m1(test1);
    EXPECT_EQ(test1.GetRows(), m1.GetRows());
    EXPECT_EQ(test1.GetCols(), m1.GetCols());
    for (int i = 0; i < m1.GetRows(); i++) {
        for (int j = 0; j< m1.GetCols(); j++) {
            EXPECT_EQ(test1(i, j), m1(i, j));
        }
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
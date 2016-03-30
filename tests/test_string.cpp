#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyString.h"



TEST_CASE("TEST 1") {
    String s;
    REQUIRE(*(s.data()) == '\0');
    REQUIRE(s.size() == 0);
}

TEST_CASE("TEST 2") {
    char  B[] = "Test2";
    String A(B);
    const char *pt = A.data();
    REQUIRE(A.size() == 5);
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(B[i] == *(pt++));
    }
}

TEST_CASE("TEST 3") {
    char * B = "Test3";
    String A(B, 5);
    const char *pt = A.data();
    REQUIRE(A.size() == 5);
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(B[i] == *(pt++));
    }
}

TEST_CASE("Test 4") {
    char B = 'q';
    String A(B, 10);
    const char *pt = A.data();
    REQUIRE(A.size() == 10);
    for (unsigned i = 0; i < A.size(); ++i) {
        REQUIRE(B == *(pt++));
    }
    REQUIRE('\0' == *pt);
}

TEST_CASE("Test5") {
    String B("Test5");
    String A(B);
    REQUIRE(A.size() == B.size());
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(B[i] == A[i]);
    }
}

TEST_CASE("Test6") {
    String B("Test6");
    String C(B);
    String A(std::move(B));
    REQUIRE(A.size() == C.size());
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(C[i] == A[i]);
    }
    REQUIRE(B.size() == 0);
    REQUIRE(*(B.data()) == '\0');
}

TEST_CASE ("Test_assigment1") {
    String A("Test_assigment1");
    String B, C;
    C = B = A;
    REQUIRE(A.size() == C.size());
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(C[i] == A[i]);
    }
}

TEST_CASE ("Test_assigment2") {
    String B("Test_assigment2");
    String C = B;
    String A = std::move(B);
    REQUIRE(A.size() == C.size());
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(C[i] == A[i]);
    }
    REQUIRE(B.size() == 0);
    REQUIRE(*(B.data()) == '\0');
}

TEST_CASE ("Test_plus_assigment_1") {
    char *res = "plus_assigment";
    String A("plus_");
    size_t Asize = A.size();
    String B("assigment");
    size_t Bsize = B.size();
    A += B;
    REQUIRE(A.size() == (Asize + Bsize));
    for (size_t i = 0; i <= A.size(); ++i) {
        REQUIRE(res[i] == A[i]);
    }
}

TEST_CASE ("Test_plus_assigment_2") {
    char *res = "plus_assigment";
    String C("plus_");
    size_t Csize = C.size();
    char A[] = "assigment";
    size_t Asize = 9;
    String B("plus_");
    size_t Bsize = B.size();
    C += A;
    B += "assigment";
    REQUIRE((Asize + Csize) == C.size());
    REQUIRE(B.size() == (Asize + Bsize));
    REQUIRE(B.size() == C.size());
    for (size_t i = 0; i <= C.size(); ++i) {
        REQUIRE(res[i] == C[i]);
        REQUIRE(res[i] == B[i]);
    }
}

TEST_CASE ("Test_plus_assigment_3") {
    char *res = "plus_";
    String C("plus");
    size_t  Csize = C.size();
    char A = '_';
    size_t Asize = 1;
    String B("plus");
    size_t Bsize = B.size();
    C += A;
    B += '_';
    REQUIRE((Asize + Csize) == C.size());
    REQUIRE(B.size() == (Asize + Bsize));
    REQUIRE(B.size() == C.size());
    for (size_t i = 0; i <= B.size(); ++i) {
        REQUIRE(res[i] == C[i]);
        REQUIRE(res[i] == B[i]);
    }
}

TEST_CASE ("Test_index") {
    String A("Test");
    A[1] = 'a';
    char *res = "Tast";
    for (unsigned i = 0; i <= A.size(); ++i) {
        REQUIRE(res[i] == A[i]);
    }
}

TEST_CASE ("Test_swap") {
    char *res1 = "hgf";
    char *res2 = "lkjhgf";
    String A(res1);
    String B(res2);
    size_t Asize = A.size();
    size_t Bsize = B.size();
    A.swap(B);
    REQUIRE(Bsize == A.size());
    REQUIRE(Asize == B.size());
    for (size_t i = 0; i <= A.size(); ++i) {
        REQUIRE(res2[i] == A[i]);
    }
    for (size_t i = 0; i <= B.size(); ++i) {
        REQUIRE(res1[i] == B[i]);
    }
}

TEST_CASE ("Test_at") {
    const String A("Test_at");
    REQUIRE(A.at(3) == 't');
    REQUIRE_THROWS(A.at(10));
}

TEST_CASE ("Test_equality") {
    String A("Test");
    String B(A);
    REQUIRE(A.size() == B.size());
    for (size_t i = 0; i < A.size(); ++i) {
        REQUIRE(A[i] == B[i]);
    }
}

TEST_CASE ("Test_less") {
    String A("Test");
    String B(A);
    REQUIRE_FALSE(A < B);
    B += "er";
    REQUIRE(A < B);
    A+="aa";
    REQUIRE(A < B);
}

TEST_CASE ("Test_plus_1") {
    String A("Test_");
    String B("plus_1");
    String C;
    String res("Test_plus_1");

    C = A + B;
    A = A + B;
    REQUIRE(C == res);
    REQUIRE(A == res);
}

TEST_CASE ("Test_plus_2") {
    String A("Test_");
    char * B = "plus_1";
    String C;
    String res("Test_plus_1");
    C = A + B;
    A = A + B;
    REQUIRE(C == res);
    REQUIRE(A == res);
}

TEST_CASE ("Test_plus_3") {
    String A("Test_");
    char * B = "plus_1";
    String C;
    String res("Test_plus_1");
    C = B + A;
    A = B + A;
    REQUIRE(C == res);
    REQUIRE(A == res);
}

TEST_CASE ("Test_not_equality") {
    String A("kjh");
    String B("hgh");
    REQUIRE(!(A == B));
}

TEST_CASE ("Test_less_equality") {
    String A("less");
    String B("equality");
    String C("less");
    REQUIRE(((B <= A) && (A <= C)));

}

TEST_CASE ("Test_more") {
    String A("more");
    String B("aaaaa");
    REQUIRE(A > B);

}

TEST_CASE ("Test_more_equality") {
    String A("more");
    String B("more");
    String C("equality");
    REQUIRE(((B >= A) && (A >= C)));

}

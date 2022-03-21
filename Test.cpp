#include "doctest.h"
#include "Notebook.hpp"
#include <string>
#include <algorithm>

using namespace ariel;
using ariel::Direction;
using ariel::Notebook;
using namespace std;

Notebook n;

//TEST_CASE("Bad input - minus") {
//    CHECK_THROWS (n.write(/*page=*/100, /*row=*/-1, /*column=*/50, Direction::Horizontal, "abcd"));
//}
//TEST_CASE("Bad input - minus ") {
//    CHECK_THROWS (n.write(/*page=*/-2, /*row=*/1, /*column=*/50, Direction::Horizontal, "abcd"));
//}
//TEST_CASE("Bad input - minus ") {
//    CHECK_THROWS (n.write(/*page=*/2, /*row=*/1, /*column=*/-5, Direction::Horizontal, "abcd"));
//}
//TEST_CASE("Bad input - minus ") {
//    CHECK_THROWS (n.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/-1));
//}
TEST_CASE("Bad input - 110 chars") {
    CHECK_THROWS (n.write(/*page=*/2, /*row=*/1, /*column=*/5, Direction::Horizontal, "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"));
}
TEST_CASE("Bad input - Page not written") {
    CHECK_THROWS (n.read(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3));

//good write:
    n.write(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, "01234567");
    n.write(/*page=*/0, /*row=*/0, /*column=*/9, Direction::Horizontal, "9");
}
TEST_CASE("Good output") {
            CHECK (n.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/10) == "01234567_9");


//good erase: 
    n.erase(/*page=*/0, /*row=*/0, /*column=*/1, Direction::Vertical, /*length=*/1);
}

TEST_CASE("Good output") {
            CHECK (n.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/10) == "0~234567_9");


//good erase: 
    n.erase(/*page=*/0, /*row=*/0, /*column=*/1, Direction::Vertical, /*length=*/1);
}

TEST_CASE("Good output") {
            CHECK (n.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/10) == "0~234567_9");
}

TEST_CASE("Good output") {
//Todo: check if legal to erase empty char:
    n.erase(/*page=*/0, /*row=*/0, /*column=*/8, Direction::Horizontal, /*length=*/1);

            CHECK (n.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/10) == "0~234567~9");
}

TEST_CASE("Good output") {
//good write:
    n.write(/*page=*/0, /*row=*/1, /*column=*/0, Direction::Vertical, "Yossi");

            CHECK (n.read(/*page=*/0, /*row=*/1, /*column=*/0, Direction::Vertical, /*length=*/5) == "Yossi");
}
TEST_CASE("Bad input - override") {
    CHECK_THROWS (n.write(/*page=*/0, /*row=*/1, /*column=*/0, Direction::Vertical, "Yossi"));
}
TEST_CASE("Bad input - override") {
    CHECK_THROWS (n.write(/*page=*/0, /*row=*/2, /*column=*/0, Direction::Horizontal, "ov"));
}
TEST_CASE("Bad input - override") {
    CHECK_THROWS (n.write(/*page=*/0, /*row=*/0, /*column=*/1, Direction::Vertical, "123456789"));
}

TEST_CASE("Good output - all line") {
//good write:
    n.write(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, "Once upon a time there was a dear little girl who was loved by every one who looked at her...");

            CHECK (n.read(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/100) == "Once upon a time there was a dear little girl who was loved by every one who looked at her..._______");
}
TEST_CASE("Good output - empty") {      //Todo: check if legal to read empty string:
            CHECK (n.read(/*page=*/0, /*row=*/1, /*column=*/0, Direction::Vertical, /*length=*/0) == "");
}

TEST_CASE("Good output - all line 1") {
//good write:
    n.write(/*page=*/1, /*row=*/1, /*column=*/0, Direction::Horizontal, "Once upon a time there was a dear little girl who was loved by every one who looked at her...");
//good erase: 
    n.erase(/*page=*/1, /*row=*/0, /*column=*/4, Direction::Vertical, /*length=*/2);
            CHECK (n.read(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/100) == "Once~upon a time there was a dear little girl who was loved by every one who looked at her..._______");
}
TEST_CASE("Good output - all line 2") {
            CHECK (n.read(/*page=*/1, /*row=*/1, /*column=*/0, Direction::Horizontal, /*length=*/100) ==
                   "Once~upon a time there was a dear little girl who was loved by every one who looked at her..._______");
}
TEST_CASE("Bad input - 101 chars - read") {
    CHECK_THROWS (n.read(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/101));
}
TEST_CASE("Bad input - 101 chars - erase") {
    CHECK_THROWS (n.erase(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/101));
}
TEST_CASE("Bad input - more chars then line - erase") {
    CHECK_THROWS (n.erase(/*page=*/1, /*row=*/0, /*column=*/10, Direction::Horizontal, /*length=*/95));
}

Notebook n1;
TEST_CASE("Good output - all line 1") {
    for (unsigned int i= 0; i<10; i++){
//good write:
        n1.write(/*page=*/0, /*row=*/i, /*column=*/0, Direction::Horizontal, "Once upon a time there was a dear little girl who was loved by every one who looked at her...");
    }
            CHECK (n1.read(/*page=*/0, /*row=*/6, /*column=*/0, Direction::Horizontal, /*length=*/100) == "Once upon a time there was a dear little girl who was loved by every one who looked at her..._______");
            CHECK (n1.read(/*page=*/0, /*row=*/10, /*column=*/0, Direction::Horizontal, /*length=*/10) == "__________");
            CHECK (n1.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/10) == "OOOOOOOOOO");
//good erase:
    n1.erase(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/10);
            CHECK (n1.read(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/10) == "~~~~~~~~~~");
}
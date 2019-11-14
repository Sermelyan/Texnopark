#include <gtest/gtest.h>

extern "C" {
    #include "../include/blank_pack.h"
}

class BlankTest : public ::testing::Test{
 public:
    void SetUp() {
    }
    void TearDown() {
    }
 protected:
};

TEST_F(BlankTest, TestNewBlank) {
    Blank *blank = new_blank();
    ASSERT_TRUE(blank);
    ASSERT_EQ(blank->number, 0);
    ASSERT_STREQ(blank->storage_place, "");
    ASSERT_STREQ(blank->responsible_name, "");
    ASSERT_STREQ(blank->responsible_surname, "");
}

TEST_F(BlankTest, TestPrintingBlank) {
    FILE *inp = fopen("inp.txt", "w");
    fprintf(inp, "121;Russia, Moscow, str Street;Sergey; Melikyan;");
    fclose(inp);

    Blank *blank = NULL;
    FILE *inp1 = fopen("inp.txt", "r");
    ASSERT_TRUE(blank = get_blank(inp, NULL));
    fclose(inp1);

    FILE *out = fopen("out.txt", "w");
    print_blank(out, blank);
    fclose(out);

    FILE *out1 = fopen("out.txt", "r");
    char *buffer = (char *) calloc(256, sizeof(char));
    fgets(buffer, 256, out1);
    fclose(out1);

    EXPECT_STREQ(buffer, "number: 121; storage: Russia, Moscow, str Street; responsible: Sergey Melikyan\n");

    free(blank);
    free(buffer);
}

class BlankArrayTest : public ::testing::Test{
};

TEST_F(BlankArrayTest, TestNewArray) {
    Blank_array *blank_array = new_blank_array(0);
    ASSERT_TRUE(blank_array);
    ASSERT_TRUE(blank_array->array);
    ASSERT_EQ(blank_array->size, 0);
    free_blank_array_full(blank_array);
}

TEST_F(BlankArrayTest, TestGetArray) {
    FILE *inp = fopen("inp.txt", "w");
    fprintf(inp, "3\n");
    fprintf(inp, "121;Russia, Moscow, str Street;Sergey; Melikyan;\n");
    fprintf(inp, "1;USA, Moscow, str Street; Jhon;Smit;\n");
    fprintf(inp, "13; Europe, Moscow, str Street;Monte;Negro;\n");
    fclose(inp);

    Blank_array *blank_array = NULL;
    FILE *inp1 = fopen("inp.txt", "r");
    ASSERT_TRUE(blank_array = get_blanks(inp, NULL));
    fclose(inp1);
    
    ASSERT_EQ(blank_array->size, 3);

    ASSERT_TRUE(blank_array->array[0]->number == 121);
    ASSERT_STREQ(blank_array->array[0]->storage_place, "Russia, Moscow, str Street");
    ASSERT_STREQ(blank_array->array[0]->responsible_name, "Sergey");
    ASSERT_STREQ(blank_array->array[0]->responsible_surname, "Melikyan");
    
    ASSERT_TRUE(blank_array->array[1]->number == 1);
    ASSERT_STREQ(blank_array->array[1]->storage_place, "USA, Moscow, str Street");
    ASSERT_STREQ(blank_array->array[1]->responsible_name, "Jhon");
    ASSERT_STREQ(blank_array->array[1]->responsible_surname, "Smit");
    
    ASSERT_TRUE(blank_array->array[2]->number == 13);
    ASSERT_STREQ(blank_array->array[2]->storage_place, "Europe, Moscow, str Street");
    ASSERT_STREQ(blank_array->array[2]->responsible_name, "Monte");
    ASSERT_STREQ(blank_array->array[2]->responsible_surname, "Negro");


    free_blank_array_full(blank_array);
}

class BlankPackTest : public ::testing::Test{
};

TEST_F(BlankPackTest, TestNewPack) {
    Blank_pack *blank_pack = new_blank_pack(0);
    ASSERT_TRUE(blank_pack);
    ASSERT_TRUE(blank_pack->blanks);
    ASSERT_TRUE(!blank_pack->next);
    ASSERT_TRUE(blank_pack->blanks->array);
    ASSERT_EQ(blank_pack->blanks->size, 0);
    free_blank_pack(blank_pack);
}

TEST_F(BlankPackTest, TestMergeSort) {
    FILE *inp = fopen("inp.txt", "w");
    fprintf(inp, "10\n");
    for (size_t i = 10; i > 0; i--) {
        fprintf(inp, "%lu;a;a;a;\n", i); 
    }
    fclose(inp);

    Blank_array *blank_array = NULL;
    FILE *inp1 = fopen("inp.txt", "r");
    ASSERT_TRUE(blank_array = get_blanks(inp, NULL));
    fclose(inp1);

    Blank **temp = (Blank **) calloc(10, sizeof(Blank *));
    ASSERT_TRUE(temp);

    Blank **result = merge_sort(blank_array->array, temp, 0, 9, is_less);

    for (size_t i = 0; i < 10; i++) {
        ASSERT_EQ(result[i]->number, i+1);
    }
    
    if (result == temp)
        std::swap(temp, blank_array->array);
    free(temp);
    free_blank_array_full(blank_array);    
}

TEST_F(BlankPackTest, TestPrintPacks) {
    FILE *inp = fopen("inp.txt", "w");
    fprintf(inp, "5\n");
    fprintf(inp, "5;Russia, Moscow, str Street;Sergey; Melikyan;\n");
    fprintf(inp, "1;USA, Moscow, str Street; Jhon;Smit;\n");
    fprintf(inp, "3; Europe, Moscow, str Street;Sergey; Melikyan;\n");
    fprintf(inp, "2; USA, Moscow, str Street;Jhon; Smit;\n");
    fprintf(inp, "4;Europe, Moscow, str Street;Sergey; Melikyan;\n");
    fclose(inp);

    Blank_pack *blank_pack = NULL;
    FILE *inp1 = fopen("inp.txt", "r");
    ASSERT_TRUE(blank_pack = get_packs(inp, NULL));
    fclose(inp1);

    FILE *out = fopen("out.txt", "w");
    print_packs(out, blank_pack);
    fclose(out);

    char strings[][100] = {
        {"Pack number 1:\n"},
        {"\tnumber: 1; storage: USA, Moscow, str Street; responsible: Jhon Smit\n"},
        {"\tnumber: 2; storage: USA, Moscow, str Street; responsible: Jhon Smit\n"},
        {"Pack number 2:\n"},
        {"\tnumber: 3; storage: Europe, Moscow, str Street; responsible: Sergey Melikyan\n"},
        {"\tnumber: 4; storage: Europe, Moscow, str Street; responsible: Sergey Melikyan\n"},
        {"Pack number 3:\n"},
        {"\tnumber: 5; storage: Russia, Moscow, str Street; responsible: Sergey Melikyan\n"},
    };

    FILE *out1 = fopen("out.txt", "r");
    char *buffer = (char *) calloc(256, sizeof(char));

    for (size_t i = 0; i < 8; i++) {
        fgets(buffer, 256, out1);
        ASSERT_STREQ(buffer, strings[i]);
    }
    
    fclose(out1);
    free_blank_pack(blank_pack);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

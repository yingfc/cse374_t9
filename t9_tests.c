#include "string.h"

#include "safe_assert.h"
#include "t9_lib.h"

void AssertReturnedStringEquals(char *expected, char *actual);

suite("T9") {
    test("Empty initialization") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);
        DestroyT9(dict);
    }

    test("Check whether add one # works") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "2665#");
        AssertReturnedStringEquals("cool", word);
    }

    test("Check add duplicated word") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "2665#");
        safe_assert(word != NULL);
        AssertReturnedStringEquals("cool", word);
    }

    test("Test if 'ac' is 22### in dictionary") {
        T9 *dict = InitializeFromFileT9("./dictionary.txt");
        safe_assert(dict != NULL);

        AddWordToT9(dict, "ac");
        char* word = PredictT9(dict, "22###");
        safe_assert(word != NULL);
        AssertReturnedStringEquals("ac", word);
    }

    test("Test PredictT9 with NULL") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, NULL);
        char* word = PredictT9(dict, NULL);
        safe_assert(word == NULL);
    }

    test("Initialize with invalid file") {
        T9 *dict = InitializeFromFileT9("./missing_dictionary.txt");
        safe_assert(dict == NULL);
    }

    test("Test PredictT9 with invalid character") {
        T9 *dict = InitializeFromFileT9("./small_dictionary.txt");
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "227!");
        safe_assert(word == NULL);
    }

    test("Test adding empty word") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "");
        char* word = PredictT9(dict, "");
        safe_assert(word == NULL);
        DestroyT9(dict);
    }

    test("Test adding uppercased word") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "CHEN");
        char* word = PredictT9(dict, "2436");
        safe_assert(word == NULL);
    }

    test("Test returned value of no word") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        char* word = PredictT9(dict, "2665#");
        safe_assert(word == NULL);
    }

    test("Initialize from small_dict file and reach till the end") {
        T9 *dict = InitializeFromFileT9("./small_dictionary.txt");
        safe_assert(dict != NULL);

        char* first = PredictT9(dict,"22738275");
        AssertReturnedStringEquals("aardvark", first);
        char* last = PredictT9(dict,"93272");
        AssertReturnedStringEquals("zebra", last);
    }
}

void AssertReturnedStringEquals(char *expected, char *actual) {
    safe_assert(actual > 0);
    safe_assert(strlen(actual) == strlen(expected));
    safe_assert(strcmp(actual, expected) == 0);
}
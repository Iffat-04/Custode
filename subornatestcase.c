#include <stdio.h>
#include <string.h>
#include "category_item.c"   // only the CRUD module, no main here

void resetData() {
    categoryCount = 0;
    itemCount = 0;
}

int test_add_category() {
    resetData();
    Category c = {1, "Electronics"};
    categories[categoryCount++] = c;

    int actual   = (categoryCount == 1 &&
                    categories[0].id == 1 &&
                    strcmp(categories[0].name, "Electronics") == 0);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_add_category -> expected:%d actual:%d success:%d\n",
           expected, actual, success);
    return success;
}

int test_find_category_index() {
    resetData();
    categories[0].id = 1; strcpy(categories[0].name, "Electronics");
    categories[1].id = 2; strcpy(categories[1].name, "Grocery");
    categoryCount = 2;

    int i1 = findCategoryIndexById(1);
    int i2 = findCategoryIndexById(2);
    int i3 = findCategoryIndexById(99);

    int actual   = (i1 == 0 && i2 == 1 && i3 == -1);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_find_category_index -> expected:%d actual:%d success:%d\n",
           expected, actual, success);
    return success;
}

int test_add_item_valid_category() {
    resetData();
    categories[0].id = 1;
    strcpy(categories[0].name, "Electronics");
    categoryCount = 1;

    Item it = {1, "Keyboard", 1, 10, 3, 1500.0f};
    items[itemCount++] = it;

    int idx = findItemIndexById(1);
    int actual   = (itemCount == 1 && idx == 0 &&
                    items[0].category_id == 1 &&
                    strcmp(items[0].name, "Keyboard") == 0);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_add_item_valid_category -> expected:%d actual:%d success:%d\n",
           expected, actual, success);
    return success;
}

int test_find_item_invalid_id() {
    resetData();
    items[0].id = 1;
    strcpy(items[0].name, "Mouse");
    items[0].category_id = 1;
    items[0].quantity = 5;
    items[0].reorder_level = 2;
    items[0].price = 800.0f;
    itemCount = 1;

    int idx = findItemIndexById(99);
    int actual   = (idx == -1);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_find_item_invalid_id -> expected:%d actual:%d success:%d\n",
           expected, actual, success);
    return success;
}

int main(void) {
    int ok = 1;
    ok &= test_add_category();
    ok &= test_find_category_index();
    ok &= test_add_item_valid_category();
    ok &= test_find_item_invalid_id();

    if (!ok) {
        printf("Some tests failed\n");
        return 1;
    }
    printf("All tests passed\n");
    return 0;
}
// ...existing code...

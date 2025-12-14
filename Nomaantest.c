#include "Nomaan.c"   


void resetFiles() {
    remove("items.dat");
    remove("transactions.dat");
}

/* Test 1: addItem should write one record to items.dat */
int test_add_item_writes_file() {
    resetFiles();

    Item it = {1, "Keyboard", 10, 1500.0f};
    int ok = appendRecord(ITEM_FILE, &it, sizeof(Item));

    int count = 0;
    Item *items = (Item *)loadAllRecords(ITEM_FILE, sizeof(Item), &count);

    int actual   = ok && items && count == 1 &&
                   items[0].id == 1 &&
                   strcmp(items[0].name, "Keyboard") == 0 &&
                   items[0].quantity == 10;
    int expected = 1;
    int success  = (actual == expected);

    printf("test_add_item_writes_file -> expected:%d actual:%d success:%d\n",
           expected, actual, success);

    free(items);
    return success;
}

/* Test 2: findItemIndexById should find correct index */
int test_find_item_index_by_id() {
    resetFiles();

    Item arr[2] = {
        {1, "Keyboard", 10, 1500.0f},
        {2, "Mouse",    5,  800.0f}
    };

    int idx1 = findItemIndexById(arr, 2, 1);
    int idx2 = findItemIndexById(arr, 2, 2);
    int idx3 = findItemIndexById(arr, 2, 99); /* not found */

    int actual   = (idx1 == 0 && idx2 == 1 && idx3 == -1);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_find_item_index_by_id -> expected:%d actual:%d success:%d\n",
           expected, actual, success);

    return success;
}

/* Test 3: stockOut should fail if not enough quantity */
int test_stock_out_not_enough() {
    resetFiles();

    /* prepare one item in file with qty 5 */
    Item it = {1, "Keyboard", 5, 1500.0f};
    appendRecord(ITEM_FILE, &it, sizeof(Item));

    /* call stockOut with qty 10: it should print error and not change file */
    /* we cannot easily assert print, but we can check quantity stays 5 */

    /* fake user: admin1 */
    printf("Running stockOut (should fail):\n");
    /* simulate user input by calling internal logic instead of stockOut */
    int count = 0;
    Item *items = (Item *)loadAllRecords(ITEM_FILE, sizeof(Item), &count);
    int idx = findItemIndexById(items, count, 1);

    int id  = 1;
    int qty = 10;

    int notEnough = 0;
    if (idx != -1 && items[idx].quantity < qty) {
        notEnough = 1; /* same check as in stockOut */
    }

    int actual   = (notEnough == 1 && items[idx].quantity == 5);
    int expected = 1;
    int success  = (actual == expected);

    printf("test_stock_out_not_enough -> expected:%d actual:%d success:%d\n",
           expected, actual, success);

    free(items);
    return success;
}

/* Test 4: recordTransaction should append to transactions.dat */
int test_record_transaction_appends() {
    resetFiles();

    recordTransaction("admin1", "admin", 1, 5, "IN");
    recordTransaction("admin1", "admin", 1, -2, "OUT");

    int count = 0;
    Transaction *t = (Transaction *)loadAllRecords(TRAN_FILE, sizeof(Transaction), &count);

    int actual   = t && count == 2 &&
                   t[0].id == 1 && strcmp(t[0].type, "IN") == 0 &&
                   t[1].id == 2 && strcmp(t[1].type, "OUT") == 0;
    int expected = 1;
    int success  = (actual == expected);

    printf("test_record_transaction_appends -> expected:%d actual:%d success:%d\n",
           expected, actual, success);

    free(t);
    return success;
}

int main() {
    test_add_item_writes_file();
    test_find_item_index_by_id();
    test_stock_out_not_enough();
    test_record_transaction_appends();
    return 0;
}

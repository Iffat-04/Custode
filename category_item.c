typedef struct {
    int id;
    char name[50];
} Category;

typedef struct {
    int id;
    char name[50];
    int category_id;
    int quantity;
    int reorder_level;
    float price;
} Item;
#define MAX_CATEGORIES 50
#define MAX_ITEMS 200

Category categories[MAX_CATEGORIES];
Item items[MAX_ITEMS];

int categoryCount = 0;
int itemCount = 0;
void inputString(char *s, int size);
void addCategory();
void listCategories();
int  findCategoryIndexById(int id);
void editCategory();
void deleteCategory();

void addItem();
int  findItemIndexById(int id);
void editItem();
void deleteItem();
void listItems();
void searchItem();

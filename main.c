#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The data file will have the following format:
// 20
// name1 company1 quantity1 price1 category1
// name2 company2 quantity2 price2 category2
// ...
// Where the first line specifies the length of the array.

struct Item{ // Creating the item object
    char* name;
    char* company;
    int quantity;
    float price;
    char* category;
};

struct Item make_item(char* name, char* company,int quantity, float price, char* category){ // Item object creation function
    struct Item temp;
    // +1 for the null terminator
    temp.name = malloc(strlen(name) + 1);
    strcpy(temp.name, name);

    temp.company = malloc(strlen(company) + 1);
    strcpy(temp.company, company);

    temp.quantity = quantity;
    temp.price = price;

    temp.category = malloc(strlen(category) + 1);
    strcpy(temp.category, category);

    return temp;
}





void clear_screen(){ // Function for a pseudo-clear of the screen
    for (int i = 0; i < 100; i++){
        printf("\n");
    }
}

void quit_program(){ //Self-explanatory
    printf("Exiting program...\n");
    exit(0);
}

void change_default_file(char* new_file){ // Function in case we want to use an already prepared file instead of adding the items one by one
    FILE *setting = fopen("../setting.txt", "w");
    if (setting == NULL){
        printf("\nThere was an error accessing the setting file!");
        return;
    }
    printf("\nSetting file accessed successfully");
    fprintf(setting, new_file);
    fclose(setting);
}



void display_items(struct Item** array, int array_length){ // Function for displaying the items
        printf("%-25s || %-25s || %-10s || %-10s || %-10s\n", "Name", "Company", "Quantity", "Price", "Category");
    for(int i = 0; i < array_length; i++){

        char numStr[20];
        sprintf(numStr, "%.2f", array[i]->price);
        snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
        strcat(numStr, "$");

        printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);
    }

}


void display_items_by_a_filter(struct Item** array, int array_length, char filter, void *filter_value, int condition){ // Function for displaying the items via a filter
    printf("%-25s || %-25s || %-10s || %-10s || %-10s\n", "Name", "Company", "Quantity", "Price", "Category");
    switch(filter){
        case 'c': {
            char *value = (char *) filter_value;
            for (int i = 0; i < array_length; i++) {
                if (!strcmp(array[i]->category, value)) {

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);
                }
            }
            break;
        }
        case 'q': {
            int value = *(int *) filter_value;
            for (int i = 0; i < array_length; i++) {
                if (condition && array[i]->quantity >= value) {

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);

                } else if(!condition && array[i]->quantity <= value){

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);

                }
            }
            break;
        }
        case 'p': {
            float value = *(float *) filter_value;
            for (int i = 0; i < array_length; i++) {
                if (condition && array[i]->price >= value) {

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);

                } else if(!condition && array[i]->price <= value){

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);

                }
            }
            break;
        }
        case 'm': {
            char *value = (char *) filter_value;
            for (int i = 0; i < array_length; i++) {
                if (!strcmp(array[i]->company, value)) {

                    char numStr[20];
                    sprintf(numStr, "%.2f", array[i]->price);
                    snprintf(numStr, sizeof(numStr), "%.2f", array[i]->price);
                    strcat(numStr, "$");

                    printf("%-25s || %-25s || %-10d || %-10s || %-10s\n", array[i]->name, array[i]->company, array[i]->quantity, numStr,  array[i]->category);

                }
            }
            break;
        }
        default:
            printf("???");
            break;
    }
}

void add_item_to_array(struct Item*** array, struct Item* item, int* array_length){ // Adding an item to the item array
    *array_length = *array_length + 1;
    *array = realloc(*array, *array_length*sizeof(struct Item*));
    (*array)[(*array_length)-1] = item;
    //update_file
}

void remove_item_from_array(struct Item*** array, char* name, char* company, int* array_length){ // Removing an item
    int index = -1;
    for (int i = 0; i < *array_length; i++){
        if (!(strcmp((*array)[i]->name, name) && strcmp((*array)[i]->company, company))){
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("Item was not found");
        return;

    }
    for (int j = index; j < *array_length; j++){
        (*array)[j] = (*array)[j+1];
    }
    *array_length = *array_length - 1;
    (*array) = realloc(*array, *array_length * sizeof(struct Item*));

}

int check_if_in_array(struct Item** array, char* name, char* company, int array_length) { // Check function which also return the index which the item was found on
    int index = -1;
    for (int i = 0; i < array_length; i++) {
        if (!(strcmp(array[i]->name, name) && strcmp(array[i]->company, company)) ) {
            index = i;
            break;
        }
    }
    return index;
}

void update_item_in_array(struct Item** array, int index, int choice){ // Update
    switch (choice){
        case 1: {
            char name[100];
            printf("\nInput new name:");
            gets(name);
            strcpy(array[index]->name, name);
            break;

        }
        case 2: {
            char company[100];
            printf("\nInput new company:");
            gets(company);
            strcpy(array[index]->company, company);
            break;

        }
        case 3: {
            int quantity;
            printf("\nInput new quantity:");
            scanf("%d", &quantity);
            getchar();
            array[index]->quantity = quantity;
            break;

        }
        case 4: {
            float price;
            printf("\nInput new price:");
            scanf("%f", &price);
            getchar();
            array[index]->price = price;
            break;

        }
        case 5: {
            char category[100];
            printf("\nInput new company:");
            gets(category);
            strcpy(array[index]->category, category);
            break;

        }
    }

}

void sort_array_by_criterion(struct Item** array, int array_length, int choice){ // Sorting the array
    switch (choice){
        case 1:{
            for (int i = 0; i < array_length; i++){
                for (int j = i; j < array_length; j++){
                    if (strcmp(array[i]->name, array[j]->name) > 0){
                        struct Item* temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }

            }
            break;
        }
        case 2:{
            for (int i = 0; i < array_length; i++){
                for (int j = i; j < array_length; j++){
                    if (array[i]->quantity > array[j]->quantity){
                        struct Item* temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }

            }
            break;
        }
        case 3:{
            for (int i = 0; i < array_length; i++){
                for (int j = i; j < array_length; j++){
                    if (array[i]->price > array[j]->price){
                        struct Item* temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }

            }
            break;
        }
    }

}




int main() {
    char directory[100] = "../Inventory/"; // Base of the directory set up specifically for the default file change
    char* file_name;
    FILE *name = fopen("../setting.txt", "r");
    if (name == NULL){
        printf("There was an error accessing the setting file!");
        return 1;
    }

    fseek(name, 0L, SEEK_END);
    int numbytes = ftell(name);
    fseek(name, 0L, SEEK_SET);

    file_name = (char*)calloc(numbytes, sizeof(char));
    if (file_name == NULL){
        printf("no mem alloc");
        return 1;
    }
    // Taking advantage of the fact we can pass in a string variable into fopen so we can use the change_default_file function
    fread(file_name, sizeof(char), numbytes, name);
    fclose(name);

    strcat(directory, file_name);



    int option;
    printf("Accessing inventory data...");
    FILE *inv_data = fopen(directory, "r");


    struct Item** item_array = NULL; // The items will be stored in the program / memory via an array of pointers to the item structs
    int num_items = 0;


    if (!inv_data){
        printf("Failed to access / find data file. Continuing..\n");
        printf("Press any key to continue...");
        getchar();
        clear_screen();
    } else{
        printf("Data file accessed successfully.\n");



        fscanf(inv_data, "%d", &num_items);
        item_array = (struct Item**) malloc(num_items * sizeof(struct Item*));
        if (item_array == NULL) {
            printf("Error allocating item array memory\n");
            exit(1);
        }


        for (int i = 0; i < num_items; i++) { // Reading the items from the file and adding them to the array
            char name[100];
            char company[100];
            int quantity;
            float price;
            char category[100];

            fscanf(inv_data, "%s %s %d %f %s", name, company, &quantity, &price, category);

            // Allocate memory for the strings in the item struct
            item_array[i] = (struct Item*) malloc(sizeof(struct Item));
            if (item_array[i] == NULL) {
                printf("Error allocating memory\n");
                exit(1);
            }

            item_array[i][0] = make_item(name, company, quantity, price, category); // Pretty cool
        }

        printf("Press any key to continue...");
        getchar();
        clear_screen();
    }





    fclose(inv_data);

    while (1) {  // Infinite loop




        printf("|======Inventory Management System======|\n");
        printf("1. Display all items\n");
        printf("2. Display items with low quantity\n");
        printf("3. Display items with a filter\n");
        printf("4. Sort items\n");
        printf("5. Add item\n");
        printf("6. Update item\n");
        printf("7. Remove item\n");
        printf("8. Change default data file\n");
        printf("9. Help\n");
        printf("10. Quit program\n");
        printf("Enter option:");
        scanf("%d", &option);

        switch (option) {
            case 1:
                clear_screen();
                getchar();
                printf("|======Display all items======|");
                printf("\n");
                display_items(item_array, num_items);
                printf("\nPress any key to continue...");
                getchar();
                break;
            case 2:
                clear_screen();
                printf("|======Display items with low quantity======|\n");
                int criteria;
                printf("Enter criteria for low quantity:");
                scanf("%d", &criteria);
                getchar();
                printf("\n");
                display_items_by_a_filter(item_array, num_items, 'q', &criteria, 0);
                printf("\nPress any key to continue...");
                getchar();
                clear_screen();
                break;
            case 3:
                clear_screen();
                printf("|======Display items with a filter======|\n");
                printf("1. Filter by category\n");
                printf("2. Filter by price\n");
                printf("3. Filter by quantity\n");
                printf("4. Filter by company\n");
                printf("5. Back\n");
                printf("Enter option:");
                scanf("%d", &option);
                switch (option) {
                    case 1:
                        printf("Enter category:");
                        getchar();
                        char categ[100];
                        gets(categ);
                        display_items_by_a_filter(item_array, num_items, 'c', &categ, 0);
                        printf("\nPress any key to continue...");
                        getchar();
                        clear_screen();
                        break;

                    case 2:
                        printf("Enter price:");
                        float pr;
                        char choice;
                        scanf("%f", &pr);
                        printf("Enter 'a' for over that price or 'b' for under:");
                        scanf(" %c", &choice);
                        getchar();
                        if (choice == 'a'){
                            display_items_by_a_filter(item_array, num_items, 'p', &pr, 1);
                        } else if(choice == 'b') {
                            display_items_by_a_filter(item_array, num_items, 'p', &pr, 0);
                        }
                        printf("\nPress any key to continue...");
                        getchar();
                        clear_screen();
                        break;

                    case 3:
                        printf("Enter quantity:");
                        int qu;
                        char choice2;
                        scanf("%d", &qu);
                        printf("Enter 'a' for over that quantity or 'b' for under:");
                        scanf(" %c", &choice2);
                        getchar();
                        if (choice2 == 'a'){
                            display_items_by_a_filter(item_array, num_items, 'q', &qu, 1);
                        } else if(choice2 == 'b') {
                            display_items_by_a_filter(item_array, num_items, 'q', &qu, 0);
                        }
                        printf("\nPress any key to continue...");
                        getchar();
                        clear_screen();
                        break;

                    case 4:
                        printf("Enter company:");
                        getchar();
                        char comp[100];
                        gets(comp);
                        display_items_by_a_filter(item_array, num_items, 'm', &comp, 0);
                        printf("\nPress any key to continue...");
                        getchar();
                        clear_screen();
                        break;

                    case 5:
                        break;

                    default:
                        getchar();
                        printf("Invalid option. Press any key to continue...");
                        getchar();
                        clear_screen();
                        break;
                }

                break;

            case 4: {
                clear_screen();
                int choice;
                printf("|======Sort items======|\n");
                printf("1. Sort by name\n");
                printf("2. Sort by quantity\n");
                printf("3. Sort by price\n");
                printf("Enter the criterion by which to sort:");
                scanf("%d", &choice);
                getchar();

                if(choice < 1 || choice >3){
                    printf("\nInvalid option");
                    printf("\nPress any key to continue...");
                    getchar();
                    break;
                }

                sort_array_by_criterion(item_array, num_items, choice);

                char inpt;
                printf("Do you wish to display the items right now?\n");
                printf("Y - Yes\n");
                printf("Anything else - No\n");
                scanf("%c", &inpt);
                getchar();
                if (inpt == 'Y' || inpt == 'y'){
                    clear_screen();
                    display_items(item_array, num_items);
                }

                printf("\nPress any key to continue...");
                getchar();
                break;

            }

            case 6: {
                clear_screen();
                char name[100], company[100];
                getchar();
                printf("|======Update item======|\n");
                printf("Enter the name:");
                gets(name);
                printf("Enter the company:");
                gets(company);
                int check = check_if_in_array(item_array, name, company, num_items);
                if (check > -1){
                    int choice;
                    printf("\n1. Edit name\n");
                    printf("2. Edit company\n");
                    printf("3. Edit quantity\n");
                    printf("4. Edit price\n");
                    printf("5. Edit category\n");
                    printf("Enter your choice:");
                    scanf("%d", &choice);
                    getchar();

                    if(choice < 1 || choice > 5){
                        printf("\nInvalid option");
                        printf("\nPress any key to continue...");
                        getchar();
                        break;
                    }

                    update_item_in_array(item_array, check, choice);

                    printf("\nPress any key to continue...");
                    getchar();
                    break;
                    //update item


                }
                else {
                    printf("Item was not found");
                    printf("\nPress any key to continue...");
                    getchar();
                    break;
                }

            }

            case 5: {
                char name[100], company[100], category[100];
                float price;
                int quantity;

                getchar();
                printf("|======Add item======|\n");
                printf("Enter the name:");
                gets(name);
                printf("Enter the company:");
                gets(company);
                printf("Enter the quantity:");
                scanf("%d", &quantity);
                printf("Enter the price:");
                scanf("%f", &price);
                getchar();
                printf("Enter the category:");
                gets(category);

                struct Item new_item = make_item(name, company, quantity, price, category);
                add_item_to_array(&item_array, &new_item, &num_items);

                printf("\nPress any key to continue...");
                getchar();
                break;
            }
            case 7: {
                clear_screen();
                char name[100], company[100];
                getchar();
                printf("|======Remove item======|\n");
                printf("Enter the name of the item you want to remove:");
                gets(name);
                printf("Enter the name of the item you want to remove:");
                gets(company);
                remove_item_from_array(&item_array, name, company, &num_items);
                printf("\nPress any key to continue...");
                getchar();
                break;
            }
            case 8: {
                clear_screen();
                getchar();
                char f_name[100];
                printf("|======Change default data file|======\n");
                printf("Enter the name of the data file you want to change to:");
                gets(f_name);
                change_default_file(f_name);
                printf("\nThe program will now restart...");
                printf("\nPress any key to continue...");
                getchar();

                for (int i = 0; i < num_items; i++) {
                    free(item_array[i]->name);
                    free(item_array[i]->company);
                    free(item_array[i]->category);
                    free(item_array[i]);
                }
                free(item_array);

                quit_program();
                break;
            }
            case 9:
                clear_screen();
                getchar();
                printf("|======Help Section======|\n");
                printf("The maximum character size for the names, companies and categories of the items is 100. Also, make sure not to input anything else other than numbers\n\n");
                printf("All data files will have to conform to the following format:\n");
                printf("== number_of_items                           ==\n");
                printf("== name1 company1 quantity1 price1 category1 ==\n");
                printf("== name2 company2 quantity2 price2 category2 ==\n");
                printf("== ...                                       ==\n\n\n");
                printf("Very important! The name, company and category of an item cannot contain an whitespace. If they contain multiple words, they shall be separated by underscored '_'.\n\n");
                printf("Two items cannot have the same name if they come from the same company. They can however have the same name if they have different companies.\n\n");
                printf("If at any point the program crashes before even the main menu can appear, delete the contents of the file 'setting.txt', thus resuming control of the program, and contact me. Also contact me if it crashes in any other situation.\n");
                printf("\nPress any key to continue...");
                getchar();
                break;
            case 10:
                for (int i = 0; i < num_items; i++) {
                    free(item_array[i]->name);
                    free(item_array[i]->company);
                    free(item_array[i]->category);
                    free(item_array[i]);
                }
                free(item_array);

                quit_program();
                break;
            default:
                getchar();
                printf("Invalid option. Press any key to continue...");
                getchar();
                clear_screen();
                break;
        }

        inv_data = fopen(directory, "w");
        if (inv_data == NULL) {
            printf("Error opening file\n");
            exit(1);
        }

        // Write the number of items to the file
        fprintf(inv_data, "%d\n", num_items);

        // Write the items to the file
        for (int i = 0; i < num_items; i++) {
            struct Item* item = item_array[i];

            fprintf(inv_data, "%s %s %d %f %s\n", item->name, item->company, item->quantity, item->price, item->category);
        }

        fclose(inv_data);
        clear_screen();
    }

    return 0;
}

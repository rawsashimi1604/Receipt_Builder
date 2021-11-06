#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getDateTime.h"

#define MAXITEMS 100
#define MAXNAME 46
#define MAXLINE 62
#define RECEIPTCHARS 4096
#define TAXRATE 0.07

void addItem(char items[MAXITEMS][MAXNAME], float prices[MAXITEMS], int qty[MAXITEMS], int* currItemIndex);
void setupReceipt(char* receipt);
void setupDateTime(char* receipt, char* date, char* time);
void setupDetails(char* receipt);
void setupItems(char* receipt, char items[MAXITEMS][MAXNAME], float prices[MAXITEMS], int qty[MAXITEMS], int* currItemIndex);

char* Line = "**************************************************************\n";

int main() {
    char* receipt = (char*)calloc(RECEIPTCHARS, sizeof(char));

    // Define arrays to store items, prices and quantity in
    char itemArray[MAXITEMS][MAXNAME]; // pointer to array of maxitems with maxname LEN
    float priceArray[MAXITEMS];
    int qtyArray[MAXITEMS];
    int itemCount = 0;

    addItem(itemArray, priceArray, qtyArray, &itemCount); // Dereference itemArray to point to string with maxname LEN

    // Get current date and time
    char* currentDate = getCurrentDate();
    char* currentTime = getCurrentTime();
    
    // Setup Receipt
    setupReceipt(receipt);
    setupDateTime(receipt, currentDate, currentTime);
    setupDetails(receipt);
    setupItems(receipt, itemArray, priceArray, qtyArray, &itemCount);
    printf("%s", receipt);
    free(receipt);
    return 0;
}

// Adds item to array
void addItem(char items[MAXITEMS][MAXNAME], float prices[MAXITEMS], int qty[MAXITEMS], int* currItemIndex) {

    // Get item
    char* tmp_item = (char*)malloc(MAXNAME * sizeof(char));
    printf("Enter your item here: ");
    fgets(tmp_item, MAXNAME, stdin);
    tmp_item[strcspn(tmp_item, "\n")] = 0; // remove '\n' character from tmp_item entered by stdin

    // Get price
    float* tmp_price = (float*)malloc(sizeof(float));
    printf("Enter your item price here: ");
    scanf(" %f", tmp_price);

    // Get quantity
    int* tmp_qty = (int*)malloc(sizeof(int));
    printf("Enter your item quantity here: ");
    scanf(" %d", tmp_qty);

    // Store into array
    for (int i = 0; i < strlen(tmp_item) + 1; i++) {
        items[*currItemIndex][i] = tmp_item[i];
    }

    prices[*currItemIndex] = *tmp_price;
    qty[*currItemIndex] = *tmp_qty;
    
    free(tmp_item);
    free(tmp_price);
    free(tmp_qty);

    printf("Item added!\n");

    *currItemIndex += 1;

    fflush(stdin); // flush stdin to accomodate fgets()
}

// Adds array items onto receipt
void setupItems(char* receipt, char items[MAXITEMS][MAXNAME], float prices[MAXITEMS], int qty[MAXITEMS], int* currItemIndex) {
    for (int i = 0; i < *currItemIndex; i++) {
        char* currLine = malloc(sizeof(char) * MAXLINE);
        sprintf(currLine, "%-3d | %-46s | $%4.2f\n", qty[i], *(items + i), prices[i]);
        strcat(receipt, currLine);
        free(currLine);
    }
}

void setupReceipt(char* receipt) {
    strcat(receipt, Line);
    strcat(receipt, "Welcome to Receipt Printer!\n");
    strcat(receipt, Line);
}

void setupDateTime(char* receipt, char* date, char* time) {
    // Initialize tmp_strings in heap to store date and time
    char* dateLine = (char*)malloc(MAXLINE * sizeof(char));
    strcpy(dateLine, "Current date is ");
    char* timeLine = (char*)malloc(MAXLINE * sizeof(char));
    strcpy(timeLine, "Current date is ");

    // Create date line to add to receipt, with new line
    strcat(dateLine, date);
    strcat(dateLine, ".\n");
    
    // Create time line to add to receipt, with new line
    strcat(timeLine, time);
    strcat(timeLine, ".\n");

    // Append to receipt
    strcat(receipt, dateLine);
    strcat(receipt, timeLine);
    strcat(receipt, Line);

    free(dateLine);
    free(timeLine);
}

void setupDetails(char* receipt) {
    char* detailsRow = (char*)malloc(sizeof(char) * MAXLINE);
    sprintf(detailsRow, "%-3s | %-46s | %4s\n", "QTY", "ITEM DESCRIPTION", "PRICE");
    strcat(receipt, detailsRow);

    free(detailsRow);
}

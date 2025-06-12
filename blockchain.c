#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// TODO: Implement a simple hash function or use a real one
void simple_hash(char *input, char *output) {
    // Simulate a hash by processing the input string
    unsigned int hash =0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash = hash * 31 + input[i];
    }

    // Hash second string
    snprintf(output, 64, "%u", hash);
}

// Block structure
typedef struct Block {
    int index;
    char timestamp[100];
    char data[256];
    char previousHash[256];
    char hash[256];
    struct Block* next;
} Block;

// TODO: Fill this to get current time in string format
void get_timestamp(char *buffer) {
    // Fill buffer with current date-time

    time_t now = time(NULL);                  
    struct tm *t = localtime(&now);           

    // Format: YYYY-MM-DD HH:MM:SS
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", t);
}

// TODO: Implement logic to create a new block
Block* create_block(int index, char *data, char *previousHash) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    // Fill the block fields (index, data, timestamp, previousHash)
    newBlock->index = index;
    strncpy(newBlock->data,data,sizeof(newBlock->data));
    strncpy(newBlock->previousHash,previousHash,sizeof(newBlock->previousHash));


    get_timestamp(newBlock->timestamp);

    // Create a string from block data to hash
    char Blockstr[1024];
    snprintf(Blockstr,sizeof(Blockstr), "%d%s%s%s",index,data,newBlock->timestamp,previousHash);

    // Call simple_hash on the string and store in block->hash
    simple_hash(Blockstr,newBlock->hash);
    
    newBlock->next = NULL;
    return newBlock;
}

// TODO: Implement logic to add a block to the chain
void add_block(Block **head, char *data) {
    // Traverse to the last block
    if(*head == NULL){
        *head = create_block(0, data, "0");
        return;
    }

    Block *current = *head; 
    while (current->next != NULL) {
        current = current->next;
    }
    // Get index and previousHash
    int newIndex = current->index + 1;
    char *prevHash = current->hash;
    // Call create_block and link the new block
    Block *newBlock = create_block(newIndex, data, prevHash);
    current->next = newBlock;
    
}

// TODO: Print all blocks in the blockchain
void print_chain(Block *head) {
    // Traverse the chain and print block details
    Block *current = head;
    while (current != NULL) {
        printf("------------\n");
        printf("Block #%d\n", current->index);
        printf("Data: %s\n", current->data);
        printf("Timestamp: %s\n", current->timestamp);
        printf("Previous Hash: %s\n", current->previousHash);
        printf("Hash: %s\n", current->hash);
        current = current->next;
    }
    printf("------------\n");
}

void free_chain(Block* head) {
    Block* current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

int main() {
    Block* blockchain = NULL;

    // TODO: Add a few blocks with sample data
    char timestamp[100];
    get_timestamp(timestamp);

    printf("Current Timestamp: %s\n", timestamp);

    // add_block(&blockchain, "Genesis Block");
    add_block(&blockchain, "Genesis Block");
    // add_block(&blockchain, "Sample transaction");
    add_block(&blockchain, "Sample transaction");

    // TODO: Print the chain
    print_chain(blockchain);


    // print_chain(blockchain);

    // TODO: Free the chain
    free_chain(blockchain);
    return 0;
}

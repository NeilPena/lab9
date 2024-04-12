//Name: Neil Pena
//Date: 04/09/2024
//Assignment: Lab 9 


#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 23

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* records; 
	int* occupied; 

};

// Compute the hash function
int hash(int x)
{
	return x % HASH_SIZE; 

}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if (pHashArray -> occupied[i])
        {
            printf("Index %d -> %d %c %d\n", i, pHashArray -> records[i].id, pHashArray -> records[i].name, pHashArray -> records[i].order);
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9-1.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	struct HashType hashTable; 

	hashTable.records = (struct RecordType*)malloc(sizeof(struct RecordType) * HASH_SIZE);  
	hashTable.occupied = (int *)malloc(sizeof(int) * HASH_SIZE); 

	for(int i = 0; i < recordSz; i++){

		int index = hash(pRecords[i].id); 
		int initialIndex = index; 

		while(hashTable.occupied[index]){
        	index = (index + 1) % HASH_SIZE; 
        	if(index == initialIndex){
           		break; // Exit the loop if we looped through the entire hash table once without finding an empty slot
       		}
    	}

    hashTable.records[index] = pRecords[i]; 
    hashTable.occupied[index] = 1; 

	}

	displayRecordsInHash(&hashTable, HASH_SIZE);

	free(pRecords);
	free(hashTable.records);
	free(hashTable.occupied); 

	return 0;  

}
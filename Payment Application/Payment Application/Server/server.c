#include "server.h"


ST_accountsDB_t accountsDB[255]={ {2000.0, RUNNING, "8989374615436851"} , {5000.0, RUNNING, "9001712516434801"} , 
{4500.0, RUNNING, "3691176429124631"} , {24000, RUNNING, "4562606230524624"} , {10000.0, RUNNING, "1049912233401353"} , 
{43000.0, BLOCKED, "0457857916734490"} , {32000.0, BLOCKED, "1217454752901895"} , {9800.0, BLOCKED, "4570168687077347"} ,
{7600.0, BLOCKED, "1812104267658534"} , {22000.0, BLOCKED, "2084832381181941"} };

ST_transaction_t transactionsDB[255] = { 0, 0, 0, 0};
uint8_t ct = 0;

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence) {
	bool check = false;
	for (int i = 0; i < 255;i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
			check = true;
			//*accountRefrence = malloc(sizeof(accountsDB[i]));
			*accountRefrence = &accountsDB[i];
			break;
		}
		else {
			check = false;
			*accountRefrence = NULL;
		}
	}
	return (check == true) ? SERVER_OK : ACCOUNT_NOT_FOUND;
}
void isValidAccountTest() {
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isValidAccount");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", "4562606230524624", SERVER_OK);
	ST_cardData_t cd = { "", "4562606230524624", "" };
	ST_accountsDB_t ar;
	printf("\nActual Result: %d", isValidAccount(&cd, &ar));
	//case 2
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isValidAccount");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "4562606230334624", ACCOUNT_NOT_FOUND);
	strncpy(cd.primaryAccountNumber, "4562606230334624", 19);
	printf("\nActual Result: %d", isValidAccount(&cd, &ar));
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == RUNNING) {
		return SERVER_OK;
	}
	else if (accountRefrence->state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	else {
		return ACCOUNT_NOT_FOUND;
	}
}
void isBlockedAccountTest() {
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isBlockedAccount");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", "running account reference", SERVER_OK);
	ST_accountsDB_t acc;
	acc.state = RUNNING;
	printf("\nActual Result: %d", isBlockedAccount(&acc));
	//case 2
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isBlockedAccount");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "blocked account reference", BLOCKED_ACCOUNT);
	acc.state = BLOCKED;
	printf("\nActual Result: %d", isBlockedAccount(&acc));
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if ((*termData).transAmount > (*accountRefrence).balance) {
		return LOW_BALANCE;
	}
	else {
		return SERVER_OK;
	}
}
void isAmountAvailableTest() {
	ST_terminalData_t td;
	ST_accountsDB_t ar;
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isAmountAvailable");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", "balance: 20000, transfere amount: 15000", SERVER_OK);
	ar.balance = 20000;
	td.transAmount = 15000;
	printf("\nActual Result: %d", isAmountAvailable(&td, &ar));
	//case 2
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isAmountAvailable");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "balance: 10000, transfere amount: 15000", LOW_BALANCE);
	ar.balance = 10000;
	td.transAmount = 15000;
	printf("\nActual Result: %d", isAmountAvailable(&td, &ar));
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	bool check = false;
	int i = 0;
	for (; i < 255; i++) {
		if (transactionsDB[i].transactionSequenceNumber == 0) {
			check = true;
			break;
		}
		else {
			check = false;
		}
	}
	if (check == false) {
		return SAVING_FAILED;
	}
	else {
		transactionsDB[i].cardHolderData = (*transData).cardHolderData;
		transactionsDB[i].terminalData = (*transData).terminalData;
		transactionsDB[i].transactionSequenceNumber = ++ct;
		transactionsDB[i].transState = (*transData).transState;
		return SERVER_OK;
	}
}
void saveTransactionTest() {
	ST_transaction_t transData;
	transactionsDB[254].transactionSequenceNumber = 0;
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: saveTransaction");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", "Save Success", SERVER_OK);
	printf("\nActual Result: %d", saveTransaction(&transData));
	//case 2
	for (int i = 0; i < 255; i++) {
		transactionsDB[i].transactionSequenceNumber = 1;
	}
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: saveTransaction");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "Save Failed", SAVING_FAILED);
	printf("\nActual Result: %d", saveTransaction(&transData));
}

void listSavedTransactions(void) {
	for (int i = 0; i < 255; i++) {
		if (transactionsDB[i].transactionSequenceNumber > 0) {
			printf("#########################\nTransaction Sequence Number: %d\nTransaction Date: %s\nTransaction Amount: %.2f\nTransaction State: %d", 
				transactionsDB[i].transactionSequenceNumber, transactionsDB[i].terminalData.transactionDate, transactionsDB[i].terminalData.transAmount, 
				transactionsDB[i].transState);
			printf("\nTerminal Max Amount: %.2f\nCardholder Name: %s\nPAN: %s\nCard Expiration Date: %s\n#########################", 
				transactionsDB[i].terminalData.maxTransAmount, transactionsDB[i].cardHolderData.cardHolderName, 
				transactionsDB[i].cardHolderData.primaryAccountNumber, transactionsDB[i].cardHolderData.cardExpirationDate);
		}
	}
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	ST_accountsDB_t* ptr = &accountsDB[0];
	for (int i = 0; i < 255; i++) {
		if (isValidAccount(&(*transData).cardHolderData, &ptr) == ACCOUNT_NOT_FOUND) {
			return FRAUD_CARD;
		}
		else if (isAmountAvailable(&(*transData).terminalData.transAmount, ptr) == LOW_BALANCE) {
			return DECLINED_INSUFFECIENT_FUND;
		}
		else if (isBlockedAccount(ptr) == BLOCKED_ACCOUNT) {
			return DECLINED_STOLEN_CARD;
		}
		else {
			for (int j = 0; j < 255; j++) {
				if (strcmp((*transData).cardHolderData.primaryAccountNumber, accountsDB[j].primaryAccountNumber) == 0) {
					accountsDB[j].balance -= (*transData).terminalData.transAmount;
					break;
				}
			}
			return APPROVED;
		}
	}
}
void recieveTransactionDataTest() {
	ST_cardData_t cd = { "Abdulrahman Omar Ahmed", "826493054732823684", "05/25" };
	ST_transaction_t transData;
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: recieveTransactionData");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", "Fraud Card", FRAUD_CARD);
	transData.cardHolderData = cd;
	transData.terminalData.transAmount = 3000.f;
	printf("\nActual Result: %d", recieveTransactionData(&transData));
	//case 2
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: recieveTransactionData");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "Low Balance", DECLINED_INSUFFECIENT_FUND);
	ST_cardData_t cd2 = { "Abdulrahman Omar Ahmed", "8989374615436851", "05/25" }; 
	transData.cardHolderData = cd2;
	transData.terminalData.transAmount = 3500.f;
	printf("\nActual Result: %d", recieveTransactionData(&transData));
	//case 3
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: recieveTransactionData");
	printf("\nTest Case 3:");
	printf("\nInput Data: %s\nExpected Result: %d", "Stolen Card", DECLINED_STOLEN_CARD);
	ST_cardData_t cd3 = { "Abdulrahman Omar Ahmed", "1217454752901895", "05/25" };
	transData.cardHolderData = cd3;
	transData.terminalData.transAmount = 3500.f;
	printf("\nActual Result: %d", recieveTransactionData(&transData));
	//case 4
	printf("\n\n\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: recieveTransactionData");
	printf("\nTest Case 4:");
	printf("\nInput Data: %s\nExpected Result: %d", "Approved", APPROVED);
	ST_cardData_t cd4 = { "Abdulrahman Omar Ahmed", "4562606230524624", "05/25" };
	transData.cardHolderData = cd4;
	transData.terminalData.transAmount = 5500.f;
	printf("\nActual Result: %d", recieveTransactionData(&transData));
}


/*int main() {
	ST_cardData_t cd = {"Abdulrahman Omar Ahmed", "4562606230524624", "05/25"};
	ST_terminalData_t td = { 10000, 15000, "" }; getTransactionDate(&td);
	ST_accountsDB_t* ar = &accountsDB[0];
	ST_transaction_t transData;
	printf("%d", isBelowMaxAmount(&td));
	printf("\n%d", isValidAccount(&cd, &ar));
	printf("\n%d", isBlockedAccount(ar));
	printf("\n%d\n", isAmountAvailable(&td, ar));
	getTransactionDate(&td);
	transData.cardHolderData = cd;
	transData.terminalData = td;
	transData.transState = ar->state;
	printf("\n%d\n", saveTransaction(&transData));
	listSavedTransactions();
	printf("\n\n%d", recieveTransactionData(&transData));
	
	isValidAccountTest();
	isBlockedAccountTest();
	isAmountAvailableTest();
	recieveTransactionDataTest();
	saveTransactionTest();
}*/
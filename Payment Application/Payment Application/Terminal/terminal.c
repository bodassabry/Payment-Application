#include "terminal.h"

uint8_t* calcDate() {
	time_t t = time(NULL);
	struct tm ct = *localtime(&t);
	uint8_t cct[11] = "";
	int ct1 = ct.tm_mday, ct2 = ct.tm_mon + 1, ct3 = ct.tm_year + 1900;
	cct[0] = (ct1 - (ct1 % 10)) / 10 + '0';
	cct[1] = (ct1 % 10) + '0';
	cct[2] = '/';
	cct[3] = (ct2 - (ct2 % 10))/10 + '0';
	cct[4] = (ct2 % 10) + '0';
	cct[5] = '/'; // 2022
	cct[6] = (ct3 - (ct3 % 1000)) / 1000 + '0';
	cct[7] = ((ct3 % 1000) - (ct3 % 100)) / 100 + '0';
	cct[8] = ((ct3 % 100) - (ct3 % 10)) / 10 + '0';
	cct[9] = (ct3 % 10) + '0';

	uint8_t* ptr = malloc(11);
	ptr = &cct;
	return ptr;
}

int checker(uint8_t c) {
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	uint8_t* ptr2 = calcDate();
	strncpy(termData->transactionDate, ptr2, 10);
	(*termData).transactionDate[10] = '\0';
	ptr2 = &(*termData).transactionDate;
	if (((*termData).transactionDate == NULL) || (strlen(ptr2) < 10) || !(checker(ptr2[0]) && checker(ptr2[1]) &&
		ptr2[2] == '/' && checker(ptr2[3]) && checker(ptr2[4]) && ptr2[5] == '/' && checker(ptr2[6]) && checker(ptr2[7]) &&
		checker(ptr2[8]) && checker(ptr2[9]))) {
		return WRONG_DATE;
	}
	else {
		return TERMINAL_OK;
	}
}
void getTransactionDateTest(ST_terminalData_t* termData) {
	uint8_t* ptr2 = calcDate();
	strncpy(termData->transactionDate, ptr2, 10);
	//////////////////////////////////////////
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getTransactionDate");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s\nExpected Result: %d", termData->transactionDate, TERMINAL_OK); //	dd/mm/yyyy
	//actual function
	ptr2 = &termData->transactionDate;
	if ((termData->transactionDate == NULL) || (strlen(ptr2) < 10) || !(checker(ptr2[0]) && checker(ptr2[1]) &&
		ptr2[2] == '/' && checker(ptr2[3]) && checker(ptr2[4]) && ptr2[5] == '/' && checker(ptr2[6]) && checker(ptr2[7]) &&
		checker(ptr2[8]) && checker(ptr2[9]))) {
		//return WRONG_DATE;
		printf("\nActual Result: %d", WRONG_DATE);
	}
	else {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	//test 2
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getTransactionDate");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s\nExpected Result: %d", "21/23/22", WRONG_DATE); //	dd/mm/yyyy
	//actual function
	strncpy(termData->transactionDate, "21/23/22", 10);
	if ((termData->transactionDate == NULL) || (strlen(ptr2) < 10) || !(checker(ptr2[0]) && checker(ptr2[1]) &&
		ptr2[2] == '/' && checker(ptr2[3]) && checker(ptr2[4]) && ptr2[5] == '/' && checker(ptr2[6]) && checker(ptr2[7]) &&
		checker(ptr2[8]) && checker(ptr2[9]))) {
		//return WRONG_DATE;
		printf("\nActual Result: %d", WRONG_DATE);
	}
	else {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	//test 3
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getTransactionDate");
	printf("\nTest Case 3:");
	printf("\nInput Data: %s\nExpected Result: %d", "21/mm/2022", WRONG_DATE); //	dd/mm/yyyy
	//actual function
	strncpy(termData->transactionDate, "21/mm/2022", 10);
	if ((termData->transactionDate == NULL) || (strlen(ptr2) < 10) || !(checker(ptr2[0]) && checker(ptr2[1]) &&
		ptr2[2] == '/' && checker(ptr2[3]) && checker(ptr2[4]) && ptr2[5] == '/' && checker(ptr2[6]) && checker(ptr2[7]) &&
		checker(ptr2[8]) && checker(ptr2[9]))) {
		//return WRONG_DATE;
		printf("\nActual Result: %d", WRONG_DATE);
	}
	else {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	uint8_t cd[6] = { "" }, td[11] = { "" };
	strncpy(cd, cardData->cardExpirationDate, 6);	//	mm/yy	05/25
	strncpy(td, termData->transactionDate, 11);		//	dd/mm/yyyy	18/10/2022
	if (cd[3] > td[8]) {
		return TERMINAL_OK;
	}
	else if (cd[3] == td[8]) {
		if (cd[4] > td[9]) {
			return TERMINAL_OK;
		}
		else if (cd[4] == td[9]) {
			if (cd[0] > td[3]) {
				return TERMINAL_OK;
			}
			else if (cd[0] == td[3]) {
				if (cd[1] >= td[4]) {
					return TERMINAL_OK;
				}
				else {
					return EXPIRED_CARD;
				}
			}
			else {
				return EXPIRED_CARD;
			}
		}
		else {
			return EXPIRED_CARD;
		}
	}
	else {
		return EXPIRED_CARD;
	}
}
void isCardExpiredTest(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	uint8_t cd[6] = { "" }, td[11] = { "" };
	//case 1
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isCardExpired");
	printf("\nTest Case 1:");
	printf("\nInput Data: %s and %s\nExpected Result: %d", cardData->cardExpirationDate, termData->transactionDate, TERMINAL_OK);
	strncpy(cd, cardData->cardExpirationDate, 5);	//	mm/yy	05/25
	strncpy(td, termData->transactionDate, 10);		//	dd/mm/yyyy	18/10/2022
	if (cd[3] > td[8]) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d\n", TERMINAL_OK);
	}
	else if (cd[3] == td[8]) {
		if (cd[4] > td[9]) {
			//return TERMINAL_OK;
			printf("\nActual Result: %d\n", TERMINAL_OK);
		}
		else if (cd[4] == td[9]) {
			if (cd[0] > td[3]) {
				//return TERMINAL_OK;
				printf("\nActual Result: %d\n", TERMINAL_OK);
			}
			else if (cd[0] == td[3]) {
				if (cd[1] >= td[4]) {
					//return TERMINAL_OK;
					printf("\nActual Result: %d\n", TERMINAL_OK);
				}
				else {
					//return EXPIRED_CARD;
					printf("\nActual Result: %d\n", EXPIRED_CARD);
				}
			}
			else {
				//return EXPIRED_CARD;
				printf("\nActual Result: %d\n", EXPIRED_CARD);
			}
		}
		else {
			//return EXPIRED_CARD;
			printf("\nActual Result: %d\n", EXPIRED_CARD);
		}
	}
	else {
		//return EXPIRED_CARD;
		printf("\nActual Result: %d\n", EXPIRED_CARD);
	}

	//case 2
	strncpy(cardData->cardExpirationDate, "05/20", 5);
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isCardExpired");
	printf("\nTest Case 2:");
	printf("\nInput Data: %s and %s\nExpected Result: %d", cardData->cardExpirationDate, termData->transactionDate, EXPIRED_CARD);
	strncpy(cd, cardData->cardExpirationDate, 5);	//	mm/yy	05/25
	strncpy(td, termData->transactionDate, 10);		//	dd/mm/yyyy	18/10/2022
	if (cd[3] > td[8]) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d\n", TERMINAL_OK);
	}
	else if (cd[3] == td[8]) {
		if (cd[4] > td[9]) {
			//return TERMINAL_OK;
			printf("\nActual Result: %d\n", TERMINAL_OK);
		}
		else if (cd[4] == td[9]) {
			if (cd[0] > td[3]) {
				//return TERMINAL_OK;
				printf("\nActual Result: %d\n", TERMINAL_OK);
			}
			else if (cd[0] == td[3]) {
				if (cd[1] >= td[4]) {
					//return TERMINAL_OK;
					printf("\nActual Result: %d\n", TERMINAL_OK);
				}
				else {
					//return EXPIRED_CARD;
					printf("\nActual Result: %d\n", EXPIRED_CARD);
				}
			}
			else {
				//return EXPIRED_CARD;
				printf("\nActual Result: %d\n", EXPIRED_CARD);
			}
		}
		else {
			//return EXPIRED_CARD;
			printf("\nActual Result: %d\n", EXPIRED_CARD);
		}
	}
	else {
		//return EXPIRED_CARD;
		printf("\nActual Result: %d\n", EXPIRED_CARD);
	}

	//case 3
	strncpy(cardData->cardExpirationDate, "05/22", 5);
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isCardExpired");
	printf("\nTest Case 3:");
	printf("\nInput Data: %s and %s\nExpected Result: %d", cardData->cardExpirationDate, termData->transactionDate, EXPIRED_CARD);
	strncpy(cd, cardData->cardExpirationDate, 5);	//	mm/yy	05/25
	strncpy(td, termData->transactionDate, 10);		//	dd/mm/yyyy	18/10/2022
	if (cd[3] > td[8]) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d\n", TERMINAL_OK);
	}
	else if (cd[3] == td[8]) {
		if (cd[4] > td[9]) {
			//return TERMINAL_OK;
			printf("\nActual Result: %d\n", TERMINAL_OK);
		}
		else if (cd[4] == td[9]) {
			if (cd[0] > td[3]) {
				//return TERMINAL_OK;
				printf("\nActual Result: %d\n", TERMINAL_OK);
			}
			else if (cd[0] == td[3]) {
				if (cd[1] >= td[4]) {
					//return TERMINAL_OK;
					printf("\nActual Result: %d\n", TERMINAL_OK);
				}
				else {
					//return EXPIRED_CARD;
					printf("\nActual Result: %d\n", EXPIRED_CARD);
				}
			}
			else {
				//return EXPIRED_CARD;
				printf("\nActual Result: %d\n", EXPIRED_CARD);
			}
		}
		else {
			//return EXPIRED_CARD;
			printf("\nActual Result: %d\n", EXPIRED_CARD);
		}
	}
	else {
		//return EXPIRED_CARD;
		printf("\nActual Result: %d\n", EXPIRED_CARD);
	}

	//case 4
	strncpy(cardData->cardExpirationDate, "11/22", 5);
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isCardExpired");
	printf("\nTest Case 4:");
	printf("\nInput Data: %s and %s\nExpected Result: %d", cardData->cardExpirationDate, termData->transactionDate, TERMINAL_OK);
	strncpy(cd, cardData->cardExpirationDate, 5);	//	mm/yy	05/25
	strncpy(td, termData->transactionDate, 10);		//	dd/mm/yyyy	18/10/2022
	if (cd[3] > td[8]) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d\n", TERMINAL_OK);
	}
	else if (cd[3] == td[8]) {
		if (cd[4] > td[9]) {
			//return TERMINAL_OK;
			printf("\nActual Result: %d\n", TERMINAL_OK);
		}
		else if (cd[4] == td[9]) {
			if (cd[0] > td[3]) {
				//return TERMINAL_OK;
				printf("\nActual Result: %d\n", TERMINAL_OK);
			}
			else if (cd[0] == td[3]) {
				if (cd[1] >= td[4]) {
					//return TERMINAL_OK;
					printf("\nActual Result: %d\n", TERMINAL_OK);
				}
				else {
					//return EXPIRED_CARD;
					printf("\nActual Result: %d\n", EXPIRED_CARD);
				}
			}
			else {
				//return EXPIRED_CARD;
				printf("\nActual Result: %d\n", EXPIRED_CARD);
			}
		}
		else {
			//return EXPIRED_CARD;
			printf("\nActual Result: %d\n", EXPIRED_CARD);
		}
	}
	else {
		//return EXPIRED_CARD;
		printf("\nActual Result: %d\n", EXPIRED_CARD);
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("\nEnter transaction amount: ");
	scanf("%f", &(*termData).transAmount);
	if ((*termData).transAmount <= 0.f) {
		return INVALID_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
void getTransactionAmountTest(ST_terminalData_t* termData) {
	//case 1
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getTransactionAmount");
	printf("\nTest Case 1:");
	termData->transAmount = 5000.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", termData->transAmount, TERMINAL_OK);
	//Actual function
	if (termData->transAmount <= 0.f) {
		//return INVALID_AMOUNT;
		printf("\nActual Result: %d", INVALID_AMOUNT);
	}
	else {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	//case 2
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getTransactionAmount");
	printf("\nTest Case 2:");
	termData->transAmount = 0.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", termData->transAmount, INVALID_AMOUNT);
	//Actual function
	if (termData->transAmount <= 0.f) {
		//return INVALID_AMOUNT;
		printf("\nActual Result: %d", INVALID_AMOUNT);
	}
	else {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if ((*termData).transAmount <= (*termData).maxTransAmount) {
		return TERMINAL_OK;
	}
	else {
		return EXCEED_MAX_AMOUNT;
	}
}
void isBelowMaxAmountTest(ST_terminalData_t* termData) {
	//case 1
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isBelowMaxAmount");
	printf("\nTest Case 1:");
	termData->transAmount = 3000.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", termData->transAmount, TERMINAL_OK);
	if (termData->transAmount <= termData->maxTransAmount) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	else {
		//return EXCEED_MAX_AMOUNT;
		printf("\nActual Result: %d", EXCEED_MAX_AMOUNT);
	}
	//case 2
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: isBelowMaxAmount");
	printf("\nTest Case 2:");
	termData->transAmount = 5600.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", termData->transAmount, EXCEED_MAX_AMOUNT);
	if (termData->transAmount <= termData->maxTransAmount) {
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	else {
		//return EXCEED_MAX_AMOUNT;
		printf("\nActual Result: %d", EXCEED_MAX_AMOUNT);
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	if (maxAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		(*termData).maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}
void setMaxAmountTest(ST_terminalData_t* termData, float maxAmount) {
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: setMaxAmount");
	printf("\nTest Case 1:");
	maxAmount = 5000.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", maxAmount, TERMINAL_OK);
	if (maxAmount <= 0) {
		//return INVALID_MAX_AMOUNT;
		printf("\nActual Result: %d", INVALID_MAX_AMOUNT);
	}
	else {
		termData->maxTransAmount = maxAmount;
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: setMaxAmount");
	printf("\nTest Case 2:");
	maxAmount = -10.f;
	printf("\nInput Data: %.2f\nExpected Result: %d", maxAmount, INVALID_MAX_AMOUNT);
	if (maxAmount <= 0) {
		//return INVALID_MAX_AMOUNT;
		printf("\nActual Result: %d", INVALID_MAX_AMOUNT);
	}
	else {
		termData->maxTransAmount = maxAmount;
		//return TERMINAL_OK;
		printf("\nActual Result: %d", TERMINAL_OK);
	}
}

/*int main() {
	ST_terminalData_t termData = { 0.f, 0.f, "" };
	ST_cardData_t cd = { "", "", "" };
	uint8_t* ptr2 = calcDate();
	strncpy(termData.transactionDate, ptr2, 10);	//	dd/mm/yyyy
	strncpy(cd.cardExpirationDate, "05/25", 5);		// mm/yy
	
	setMaxAmount(&termData, 5000.f);
	getTransactionDateTest(&termData); //Success
	printf("\n\n\n\n");
	//printf("\n%d", getTransactionDate(&termData));
	strncpy(termData.transactionDate, ptr2, 10);
	isCardExpiredTest(&cd, &termData); // Success
	printf("\n\n\n\n");
	//printf("\n%d", isCardExpired(&cd, &termData));
	getTransactionAmountTest(&termData); //Success
	printf("\n\n\n\n");
	//printf("\n%d", getTransactionAmount(&termData));
	isBelowMaxAmountTest(&termData); //Success
	//printf("\n%d", isBelowMaxAmount(&termData));
	//setMaxAmountTest(&termData, 10.f); //Success
}*/
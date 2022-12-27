#include "card.h"

int nameChecker(ST_cardData_t cardData) {
	uint8_t ch[25];
	bool check;
	strncpy(ch, cardData.cardHolderName, 24);
	for (int i = 0; i < 24; i++) {
		if ((ch[i] >= 'A' && ch[i]<='Z') || (ch[i]>='a' && ch[i]<='z') || ch[i] == ' ' || ch[i] == '\0') {
			check = true;
		}
		else {
			check = false;
			break;
		}
	}
	return check;
}

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("\nEnter the cardholder name: ");
	gets(&(*cardData).cardHolderName);
	if (cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 || !(nameChecker(*cardData))) {
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}
void getCardHolderNameTest(ST_cardData_t* cardData)
{
	//test procedures:
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getCardHolderName");
	char n = 0;
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: Abdulrahman Omar Ahmed\nExpected Result: %d", CARD_OK);
	//actual function:
	printf("\nEnter the cardholder name: ");
	gets(&cardData->cardHolderName);
	if (cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) {
		//return WRONG_NAME;
		printf("\nActual Result: %d", WRONG_NAME);
	}
	else
	{
		//return CARD_OK
		printf("\nActual Result: %d", CARD_OK);
	}
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: Abdulrahman Omar Ahmed Sabry\nExpected Result: %d", WRONG_NAME);
	//actual function:
	printf("\nEnter the cardholder name: ");
	gets(&cardData->cardHolderName);
	if (cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) {
		//return WRONG_NAME;
		printf("\nActual Result: %d", WRONG_NAME);
	}
	else {
		//return CARD_OK
		printf("\nActual Result: %d", CARD_OK);
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t* exDate = (*cardData).cardExpirationDate;
	printf("\nEnter the card expiry date: ");
	gets(&(*cardData).cardExpirationDate);
	if (strlen(exDate) < 5 || exDate == NULL || !((exDate[0] >= '0' && exDate[0] <= '9') &&
		(exDate[1] >= '0' && exDate[1] <= '9') && (exDate[2] == '/') && (exDate[3] >= '0' && exDate[3] <= '9') &&
		(exDate[4] >= '0' && exDate[4] <= '9'))) {
		return WRONG_EXP_DATE;
	}
	else {
		return CARD_OK;
	}
}
void getCardExpiryDateTest(ST_cardData_t* cardData) {
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getCardExpiryDate");
	char n = 0;
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: 05/25\nExpected Result: %d", CARD_OK);
	//actual funtion
	uint8_t* exDate = cardData->cardExpirationDate;
	printf("\nEnter the card expiry date: ");
	gets(&cardData->cardExpirationDate);
	if (strlen(exDate) < 5 || exDate == NULL || !((exDate[0] >= '0' && exDate[0] <= '9') &&
		(exDate[1] >= '0' && exDate[1] <= '9') && (exDate[2] == '/') && (exDate[3] >= '0' && exDate[3] <= '9') &&
		(exDate[4] >= '0' && exDate[4] <= '9'))) {
		//return WRONG_EXP_DATE
		printf("Actual Result: %d", WRONG_EXP_DATE);
	}
	else {
		//return CARD_OK
		printf("Actual Result: %d", CARD_OK);
	}
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: 05-25\nExpected Result: %d", WRONG_EXP_DATE);
	//actual funtion
	printf("\nEnter the card expiry date: ");
	gets(&cardData->cardExpirationDate);
	if (strlen(exDate) < 5 || exDate == NULL || !((exDate[0] >= '0' && exDate[0] <= '9') &&
		(exDate[1] >= '0' && exDate[1] <= '9') && (exDate[2] == '/') && (exDate[3] >= '0' && exDate[3] <= '9') &&
		(exDate[4] >= '0' && exDate[4] <= '9'))) {
		//return WRONG_EXP_DATE
		printf("Actual Result: %d", WRONG_EXP_DATE);
	}
	else {
		//return CARD_OK
		printf("Actual Result: %d", CARD_OK);
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t* PAN = (*cardData).primaryAccountNumber;
	printf("\nEnter the PAN number: ");
	gets(PAN);
	if ((*cardData).primaryAccountNumber == NULL || strlen(PAN) < 16 || strlen(PAN) > 19) {
		return WRONG_PAN;
	}
	else {
		return CARD_OK;
	}
}
void getCardPANTest(ST_cardData_t* cardData) {
	printf("\nTester Name: Abdulrahman Omar Ahmed\nFunction Name: getCardPAN");
	char n = 0;
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: 1234123412341234\nExpected Result: %d", CARD_OK);
	//actual funtion
	uint8_t* PAN = cardData->primaryAccountNumber;
	printf("\nEnter the PAN number: ");
	gets(PAN);
	if (cardData->primaryAccountNumber == NULL || strlen(PAN) < 16 || strlen(PAN) > 19) {
		//return WRONG_PAN;
		printf("\nActual Result: %d", WRONG_PAN);
	}
	else {
		//return CARD_OK;
		printf("\nActual Result: %d", CARD_OK);
	}
	printf("\nTest Case %d:", ++n);
	printf("\nInput Data: 123412341234\nExpected Result: %d", WRONG_PAN);
	//actual funtion
	printf("\nEnter the PAN number: ");
	gets(PAN);
	if (cardData->primaryAccountNumber == NULL || strlen(PAN) < 16 || strlen(PAN) > 19) {
		//return WRONG_PAN;
		printf("\nActual Result: %d", WRONG_PAN);
	}
	else {
		//return CARD_OK;
		printf("\nActual Result: %d", CARD_OK);
	}
}

/*int main() {
	ST_cardData_t cd1 = {"", "", ""};
	getCardHolderNameTest(&cd1); //Success
	//printf("%d", getCardHolderName(&cd1));
	getCardExpiryDateTest(&cd1); //Success
	//printf("\n%d", getCardExpiryDate(&cd1));
	getCardPANTest(&cd1); //Success
	//printf("\n%d", getCardPAN(&cd1));

}*/
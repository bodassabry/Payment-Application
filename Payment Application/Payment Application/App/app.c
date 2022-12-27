#include "app.h"

void appStart(void) {
	ST_cardData_t cd = { "", "", "" };
	ST_terminalData_t td = { 0.f, 0.f, "" };
	ST_accountsDB_t* ar = NULL;
	ST_transaction_t transData;
	strncpy(transData.cardHolderData.cardExpirationDate, cd.cardExpirationDate, 6);
	strncpy(transData.cardHolderData.cardHolderName, cd.cardHolderName, 25);
	strncpy(transData.cardHolderData.primaryAccountNumber, cd.primaryAccountNumber, 20);
	transData.terminalData.maxTransAmount = td.maxTransAmount;
	transData.terminalData.transAmount = td.transAmount;
	strncpy(transData.terminalData.transactionDate, td.transactionDate, 11);
	setMaxAmount(&td, 15000);
	while (true) {
		strncpy(cd.cardExpirationDate, "", 6);
		strncpy(cd.cardHolderName, "", 25);
		strncpy(cd.primaryAccountNumber, "", 20);
		if (getCardHolderName(&cd) == WRONG_NAME) {
			printf("Error: Wrong Name!!");
			continue;
		}
		if (getCardExpiryDate(&cd) == WRONG_EXP_DATE) {
			printf("Error: Wrong Expiry Date!!");
			continue;
		}
		if (getCardPAN(&cd) == WRONG_PAN) {
			printf("Error: Wrong PAN");
			continue;
		}
		td.transAmount = 0.f;
		strncpy(td.transactionDate, "", 11);
		if (getTransactionDate(&td) == WRONG_DATE) {
			printf("Error: Wrong Date!!");
			continue;
		}
		if (isCardExpired(&cd, &td) == EXPIRED_CARD) {
			printf("Declined Expired Card");
			continue;
		}
		if (getTransactionAmount(&td) == INVALID_AMOUNT) {
			printf("Error: Invalid Amount!!");
			continue;
		}
		if (isBelowMaxAmount(&td) == EXCEED_MAX_AMOUNT) {
			printf("Declined Amount Exceeding Limit");
			continue;
		}
		ar = NULL;
		if (isValidAccount(&cd, &ar) == ACCOUNT_NOT_FOUND) {
			printf("Declined Invalid Account");
			continue;
		}
		if (isAmountAvailable(&td, ar) == LOW_BALANCE) {
			printf("Declined Insuffecient Funds");
			continue;
		}
		strncpy(transData.cardHolderData.cardExpirationDate, cd.cardExpirationDate, 6);
		strncpy(transData.cardHolderData.cardHolderName, cd.cardHolderName, 25);
		strncpy(transData.cardHolderData.primaryAccountNumber, cd.primaryAccountNumber, 20);
		transData.terminalData.maxTransAmount = td.maxTransAmount;
		transData.terminalData.transAmount = td.transAmount;
		strncpy(transData.terminalData.transactionDate, td.transactionDate, 11);
		transData.transState = ar->state;
		EN_transState_t state = recieveTransactionData(&transData);
		if (state == FRAUD_CARD) {
			printf("Error: Fraud Card!!");
			continue;
		}
		else if (state == DECLINED_INSUFFECIENT_FUND) {
			printf("Error: Declined Insuffecient Fund!!");
			continue;
		}
		else if (state == DECLINED_STOLEN_CARD) {
			printf("Error: Declined Stolen Card!!");
			continue;
		}
		if (saveTransaction(&transData) == SAVING_FAILED) {
			printf("Error: Saving Failed");
			continue;
		}
		listSavedTransactions();
	}
}

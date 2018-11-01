#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>
#include "StockAccount.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <random>
void StockAccount::choice(){
	int ch; //user Choice
	cout << "Which type of sort do you want to sort the portfolio? (1 for selection sort, 2 for insertion sort)" << endl;
	cin >> ch;
	portfolio->choice = ch;//set the linked list choice to the user choice thereby sorting the list based on their input.
}
void StockAccount::displayStockPrice(string stockName){
	vector<string> stockData;//the data for the stock user wants
	populateList();//first we get randomised stock prices for various stocks.
	//Now we go through the list to see which one has the stock name and display its price. The names are stored in all the 0th column of each string vector in stockList.
	for (int i = 0; i < stockList.size() - 1; i++){//the last line is just an empty character so we don't need it.
		if (stockList[i][0] == stockName){
			stockData = stockList[i];//found the stockData lets enter it into stockData and exit loop.
			break;
		}
	}
	if (stockData.empty()){ //Couldn't find it so it must not exist.
		cout << "This stock symbol was not found." << endl;
		return; //end the method.
	}
	//got here so we must have the stockData lets display it, its name is the first element, price is the second element.
	cout << "Company-Symbol\t\t" << "Price per share" << endl;
	cout << stockData[0] << "\t\t\t" << stockData[1]<<endl;
}
void StockAccount::setRnd(){
	random_device rd;
	rnd = rd() % 100; //rnd is a number between 0 and 99 if its greater than 50 we use results2 else we use results1.  	
}
void StockAccount::populateList(){
	fstream fs;
	stockList.clear();//make sure stockList is clear. 
	vector<string> tokens;
	setRnd();//get random value.
	if (rnd > 50){//use results 2
		fs.open("Results_2.txt", std::fstream::in);
	}
	else fs.open("Results_1.txt", std::fstream::in); //use results 1.
	if (!fs){
		cout << "No stock info found found." << endl;
		return;
	}
	else{
		string line;
		while (fs.good()){
			getline(fs, line);
			tokens = split<string>(line, " \t"); //get the current line and split it based on the seperators and put it into the vector for processing
			stockList.push_back(tokens); //put stock in our current stockList.
		}
		fs.close();
	}
}
void StockAccount::writePort(){
	//we'll go through the portfolio writing the information of the stocks one portfolio per line, we'll rewrite each time we have to write.
	ofstream fs("portHistory.txt", fstream::out, fstream::trunc); //this will create the object if it doesn't exist.
	Node *curr = portfolio->myHead;
	while (curr != NULL){
		//write to the file with all the info of each node one line at at time, tab seperated, it'll be in name, price, numshares, value order.
		fs << curr->itemName << "\t" << curr->itemNo << "\t" << curr->numberShares << "\t" << (curr->itemNo*curr->numberShares) << endl;
		curr = curr->next; //advance curr.
	}
}
void StockAccount::updatePortfolio(){
	//we wrote to portfolio lets use that file to write to the portfolio
	ifstream fs;
	fs.open("portHistory.txt", fstream::in);//want to read from this file.
	portfolio = new LinkedList(); //reset portfolio.
	if (!fs.is_open()){
		return;//we're done no portfolio history was found.
	}
	string line;
	vector<string>tokens;//same as many times before.
	Node *n;
	while (fs.good()){
		getline(fs, line);
		tokens = split<string>(line, "\t");//it should be seperated by tabs.
		if (fs.eof()){
			break;
		}
		//since we stored in name,price,numshares,value order we will populate the portfolio based on this data, note this data should be sorted, since the portfolio is always sorted.
		n = new Node(tokens[0], stof(tokens[1]), stof(tokens[3]), stoi(tokens[2]));
		//lets add the node to portfolio and move on.
		portfolio->addToEnd(n);
	}
}
void StockAccount::buyShares(){
	updateBalance();
	updatePortfolio();//make sure we have most recent portfolio.
	populateList();
	vector<string> stockData; //this will store the stock price.
	fstream fs;
	float amountShares;
	float stockPrice;
	float userPrice;
	string stockName;
	cout << "What stock do you want to buy?" << endl;
	cin >> stockName;
	for (int i = 0; i < stockList.size() - 1; i++){//the last line is just an empty character so we don't need it.
		if (stockList[i][0] == stockName){
			stockData = stockList[i];//found the stockData lets enter it into stockData and exit loop.
			break;
		}
	}
	if (stockData.empty()){
		cout << "That stock does not exist in our database." << endl;
		return;
	}
	cout << "How many shares do you want to buy?" << endl;
	cin >> amountShares;
	cout << "What price are you willing to purchase this stock at?" << endl;
	cin >> userPrice;//this is the users price for stock
	stockPrice = stof(stockData[1]); //get the stock price and convert it to a float.
	if (stockPrice > userPrice){
		cout << "That price is to low for stock " << stockName << "." << endl;
		return;//make sure they cant continue
	}
	if (balance < (userPrice * amountShares)){
		cout << "You do not have enough money to buy that many shares, please deposit " << ((userPrice * amountShares) - balance) << " more and try again." << endl;
		return;//make sure they cant continue.
	}
	//lets see if the stock exists in the portfolio.  
	Node *curr = portfolio->myHead; //set the current to the head of portfolio.
	while (curr != NULL){
		if (curr->itemName == stockName){//we found the stock in portfolio lets edit it appropriately.
			curr->itemNo = userPrice;
			curr->numberShares += amountShares;
			curr->value = userPrice * curr->numberShares;
			return; //we're done adding lets just get out of the function
		}
		curr = curr->next;//advance curr.
	}
	//didn't find it lets make a new entry.
	Node *n = new Node(stockName, userPrice, (amountShares * userPrice), amountShares); //create the node to add to portfolio
	portfolio->addToEnd(n); //add the node to the portfolio and we're done.
	//now we need to save this event in the stock transaction history
	fs.open("stock_transaction_history.txt", fstream::out | fstream::app); //we want to output to the file and append to it.
	//I'm not going to do a check because this file should exist otherwise its a program error.
	//time info
	time_t seconds;
	seconds = time(NULL);
	tm  timeinfo;
	localtime_s(&timeinfo, &seconds);
	//get rid of some characters that append a new line in the time string. 
	char str[26];
	asctime_s(str, &timeinfo);
	string times = (string)str;
	times = times.substr(0, 24);
	fs << "Buy\t" << stockName << "\t\t" << amountShares << "\t" << userPrice << "\t\t" << (amountShares * userPrice) << "\t\t" << times << endl;
	writePort();//did something to portfolio so we save its current state.
	//have to save the new state of balance in history.
	fs.close();//close old file.
	fs.open("history.txt", fstream::out | fstream::app);//want to append to history, this will also create history if none exists.
	balance -= (amountShares*userPrice); //subtract balance with the amount bought.
	fs << times << " Stock Buy: " << (amountShares * userPrice) << " New Balance: " << balance << "\n"; //save to balance history.
	cout << "Transaction Complete!" << endl;//let user know it went through.
}
void StockAccount::sellShares(){
	//almost the same as buy shares but we check for a little different things.
	updateBalance();
	updatePortfolio();//make sure we have most recent portfolio.
	populateList();
	vector<string> stockData; //this will store the stock price.
	fstream fs;
	float amountShares;
	float stockPrice;
	float userPrice;
	string stockName;
	cout << "What stock do you want to sell?" << endl;
	cin >> stockName;
	Node *curr = portfolio->myHead;
	while (curr != NULL){
		if (curr->itemName == stockName){
			//we found the correct node lets stay here.
			break;
		}
		curr = curr->next;//advance curr until we reach end
	}
	if (curr == NULL){
		cout << "You do not currently have any shares in that stock." << endl;
		return;//make sure they cant continue.
	}
	cout << "How many shares do you want to sell?" << endl;
	cin >> amountShares;
	if (curr->numberShares < amountShares){//they dont have that many shares.
		cout << "You currently do not have that many shares to sell." << endl;
		return;
	}
	cout << "What price do you want to sell this stock at?" << endl;
	cin >> userPrice;
	//lets go through the portfolio to ensure we have the stock and enough shares.
	for (int i = 0; i < stockList.size() - 1; i++){
		if (stockList[i][0] == stockName){
			stockData = stockList[i];
			break;
		}
	}
	stockPrice = stof(stockData[1]); //get the stock price and convert it to a float.
	if (stockPrice < userPrice){
		cout << "That price is too high to sell stock " << stockName << "." << endl;
		return; //make sure they can't continue.
	}
	//got here so they must have the stock 
	//well they must have the stock and the proper amount of shares to sell so lets just edit this entry and move on.
	curr->numberShares -= amountShares;
	curr->itemNo = userPrice;//set the stock price the price the user sold at.
	curr->value = (curr->numberShares*userPrice);
	balance += (amountShares*userPrice);//new balance and new amount of shares.
	if (curr->numberShares == 0){
		//we need to remove this from their portfolio
		portfolio->removeNodeFromList(stockName);
	}
	//save this in transaction history
	fs.open("stock_transaction_history.txt", fstream::out | fstream::app); //we want to output to the file and append to it.
	//I'm not going to do a check because this file should exist otherwise its a program error.
	//time info
	time_t seconds;
	seconds = time(NULL);
	tm  timeinfo;
	localtime_s(&timeinfo, &seconds);
	//get rid of some characters that append a new line in the time string. 
	char str[26];
	asctime_s(str, &timeinfo);
	string times = (string)str;
	times = times.substr(0, 24);
	fs << "Sell\t" << stockName << "\t\t" << amountShares << "\t" << userPrice << "\t\t" << (amountShares * userPrice) << "\t\t" << times << endl;
	fs.close();//close old file.
	fs.open("history.txt", fstream::out | fstream::app);//want to append to history, this will also create history if none exists.
	fs << times << " Stock Sell: " << (amountShares * userPrice) << " New Balance: " << balance << "\n"; //save to balance history.
	writePort(); //update portfolio.
	cout << "Transaction Complete" << endl;//let user know it went through.
}
void StockAccount::displayPortfolio(){
	updatePortfolio();
	updateBalance();
	vector<string> tokens;//for the transaction history.
	cout << "Cash Balance = " << balance << endl;//print out the balance.
	float total = 0;//total portfolio value.
	total += balance; //add balance.
	if (portfolio->size() == 0){
		cout << "Portfolio is empty, please buy shares to fill the portfolio." << endl;
		return;//make sure they cant continue.
	}
	//well portfolio must have something lets display it.
	cout << "Company-Symbol\tNumber\tPrice-per-share\tTotal value" << endl;
	Node *curr = portfolio->myHead;
	while (curr != NULL){
		cout << curr->itemName << "\t\t" << curr->numberShares << "\t" << curr->itemNo << "\t\t" << curr->value << endl;
		total += curr->value;//add the value.
		curr = curr->next;
	}
	cout << "Total portfolio value: " << total << endl;
}
void StockAccount::printHistory(){
	ifstream fs;
	fs.open("stock_transaction_history.txt", fstream::in);//read from this file.
	string line;
	while (fs.good()){
		getline(fs, line);
		cout << line << endl;//display one line at a time of the history. 
	}
	fs.close();//close file before exiting.
}
void StockAccount::createPortfolioHistory(){//this will create the portfolio values we need to graph, we'll call it when program exits.
	vector<string> stockData; //this will store the stock price.
	//time info
	time_t seconds;
	seconds = time(NULL);
	updatePortfolio();
	updateBalance();
	populateList();//make sure to get a random value for the stock price.
	vector<string> tokens;//for the transaction history.
	float total = 0;//total portfolio value.
	total += balance; //add balance.
	if (portfolio->size() == 0){
		return;//make sure they cant continue.
	}
	//well portfolio must have something lets display it.
	Node *curr = portfolio->myHead;
	while (curr != NULL){
		for (int i = 0; i < stockList.size() - 1; i++){//the last line is just an empty character so we don't need it.
			if (stockList[i][0] == curr->itemName){
				stockData = stockList[i];//found the stockData lets enter it into stockData and exit loop.
				break;
			}
		}
		total += (float)curr->numberShares * stof(stockData[1]); //make sure the value uses the current stock price rather than the price user paid for it.
		curr = curr->next;
	}
	ofstream fs;
	fs.open("pHistory.txt", fstream::out | fstream::app);//append to the file and open it for writing, this will create it if it doesn't exist.
	fs << seconds << "\t" << total << endl;
	fs.close();
}
void StockAccount::graphPort(){
	//matlab engine.
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	}
	//first we need the x values for graph, i.e the date get this from pHistory.
	ifstream fs;
	fs.open("pHistory.txt", fstream::in);//read from phistory.
	if (!fs.is_open()){
		cout << "There is no portfolio history start to buy and sell shares and exit the program several times to view the graph." << endl;
		return;
	}
	string line;
	vector<vector<string>> data;//store that data here.
	vector<string> tokens;//intermediate values.
	int size1 = 0;
	while (fs.good()){
		getline(fs, line);
		if (fs.eof())break;//don't want the empty line
		size1++;
	}
	fs.close();
	fs.open("pHistory.txt", fstream::in);
	int size = 0;
	double *x = new double[size1];
	double *y = new double[size1];
	while (fs.good()){
		getline(fs, line);
		if (fs.eof())break;//don't want the empty line
		tokens = split<string>(line, "\t");//it should be seperated by tabs.
		x[size] = stod(tokens[0]); //should be date.
		y[size] = stod(tokens[1]);//should be total value.
		size++;
	}
	mxArray *A;
	mxArray *B;
	// assume a gets initialized, all values
	A = mxCreateDoubleMatrix(1, size1, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)x, sizeof(double)*size1);
	engPutVariable(ep, "x", A);
	B = mxCreateDoubleMatrix(1, size1, mxREAL);
	memcpy((void *)mxGetPr(B), (void *)y, sizeof(double)*size1);
	engPutVariable(ep, "y", B);
	engEvalString(ep, "plot(x, y);");
	engEvalString(ep, "xlabel(\'Seconds After 1/1/1970\')");
	engEvalString(ep, "ylabel(\'Total Portfolio Value (USD)\')");
}
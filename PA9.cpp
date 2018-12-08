#include "PA9.h"


/*************************************************************
 * Function: readBody ()                  	
 * Date Created: 4/27/18                  	        
 * Date Last Modified: 1/27/18                        
 * Description: This function reads the contents of the	
 *              image file's body                	
 * Input parameters: The image data and input file.    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	the file name must be declared     	
 * Post: The body of the file is processed     
 *************************************************************/
void readBody(ifstream& inputFile, short imageData[ROWS][COLS][PIXEL_SIZE]) {
	string line;
	istringstream inputStringStream;
	int value;
	int rowIndex = 0, colIndex = 0, colorIndex = 0;
	
	while (!inputFile.eof()) {
		getline(inputFile, line);
		if (inputFile.good()) {
			//cout << "Line: " << line << endl;
			inputStringStream.clear(); // for good practice
			inputStringStream.str(line);
			colIndex = 0;
			do {
				inputStringStream >> value;
				if (inputStringStream.good()) {
					// insert value into imageData
					// at the correct row, column, and RGB index
					imageData[rowIndex][colIndex][colorIndex] = value;
					colorIndex++;
					if (colorIndex == 3) {
						// we just finished processing an RGB triple
						colorIndex = 0;
						colIndex++; // next triple goes in the next column
					}
				}
			
			} while(inputStringStream.good());
			rowIndex++;
		}
	}
}

/*************************************************************
 * Function: readHeader ()                  	
 * Date Created: 4/27/18                  	        
 * Date Last Modified: 1/27/18                        
 * Description: This function reads the contents of the	
 *              image file's header and prints them               	
 * Input parameters: The rows, collums and input file.    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	the file name must be declared     	
 * Post: The header of the file is processed and output     
 *************************************************************/
void readHeader(ifstream& inputFile, int& rows, int& cols) {
	string line;
	
	getline(inputFile, line);
	cout << "Specification: " << line << endl;
	inputFile >> cols >> rows; 
	cout << "Rows: " << rows << " " << " Cols: " << cols << endl;
	getline(inputFile, line); // get rid of newline after rows
	getline(inputFile, line);
	cout << "Max RGB value: " << line << endl;
}

/*************************************************************
 * Function: openFile ()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/1/18                        
 * Description: This function opens the output file            	
 * Input parameters: The output file and the file name  	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	the file name must be declared     	
 * Post: The output file is opened    
 *************************************************************/
void openFile(ofstream& outputFile, string nameOfFile) {
	
	outputFile.open(nameOfFile);
	
	if (outputFile.is_open()) {
		cout << "Successfully opened output file" << endl;
	}
	else {
		cout << "Failed to open output file" << endl;
		exit(-1); // exits program
	}
}

/*************************************************************
 * Function: openInputFile ()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/1/18                        
 * Description: This function opens the input file            	
 * Input parameters: The input file and the file name  	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	the file name must be declared     	
 * Post: The input file is opened    
 *************************************************************/
void openInputFile(ifstream& inputFile, string nameOfFile){
	inputFile.open(nameOfFile);
	cout << nameOfFile << endl;
	if (inputFile.is_open()) {
		cout << "File successfully opened" << endl;
	}
	else {
		cout << "Failed to open file" << endl;
		exit(-1); // exits the program
	}
}

/*************************************************************
 * Function: applyModifacation()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function opens and calls the modifacation
 *            files, and closes the files once finished               	
 * Input parameters: The rows, collums and input file.    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	the file name must be declared     	
 * Post: The moddifactions are called and the file is essentially
 * 	 processed here     
 *************************************************************/
void applyModification(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, string& nameOfFile, ofstream& outputFile, ifstream& inputFile) {


	string userInput; // the user input that determines what ppm to use
	string nameInput; // the name of the file before the .ppm part of it
			  // used in a for loop to continuosly add chars to a
			  // string until the period that I mentioned earlier
	
	string modifyString[] = {"_vertical", "_horizontal", "_remove_red", "_remove_green", "_remove_blue", "_negate_color", "_high_contrast", "_random_noise", "_gray_scale", "_jacksonPollock", "_horizontal_blur"}; // holds all the various names of the moddifactions, used as an array it can be put into a for loop to make things easier and less hardcoded
	
	cout << "Please enter the name of a PPM file you want processed: "; // prompt the user
	cin >> userInput; // get user input so you know what image to input
	cout << endl; // create space for readability

	openInputFile(inputFile, userInput); // call the open image function to open the image based on user input

	
	
	readHeader(inputFile, rows, cols); // call the read header
	readBody(inputFile, imageData); // call the read body

	// print out the last RGB value in thee file
	cout << imageData[rows - 1][cols - 1][0] << " " << imageData[rows - 1][cols - 1][1] << " "  << imageData[rows - 1][cols - 1][2] << endl;


	
	for (int i = 0; i < userInput.size(); i++) { // used to loop through the string until it encounters a period
						     // sequentially adding chars to inputName, this is the for loop
						     // that I mentioned earlier
			if (userInput[i] == '.') { // if the char is a period
				break; // should break the loop once the if statement condition is met (the period was encountered)
			} else {
			nameInput += userInput[i]; // adds the current char at position i to the nameInput variable for later
			}
	} 
	
	for (int i = 0; i <= 10; i++) { // for loop to aplly the modifacation and close the file one at a time, or else I would have to close the
				       // files after every call, which would get a little tiring, I think a for loop and a switch
				       // statement saves time and energy
		nameOfFile = nameInput + modifyString[i] + ".ppm"; // (concatination) add the strings together to get the correct file name
		cout << nameOfFile << endl; // print out the name of the file as they process it with each iteration of the for loop
		openFile(outputFile, nameOfFile); // open all the different files
		
		switch (i){// switch staement within the for loop to open the files sequentialy
			case 0 : applyVerticalFlip(imageData, rows, cols, outputFile);
				break;
			case 1 : applyHorizontalFlip(imageData, rows, cols, outputFile);
				break;
			case 2 : removeRed(imageData, rows, cols, outputFile);
				break;
			case 3 : removeGreen(imageData, rows, cols, outputFile);
				break;
			case 4 : removeBlue(imageData, rows, cols, outputFile);
				break;
			case 5 : computeNegativeValue(imageData, rows, cols, outputFile);
				break;
			case 6 : computeHighContrastValue(imageData, rows, cols, outputFile);
				break;
			case 7 : computeRandomNoiseValue(imageData, rows, cols, outputFile);
				break;
			case 8 : computeGrayScaleValue(imageData, rows, cols, outputFile);
				break;
			case 9: JacksonPollock(imageData, rows, cols, outputFile); // for fun :)
				break;
			case 10: horozontalBlur(imageData, rows, cols, outputFile); // Extra credit
				break;
		}
	outputFile.close(); // close the file after each case, if you don't do this switch and output close here, only vertical will open
	}
	
}

/*************************************************************
 * Function: verticalFlip()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function opens flips the image vertically              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file is flipped vertically   
 *************************************************************/
void applyVerticalFlip(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

		int i, j, k;
		
		outputFile << "P3" << endl; // header info is the same for all pictures
		outputFile << cols << " " << rows << endl;
		outputFile << "255" << endl;
		
		for(i = rows; i >= 1; i--) {
			for(j = cols; j >= 1; j--) {
				for(k = 0; k < 3; k++) {
				outputFile << imageData[i][j][k] << " ";
			}
		}
	}

}

/*************************************************************
 * Function: horozontalFlip()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function opens flips the image horozontally              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file is flipped horozontally  
 *************************************************************/
void applyHorizontalFlip(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {


		int i, j, k;
		
		outputFile << "P3" << endl; // header info is the same for all pictures
		outputFile << cols << " " << rows << endl;
		outputFile << "255" << endl;
		
	for(i = 0; i < rows; i++){
		for(j = cols; j > 0; j--){
			for(k = 0; k < 3; k++){
			outputFile << imageData[i][j][k] << " ";
			}
		}
	}
}

/*************************************************************
 * Function: JacksonPollock()                  	
 * Date Created: 5/1/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function rearanges the image to look like
 *              A Jackson Pollock painting (he was famous for
 *		crazy, nonsensical artwork)             	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file is sort of twisted around into waves 
 *************************************************************/
void JacksonPollock(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

		int i, j, k;
		
		outputFile << "P3" << endl; // header info is the same for all pictures
		outputFile << cols << " " << rows << endl;
		outputFile << "255" << endl;

		for(j = cols; j >= 1; j--) { //increment rows and cols
			for(i = rows; i >= 1; i--) {
				for(k = 0; k < 3; k++) {
				outputFile << imageData[i][j][k] << " ";
			}
		}
	}
}

/*************************************************************
 * Function: removeRed()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function removes the red RGB value from
 *		the image              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB index at 0 is set to 0 
 *************************************************************/
void removeRed(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

	int i, j, k;

	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) { //increment rows and cols
			for(k = 0; k < 3; k++){
				if(k == 0){ // RGB -> R is at index 0
				outputFile << 0 << " "; // output 0 at that index
				} else {
				outputFile << imageData[i][j][k] << " "; // output the normal value
				}
			}
		}
	}

}

/*************************************************************
 * Function: removeGreen()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function removes the green RGB value from
 *		the image              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB index at 1 is set to 0 
 *************************************************************/
void removeGreen(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

	int i, j, k;

	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) { //increment rows and cols
		for(j = 0; j < cols; j++) {
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				if(k == 1){ // RGB -> G is at index 1
				outputFile << 0 << " "; // output 0 at that index
				} else {
				outputFile << imageData[i][j][k] << " "; // if not the output should remain normal
				}
			}
		}
	}
}

/*************************************************************
 * Function: removeBlue()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function removes the blue RGB value from
 *		the image              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB index at 2 is set to 0 
 *************************************************************/
void removeBlue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {
	int i, j, k;
	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) { //increment rows and cols
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				if(k == 2){ // RGB -> B is at index 2
				outputFile << 0 << " "; // output 0 at that index
				} else {
				outputFile << imageData[i][j][k] << " "; // if not the output should remain normal
				}
			}
		}
	}	
}

/*************************************************************
 * Function: computeNegativeValue()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function removes the green RGB value from
 *		the image              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB values are inverted
 *************************************************************/
void computeNegativeValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {
	int i, j, k, negative;
	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;	
	for(i = 0; i < rows; i++) { // rows loop
		for(j = 0; j < cols; j++) { // collum loop
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				negative = abs(imageData[i][j][k] - 255); // to invert the colors, get the absolute
									 // value of the RGB value - the max value
									 // of 255
				outputFile << negative << " "; // output the altered RGB value
			}
		}
	}
}

/*************************************************************
 * Function: computeHighContrastValue()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function increases and decreases the overall
 *		RGB values from the image drastically              	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB values are high contrast
 *************************************************************/
void computeHighContrastValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {
	int i, j, k;
	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) { // rows loop
		for(j = 0; j < cols; j++) { // collum loop
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				if(imageData[i][j][k] >= 127){ // amplify the color to 255 if rgb is > 127, otherwis lower it to 0
				outputFile << 255 << " "; // output a high RGB value
				} else {
				outputFile << 0 << " "; // output a low RGB value
				}
			}
		}
	}
}

/*************************************************************
 * Function: computeRandomNoiseValue()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function adds random noise to the image             	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB values are moddified at random
 *************************************************************/
void computeRandomNoiseValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {
	int i, j, k;
	int randRGB;
	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) { // rows loop
		for(j = 0; j < cols; j++) { // collum loop
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				randRGB = k + (rand()% 101); // generate a random intager between 1 and 100
					if(randRGB < 0){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
						randRGB *= (-1); // if the value is less than 1, multiplay it by -1 to get a positive
					}
					outputFile << imageData[i][j][k] + randRGB << " "; // add the randRGB value to the normal RGB value to create noise (randomly altered RGBs)
			}
		}
	}
}

/*************************************************************
 * Function: computeGrayScaleValue()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function makes the image black and white
 *		essentially            	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB values are moddified to be gray scale
 *************************************************************/
void computeGrayScaleValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

	int i, j, k;
	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
	for(i = 0; i < rows; i++) { // rows loop
		for(j = 0; j < cols; j++) { // collum loop
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				outputFile << imageData[i][j][k / 3] << " "; // divide the rgb values by 3 to remove the color from the image
			}
		}
	}
}

/*************************************************************
 * Function: horozontalBlur()                  	
 * Date Created: 4/30/18                  	        
 * Date Last Modified: 5/2/18                        
 * Description: This function makes the image black and white
 *		essentially            	
 * Input parameters: The image data, rows, collums and the
 *		     output file    	
 * Returns: n/a           	
 * Pre: The file must be present in the folder and          
 *            	have been called in apply modifacation    	
 * Post: The file's RGB values are moddified to be gray scale
 *************************************************************/
void horozontalBlur(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile) {

	int i, j, k, newK;
	int count = 0;
	int total = 0;
	newK = 0;

	outputFile << "P3" << endl; // header info is the same for all pictures
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;

	for(i = 0; i < rows; i++) { // rows loop
		for(j = 0; j < cols; j++) { // collum loop
			count++; // count up before to check if 5 incraments have occured
			for(k = 0; k < 3; k++){	// loop through the RGBs 3 times, 1 = R, 2 = G, 3 = B
				if(count % 5 == 0){ // if there is no remainder, it must be a multiple of five so blur is nessisary
					outputFile << ((imageData[i][j][k] + imageData[i - 1][j - 1][k] + imageData[i - 2][j - 2][k] + imageData[i - 3][j - 3][k] + imageData[i - 4][j - 4][k]) / 5) << " "; // gets the average of the last 5 tripples
				} else {
				outputFile << imageData[i][j][k] << " "; // normal RGB value
				}
			}
		}
	}
}

/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer readerCreate(int size, int increment, int mode) {
	// New reader
	BufferPointer readerPointer;
	/* TO_DO: Defensive programming */ /*size cant be (-) along with increment and mode has to be either addative, multip., or fixed*/
	if (size < 0 || increment < 0 || (mode != 'f' && mode != 'a' && mode != 'm'))
		return NULL;

	if (size == 0) {
		size = READER_DEFAULT_SIZE;
	}

	if (increment == 0) {
		increment = READER_DEFAULT_INCREMENT;
		mode = MODE_FIXED;
	}

	/* TO_DO: Adjust the values according to parameters */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return NULL;

	readerPointer->content = (str)malloc(size);
		

	/* TO_DO: Defensive programming */
	if (readerPointer->content == NULL)
		return NULL;
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags = readerPointer->flags | FLAG_EMP;
	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, sofia_char ch) {
	str tempReader = NULL;
	int newSize = 0;
	/* TO_DO: Defensive programming */// done
	if (readerPointer == NULL)
		return NULL;
	if (ch < 0 || ch > NCHAR)
		return NULL;
	/* TO_DO: Reset Realocation */
	readerPointer->flags = readerPointer->flags & FLAG_REL;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (int)sizeof(sofia_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = readerPointer->flags & FLAG_FUL; // Resets
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */ /*Go to 1:28:00 for further explanation btw if it is not ok then return NULL*/
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader)
			return NULL;
		/* TO_DO: Check Relocation */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	readerPointer->flags = readerPointer->flags & !FLAG_EMP;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	return True;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return True;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags & FLAG_FUL)
		readerPointer->flags = readerPointer->flags | FLAG_FUL;
	else
		readerPointer->flags = readerPointer->flags & !FLAG_FUL;

	return False;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return True;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags & FLAG_EMP)
		readerPointer->flags = readerPointer->flags | FLAG_EMP;
	else
		readerPointer->flags = readerPointer->flags & !FLAG_EMP;
	return False;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerSetMark(BufferPointer const readerPointer, int mark) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	if (mark < 0)
		return False;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return True;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerPrint(BufferPointer const readerPointer) {
	int cont = 0;
	sofia_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (readerPointer == NULL)
		return READER_ERROR;
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	if (readerPointer->flags & FLAG_END)
		readerPointer->flags = readerPointer->flags | FLAG_END;
	else
		readerPointer->flags = readerPointer->flags & !FLAG_END;
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	int size = 0;
	sofia_char c;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return READER_ERROR;
	if (fileDescriptor == NULL)
		return READER_ERROR;

	c = (sofia_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) /*Can also be written as returnPointer == NULL*/
		return False;
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return True;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->position.read > 0) {
		readerPointer->position.read--;
		return True;
	}
		
	return False;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return False;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return True;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
sofia_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) /*Can also be written as returnPointer == NULL*/
		return READER_TERMINATOR;
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read < readerPointer->position.wrte) {
		readerPointer->flags = readerPointer->flags & !FLAG_END;

		if (readerPointer->position.read == readerPointer->position.wrte - 1) {
			readerPointer->flags = readerPointer->flags | FLAG_END;
		}
	}
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	if (readerPointer->position.wrte>0)
		return readerPointer->content[readerPointer->position.read++];
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
str readerGetContent(BufferPointer const readerPointer, int pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) /*Can also be written as returnPointer == NULL*/
		return NULL;
	if ((pos < 0) || pos > readerPointer->position.wrte) /*The reason why we have the second condition is beacuse the pos cannot exceed the wrte however this part of the code is optional*/
		return NULL;
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos; 
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
byte readerGetFlags(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return NULL;
	/* TO_DO: Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
none readerPrintStat(BufferPointer const readerPointer) {
	
	if (readerPointer == NULL)
		return;
	/* TO_DO: Print the histogram */ 
	for (int i = 0; i < NCHAR; i++) {
		
		if(readerPointer->histogram[i] > 0)
			if (i < 32)
				printf("Histogram[%d] = %d\n", i, readerPointer->histogram[i]); /*When using %d it will print out the characters*/
			else
			printf("Histogram[%c] = %d\n", i, readerPointer->histogram[i]); /*When using %c it will print out the characters*/
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int readerNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return CHARSEOF;
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;

}

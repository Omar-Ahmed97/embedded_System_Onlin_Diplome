/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "linked_list.h"

int main()
{
	char temp_text[40];

	while(1)
	{
		Dprintf("\n=============================");
		Dprintf("\n\tChoose one of the following option ::\n");
		Dprintf("\n 1: ADD STUDENT>>>");
		Dprintf("\n 2: DELETE STUDENT>>>");
		Dprintf("\n 3: VIEW STUDENT>>>");
		Dprintf("\n 4: DELETE ALL>>>");
		Dprintf("\n 5: GET INDEX>>>");
		Dprintf("\n 6: print number of elements>>>");
		Dprintf("\n 7: GET INDEX Backward>>>");
		Dprintf("\n 8: PRINT MIDDLLE ELEMENT>>>");
		Dprintf("\n 9: REVERSE LINKED LIST>>>");
		Dprintf("\n Enter option number:");

		gets(temp_text);
		Dprintf("\n =============================");

		switch(atoi(temp_text))
		{

		case 1:
			add_student();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			view_student();
			break;
		case 4:
			deleteAll();
			break;
		case 5:
			Dprintf("\n Enter index ::");
			gets(temp_text);
			getNth(atoi(temp_text));
			break;
		case 6:
				printNumEle();
				break;

		case 7:
			Dprintf("\n Enter index ::");
			gets(temp_text);
			findIndexBackward(atoi(temp_text));
			break;
		case 8:
			 findMiddle();
			 break;
		case 9:
			 reversNodes();
			break;
		default: Dprintf("\n wrong option");
		break;

		}


	}




	return 0;
}

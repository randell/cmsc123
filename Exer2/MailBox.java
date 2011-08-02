/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 24, 2003
	chai356@yahoo.com
	
	Problem: There are 200 mailboxes, numbered 1 to 200 in the Post Office.
				During a boring night, the postman on duty played with the mailboxes.  Beginning
				with mailbox 2, he opened the doors of every even-numbered mailbox.  Then starting
				at mailbox 3, he started to open every third mailbox if it was closed, closed it if it was
				already opened.  Then he repeated this procedure with every fourth mailbox, then
				with every fifth mailbox, and so on.  Which of the mailboxes were open after the
				whole "exercise" was over?
*/

/* 1st Algorithm 						*/
/* T(n) = 2(n)squared + 11n + 4			*/
/* o(n) = n squared 					*/

class MailBox {
	public static void main (String[] args){
		boolean box[] = new boolean[201];
		int total = 0;
		// box[] = false is a closed box
		// box[] = true is an open box
		for (int i = 2; i <= 200; i++)
			for (int j = i; j <= 200; j += i)
				if (box[j] == false)
					box[j] = true;	// opens a closed mailbox when encountered
				else
					box[j] = false;	// closes an open mailbox when encountered
		for (int i = 1; i <= 200; i++)
			if (box[i] == false) {
				total++;			// counts the total number of closed mailbox
				System.out.println(i);
			}
		System.out.println("The total number of closed mailboxes is " + total + ".");	
	}
}
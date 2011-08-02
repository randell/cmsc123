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

/* Improved Algorithm of MailBox using mathematical analysis 	*/
/* T(n) = 6 * sqrt(n) + 3										*/
/* O(n) = sqrt(n)												*/

class MailBox2 {
	public static void main (String[] args){
		int total = 0; 
		for (int i = 1; i * i < 200; i++) { // searches for the closed mailboxes
			total++; // used to count the closed mailboxes
			System.out.println(i * i); // computes and prints the number of closed mailboxes
		}
		System.out.println("The total number of closed mailboxes is " + total + ".");	
	}
}